#include <cstdio>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include "HTTPRequestParse.hpp"
#include "send_cgi_handle.hpp"

using std::cerr;
using std::string;
using std::stringstream;

// Server configuration
#define EXPECTED_HOST "www.example.com"
#define EXPECTED_PORT "80"
#define CGI_DIR "/path/to/cgi-bin/" // Asegúrate de que esta definición coincida con la de cgi_handle.hpp

// Normal functioning messages
#define CONNECTION "Connection: keep-alive\n\n"
#define OK "HTTP/1.1 200 OK\n\n"
#define DATA_PROC "Data processed successfully\n"

// Error messages
#define FILE_CLOSE_ERROR "HTTP/1.1 500 Internal Server Error. Error: File close failed\n\n"
#define FILE_OPEN_ERROR "HTTP/1.1 500 Internal Server Error. Fail opening file\n\n"
#define FILE_WRITE_ERROR "HTTP/1.1 500 Internal Server Error\n\nFail Writing file\n\n"
#define INTERNAL_SERVER_ERROR "HTTP/1.1 500 Internal Server Error\n\n"
#define NOT_VALID_HOST "HTTP/1.1 400 Bad Request. Error: Not valid host\n\n"
#define WRONG_PORT "HTTP/1.1 400 Bad Request. Wrong Port: "
#define PATH_VALIDATION_ERROR "HTTP/1.1 400 Bad Request. Error: Invalid Path\n\n"
#define SEND_ERROR "HTTP/1.1 500 Internal Server Error. Error sending message. Attempt: "
#define FINAL_SEND_ERROR "HTTP/1.1 500 Internal Server Error. Failed to send message after final attempt.\n\n"
#define SOCKET_CLOSING_ERROR "Error closing socket\n\n"

// Other definitions
#define WRITE_BINARY "wb"
#define DOUBLE_LINE_BREAK "\n\n"
#define EMPTY ""

// Function to handle the POST request
void post_request(int socket_id, HTTPRequestParse request)
{
    FILE *file;
    size_t itemsWritten;
    stringstream message;
    ssize_t bytes_sent;
    int send_attempts = 0;
    const int MAX_SEND_ATTEMPTS = 3;
    file = nullptr;
    string host = request.getField(HTTPRequestParse::HOST);
    string path = request.getField(HTTPRequestParse::PATH);
    string port = request.getField(HTTPRequestParse::PORT);
    string body = request.getField(HTTPRequestParse::BODY);

    // Intenta manejar la solicitud como CGI si el path es correcto
    if (path.find(CGI_DIR) == 0)
    {
        if (handle_cgi_request(path, body, message)) {
            // La solicitud CGI fue manejada exitosamente
            // Envía la respuesta al cliente
            send_response(socket_id, message.str());
            return; // Termina el manejo de la solicitud
        }
        // Si el manejo de CGI falla, continúa para intentar manejar como una operación de archivo
    }

    // Validación básica del path
    if (path.find("..") != string::npos)
        message << PATH_VALIDATION_ERROR;
    else if (host != EXPECTED_HOST)
        message << NOT_VALID_HOST;
    else if (port != EXPECTED_PORT)
        message << WRONG_PORT << EXPECTED_PORT << DOUBLE_LINE_BREAK;
    else
    {
        file = fopen(path.c_str(), WRITE_BINARY);
        if (!file)
            message << FILE_OPEN_ERROR;
        else
        {
            itemsWritten = fwrite(body.c_str(), 1, body.size(), file);
            if (itemsWritten != body.size())
                message << FILE_WRITE_ERROR;
            else
            {
                if (fclose(file) != 0)
                {
                    message.str(EMPTY);
                    message << FILE_CLOSE_ERROR;
                }
                else
                    message << OK << DATA_PROC;
            }
        }
    }
    // Intenta enviar la respuesta al cliente
    send_response(socket_id, message.str());
}
