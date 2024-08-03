#include "post_request.hpp"

// Function to handle the POST request
void post_request(int socket_id, HTTPRequestParse request)
{
    FILE *file;
    size_t itemsWritten;
    stringstream message;
    //ssize_t bytes_sent;
    //int send_attempts = 0;
    //const int MAX_SEND_ATTEMPTS = 3;
    file = NULL;
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
