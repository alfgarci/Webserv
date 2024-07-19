#include <cstdio>
#include <iostream>
#include <sstream>
#include <sys/socket.h>
#include <unistd.h>
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
	// File to be open
	FILE *file;
	// Items read from the file
	size_t itemsWritten;
	// Message
	stringstream message;
    // Bytes sent
	ssize_t bytes_sent;
    // Send attempts
    int send_attempts;
    // Max send attempts
    const int MAX_SEND_ATTEMPTS = 3;

    send_attempts = 0;
    file = nullptr;
    string host = request.getField(HTTPRequestParse::HOST);
	string path = request.getField(HTTPRequestParse::PATH);
	string port = request.getField(HTTPRequestParse::PORT);
    string body = request.getField(HTTPRequestParse::BODY);

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
    			if (fclose(file) != 0)
	    		{
		    	    message.str(EMPTY);
   			    	message << FILE_CLOSE_ERROR;
			    }
                else
                    // Prepare the message
                    message << OK << DATA_PROC;
            }
        }
    }
    do
    {
        bytes_sent = send(socket_id, message.str().c_str(), message.str().size(), 0);
        if (bytes_sent == -1) {
            cerr << SEND_ERROR << send_attempts + 1 << "\n\n" << endl;
            send_attempts++;
            // Wait 1 second before trying again
            sleep(1);
        }
    } while (bytes_sent == -1 && send_attempts < MAX_SEND_ATTEMPTS);

    // After the loop, check if the message was sent
    if (bytes_sent == -1)
        cerr << FINAL_SEND_ERROR << endl;
    // Close the socket
    if (close(socket_id) != 0)
        cerr << SOCKET_CLOSING_ERROR << endl;
}