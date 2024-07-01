#include <iostream>
#include <sstream>
#include <sys/socket.h>
#include "HTTPRequestParse.hpp"

using std::string;
using std::stringstream;

// Server configuration
#define EXPECTED_HOST "www.example.com"
#define EXPECTED_PORT "80"

// Normal functioning messages
#define CONNECTION "Connection: keep-alive\n\n"
#define OK "HTTP/1.1 200 OK\n\n"

// Error messages
#define FILE_OPEN_ERROR "HTTP/1.1 500 Internal Server Error. Fail opening file\n\n"
#define FILE_WRITE_ERROR "HTTP/1.1 500 Internal Server Error\n\nFail Writing file\n\n"
#define INTERNAL_SERVER_ERROR "HTTP/1.1 500 Internal Server Error\n\n"
#define NOT_VALID_HOST "HTTP/1.1 400 Bad Request. Error: Not valid host\n\n"
#define WRONG_PORT "HTTP/1.1 400 Bad Request. Wrong Port: "

// Other definitions
#define WRITE_BINARY "wb"
#define DOUBLE_LINE_BREAK "\n\n"
#define EMPTY ""

// Function to handle the POST request
void post_request(int socket_id, HTTPRequestParse request)
{
	// File to be open
	FILE *file;
	// Length of the file
	size_t length;
	// Items read from the file
	size_t itemsWritten;
	// Message
	stringstream message;

    string host = request.getField(HTTPRequestParse::HOST);
	string path = request.getField(HTTPRequestParse::PATH);
	string port = request.getField(HTTPRequestParse::PORT);
    string body = request.getField(HTTPRequestParse::BODY);

    // Check if host and port are valid
    if (host != EXPECTED_HOST)
        message << NOT_VALID_HOST;
    else if (port != EXPECTED_PORT)
        message << WRONG_PORT << EXPECTED_PORT << DOUBLE_LINE_BREAK;
    else
    {
        // Trying to open the file
		file = fopen(path.c_str(), WRITE_BINARY);
        // Check if the file was opened successfully
        if (!file)
            message << FILE_OPEN_ERROR;
        else
        {
            // Write the body data to the file
            itemsWritten = fwrite(body.c_str(), 1, body.size(), file);
            // Check if the file was written successfully
            if (itemsWritten != body.size())
                message << FILE_WRITE_ERROR ;
            else
            {
                // Close the file
                fclose(file);
                // Prepare the message
                message << OK << "Data processed successfully.\n";
            }
        }
    }
    // Send the message
    send(socket_id, message.str().c_str(), message.str().size(), 0);
}