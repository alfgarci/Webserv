#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>

// Server configuration
#define EXPECTED_HOST "www.example.com"
#define EXPECTED_PORT "80"

// Normal functioning messages
#define CONNECTION "Connection: keep-alive\n\n"
#define OK "HTTP/1.1 200 OK\n\n"

// Error messages
#define FILE_NOT_FOUND "HTTP/1.1 404 Not Found\n\n"
#define INTERNAL_SERVER_ERROR "HTTP/1.1 500 Internal Server Error\n\n"
#define NOT_VALID_HOST "HTTP/1.1 400 Bad Request. Error: Not valid host\n\n"
#define PARTIAL_READ_ERROR "HTTP/1.1 500 Internal Server Error. Error: Partial file read\n\n"
#define READ_FILE_ERROR "HTTP/1.1 500 Internal Server Error. Error: Reading file\n\n"
#define WRONG_PORT "HTTP/1.1 400 Bad Request. Wrong Port: "

// Other definitions
#define READ_BINARY "rb"
#define DOUBLE_LINE_BREAK "\n\n"
#define EMPTY ""


// Function to handle the GET request
void get_request(int socket_id, const std::string &path, const std::string &host, const std::string port)
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
	std::stringstream message;

	// Check if host and port are valid
	if (host != EXPECTED_HOST)
		message << NOT_VALID_HOST;
	else if (port != EXPECTED_PORT)
		message << WRONG_PORT << EXPECTED_PORT << DOUBLE_LINE_BREAK;
	else
	{
		// Trying to open the file
		file = fopen(path.c_str(), READ_BINARY);
		// Open file
		if (file)
		{
			// Message says everything is OK
			message << OK;
			// Connection will be always "keep-alive"
			message << CONNECTION;
			// Move the file pointer to the end of the file
			fseek(file, 0, SEEK_END);
			// Obtain the current position of the file pointer, that is the length of the file
			length = ftell(file);
			// Move the file pointer back to the beginning of the file
			fseek(file, 0, SEEK_SET);
			// Try to read file
			content = malloc(length);
			// If content is allocated without any error
			if (content)
			{
				// Read the file
				itemsRead = fread(content, 1, length, file);
				if (itemsRead < length)
				{
					if (ferror(file))
					{
						// Clear the message and report a read error
						message.str(EMPTY);
						message << READ_FILE_ERROR;
					}
					else
					{
						// Clear the message and report a partial read error
						message.str(EMPTY);
						message << PARTIAL_READ_ERROR;
					}
				}
				else 
				{
					// Correctly add binary content to the message
					message.write(static_cast<const char*>(content), itemsRead);
				}
				// Free the content
				free(content);
			}
			// File is not read	
			else
			{   
				// Clear the message
				message.str(EMPTY);
				// Message says there was an internal server error   
				message << INTERNAL_SERVER_ERROR;
			}
			// Close the file
			fclose(file);
		}
		// If file not found
		else
		{
			// Clear the message
			message.str(EMPTY);
			// Message says file not found
			message << FILE_NOT_FOUND;
		}
	}	
	// Send the message
	send(socket_id, message.str().c_str(), message.str().size(), 0);
}
