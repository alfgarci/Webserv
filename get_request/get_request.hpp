#ifndef GET_REQUEST_HPP
# define GET_REQUEST_HPP

#pragma once

# include <dirent.h>		// For opendir(), readdir(), closedir()
# include <string>
# include <sys/socket.h>
# include <sys/stat.h>	// For stat()
# include <unistd.h>
# include "../HTTPRequestParse/HTTPRequestParse.hpp"
# include "../send_cgi_handle/send_cgi_handle.hpp"
# include "../ServerCore/Server.hpp"
# include "../libs/to_int.hpp"

using std::cerr;
using std::list;
using std::string;
using std::stringstream;


// Server configuration
# define EXPECTED_HOST "www.example.com"
# define EXPECTED_PORT "80"

// Normal functioning messages
# define CONNECTION_KEEP_REQUEST "Connection: keep-alive\n\n"
# define OK "HTTP/1.1 200 OK\n\n"

// Error messages
# define FILE_CLOSE_ERROR "HTTP/1.1 500 Internal Server Error. Error: File close failed\n\n"
# define FILE_NOT_FOUND "HTTP/1.1 404 Not Found\n\n"
# define INTERNAL_SERVER_ERROR "HTTP/1.1 500 Internal Server Error\n\n"
# define NOT_VALID_HOST "HTTP/1.1 400 Bad Request. Error: Not valid host\n\n"
# define PARTIAL_READ_ERROR "HTTP/1.1 500 Internal Server Error. Error: Partial file read\n\n"
# define READ_FILE_ERROR "HTTP/1.1 500 Internal Server Error. Error: Reading file\n\n"
# define WRONG_PORT "HTTP/1.1 400 Bad Request. Wrong Port: "
# define PATH_VALIDATION_ERROR "HTTP/1.1 400 Bad Request. Error: Invalid Path\n\n"

// Other definitions
# define READ_BINARY "rb"
# define DOUBLE_LINE_BREAK "\n\n"
# define EMPTY ""

// Declaración de la función para manejar la solicitud GET
void get_request(int socket_id, HTTPRequestParse request, Server server);
int stringToInt(const std::string& str);

#endif // GET_REQUEST_HPP
