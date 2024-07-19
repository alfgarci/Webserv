#include <cstdio>
#include <iostream>
#include <sstream>
#include <sys/socket.h>
#include <unistd.h>
#include <dirent.h> // For opendir(), readdir(), closedir()
#include <sys/stat.h> // For stat()
#include "HTTPRequestParse.hpp"

using std::cerr;
using std::string;
using std::stringstream;

// Server configuration
#define EXPECTED_HOST "www.example.com"
#define EXPECTED_PORT "80"

// Normal functioning messages
#define CONNECTION "Connection: keep-alive\n\n"
#define OK "HTTP/1.1 200 OK\n\n"

// Error messages
#define FILE_CLOSE_ERROR "HTTP/1.1 500 Internal Server Error. Error: File close failed\n\n"
#define FILE_NOT_FOUND "HTTP/1.1 404 Not Found\n\n"
#define INTERNAL_SERVER_ERROR "HTTP/1.1 500 Internal Server Error\n\n"
#define NOT_VALID_HOST "HTTP/1.1 400 Bad Request. Error: Not valid host\n\n"
#define PARTIAL_READ_ERROR "HTTP/1.1 500 Internal Server Error. Error: Partial file read\n\n"
#define READ_FILE_ERROR "HTTP/1.1 500 Internal Server Error. Error: Reading file\n\n"
#define WRONG_PORT "HTTP/1.1 400 Bad Request. Wrong Port: "
#define PATH_VALIDATION_ERROR "HTTP/1.1 400 Bad Request. Error: Invalid Path\n\n"
#define SEND_ERROR "HTTP/1.1 500 Internal Server Error. Error sending message. Attempt: "
#define FINAL_SEND_ERROR "HTTP/1.1 500 Internal Server Error. Failed to send message after final attempt.\n\n"
#define SOCKET_CLOSING_ERROR "Error closing socket\n\n"

// Other definitions
#define READ_BINARY "rb"
#define DOUBLE_LINE_BREAK "\n\n"
#define EMPTY ""

// Function to handle the GET request
void get_request(int socket_id, HTTPRequestParse request)
{   
    // Variable to store file data
    void *content;
    // File to be open
    FILE *file;
    // Length of the file
    size_t length;
    // Items read from the file
    size_t itemsRead;
    // Message
    stringstream message;
    // Bytes sent
    ssize_t bytes_sent;
    // Send attempts
    int send_attempts;
    // Max send attempts
    const int MAX_SEND_ATTEMPTS = 3;

    send_attempts = 0;

    string host = request.getField(HTTPRequestParse::HOST);
    string path = request.getField(HTTPRequestParse::PATH);
    string port = request.getField(HTTPRequestParse::PORT);

    // Validación básica del path
    if (path.find("..") != string::npos)
        message << PATH_VALIDATION_ERROR;
    // Check if host and port are valid
    else if (host != EXPECTED_HOST)
        message << NOT_VALID_HOST;
    else if (port != EXPECTED_PORT)
        message << WRONG_PORT << EXPECTED_PORT << DOUBLE_LINE_BREAK;
    else
    {
        struct stat path_stat;
        stat(path.c_str(), &path_stat);
        // Verificar si el path es un directorio
        if (S_ISDIR(path_stat.st_mode)) {
            DIR *dir;
            struct dirent *ent;
            // Abrir el directorio
            if ((dir = opendir(path.c_str())) != NULL) {
                // Limpiar el mensaje y empezar a construir la respuesta HTML
                message.str(EMPTY);
                message << OK << CONNECTION;
                message << "<html><head><title>Index of " << path << "</title></head><body><h1>Index of " << path << "</h1><ul>";
                // Leer los contenidos del directorio
                while ((ent = readdir(dir)) != NULL) {
                    message << "<li><a href=\"" << ent->d_name << "\">" << ent->d_name << "</a></li>";
                }
                message << "</ul></body></html>";
                closedir(dir);
            } else {
                // No se pudo abrir el directorio
                message.str(EMPTY);
                message << FILE_NOT_FOUND;
            }
        } else {
            // Intentar abrir el archivo
            file = fopen(path.c_str(), READ_BINARY);
            if (file) {
                // Mensaje indica que todo está OK
                message << OK << CONNECTION;
                fseek(file, 0, SEEK_END);
                length = ftell(file);
                fseek(file, 0, SEEK_SET);
                content = malloc(length);
                if (content) {
                    itemsRead = fread(content, 1, length, file);
                    if (itemsRead < length) {
                        if (ferror(file)) {
                            message.str(EMPTY);
                            message << READ_FILE_ERROR;
                        } else {
                            message.str(EMPTY);
                            message << PARTIAL_READ_ERROR;
                        }
                    } else {
                        message.write(static_cast<const char*>(content), itemsRead);
                    }
                    free(content);
                } else {
                    message.str(EMPTY);
                    message << INTERNAL_SERVER_ERROR;
                }
                if (fclose(file) != 0) {
                    message.str(EMPTY);
                    message << FILE_CLOSE_ERROR;
                }
            } else {
                message.str(EMPTY);
                message << FILE_NOT_FOUND;
            }
        }
    }
    do {
        bytes_sent = send(socket_id, message.str().c_str(), message.str().size(), 0);
        if (bytes_sent == -1) {
            cerr << SEND_ERROR << send_attempts + 1 << "\n\n";
            send_attempts++;
            sleep(1);
        }
    } while (bytes_sent == -1 && send_attempts < MAX_SEND_ATTEMPTS);

    if (bytes_sent == -1)
        cerr << FINAL_SEND_ERROR;
    if (close(socket_id) != 0)
        cerr << SOCKET_CLOSING_ERROR;
}
