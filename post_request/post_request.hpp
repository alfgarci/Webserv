#ifndef POST_REQUEST_HPP
#define POST_REQUEST_HPP

#include <string>
#include "../HTTPRequestParse/HTTPRequestParse.hpp"
#include <cstdio>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include "../send_cgi_handle/send_cgi_handle.hpp"
#include "../ServerCore/Server.hpp"
# include "../libs/to_int.hpp"

using std::cerr;
using std::string;
using std::stringstream;
using std::list;

// Server configuration
#define EXPECTED_HOST "www.example.com"
#define EXPECTED_PORT "80"
#define CGI_DIR "/path/to/cgi-bin/" // Asegúrate de que esta definición coincida con la de cgi_handle.hpp

// Normal functioning messages
#define CONNECTION_KEEP_REQUEST "Connection: keep-alive\n\n"
#define OK "HTTP/1.1 200 OK\n\n"
#define DATA_PROC "Data processed successfully\n"

// Error messages
#define FILE_CLOSE_ERROR "HTTP/1.1 500 Internal Server Error. Error: File close failed\n\n"
#define FILE_OPEN_ERROR "HTTP/1.1 500 Internal Server Error. Fail opening file\n\n"
#define FILE_WRITE_ERROR "HTTP/1.1 500 Internal Server Error\n\nFail Writing file\n\n"
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

// Declaraciones de funciones
void post_request(int socket_id, HTTPRequestParse request, Server server);

#endif // POST_REQUEST_HPP
