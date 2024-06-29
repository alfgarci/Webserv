#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

// Server configuration
#define EXPECTED_HOST "www.example.com"
#define EXPECTED_PORT "80"

// Function to handle the GET request
void get_request(int socket_id, const std::string &path, const std::string &host, const std::string port)
{   
    // Variable to store file data
    void *content;
    // File to be open
    FILE *file;
    // Length of the file
    size_t length;
    // Message
    std::stringstream message;

    // Check if host and port are valid
    if (host != EXPECTED_HOST)
        message << "HTTP/1.1 400 Bad Request. Error: Host no válido\n\n";
    else if (port != EXPECTED_PORT)
        message << "HTTP/1.1 400 Bad Request. Puerto incorrecto: " << EXPECTED_PORT << "." << "\n\n";
    else
    {
        // Trying to open the file
        file = fopen(path.c_str(), "rb");
        // Open file
        if (file)
        {
            // Message says everything is OK
            message << "HTTP/1.1 200 OK\n\n";
            // Connection will be always "keep-alive"
            message << "Connection: keep-alive\n\n";
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
                fread(content, 1, length, file);
                // Add the content to the message
                message << content;
                // Free the content
                free(content);
            }
            // File is not read    
            else
            {   
                // Clear the message
                message.str("");
                // Message says there was an internal server error   
                message << "HTTP/1.1 500 Internal Server Error\n\n";
            }
            // Close the file
            fclose(file);
        }
        // If file not found
        else
        {
            // Clear the message
            message.str("");
            // Message says file not found
            message << "HTTP/1.1 404 Not Found\n\n";
        }
    }    
    // Send the message
    send(socket_id, message.str().c_str(), message.str().size(), 0);
}