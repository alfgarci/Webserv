#include "get_request.hpp"

int stringToInt(const std::string& str)
{
    std::istringstream iss(str);
    int result;

    iss >> result;
    return (result);
}

// Function to handle the GET request
void get_request(int socket_id, HTTPRequestParse request, Server server)
{
    void *content;
    FILE *file;
    size_t length;
    size_t itemsRead;
    stringstream message;
    int send_attempts;
    int intPort;
    std::list<t_route> routes;
    //ssize_t bytes_sent;
    //const int MAX_SEND_ATTEMPTS = 3;

    // Send attempts initialized to 0
    send_attempts = 0;

    // Get the host, path and port from the request
    string host = request.getField(HTTPRequestParse::HOST);
    string path = request.getField(HTTPRequestParse::PATH);
    string port = request.getField(HTTPRequestParse::PORT);

     // port is a string, convert it to int
    intPort = stringToInt(port);

    // iterator to find the port in the list of ports
    std::list<int>::iterator it_1 = std::find(server.getPorts().begin(), server.getPorts().end(), intPort);
    
    // Intialize the routes list
    routes = server.getLocations();
    // iterator to find the path in the list of routes
    std::list<t_route>::iterator it_2 = routes.begin();
    while (it_2 != routes.end())
    {
        if (it_2->search_dir == path)
            break;
        it_2++;
    }

    // Check if port is valid
    if (it_1 == server.getPorts().end())
        message << WRONG_PORT << port << DOUBLE_LINE_BREAK;
    // Check if hosts is valid
    else if (server.getIp() != host)
        message << NOT_VALID_HOST;
    // Check if path is valid
    else if (it_2 == routes.end())
        message << PATH_VALIDATION_ERROR;
    else if (!handle_cgi_request(path, "", message))
	{
		// Try to handle as CGI request first
        struct stat path_stat;
        stat(path.c_str(), &path_stat);
        if (S_ISDIR(path_stat.st_mode))
		{
            DIR *dir;
            struct dirent *ent;
            if ((dir = opendir(path.c_str())) != NULL)
			{
                message.str(EMPTY);
                message << OK << CONNECTION;
                message << "<html><head><title>Index of " << path << "</title></head><body><h1>Index of " << path << "</h1><ul>";
                while ((ent = readdir(dir)) != NULL)
                    message << "<li><a href=\"" << ent->d_name << "\">" << ent->d_name << "</a></li>";
                message << "</ul></body></html>";
                closedir(dir);
            }
			else
			{
                message.str(EMPTY);
                message << FILE_NOT_FOUND;
            }
        }
		else
		{
            file = fopen(path.c_str(), READ_BINARY);
            if (file) {
                message << OK << CONNECTION;
                fseek(file, 0, SEEK_END);
                length = ftell(file);
                fseek(file, 0, SEEK_SET);
                content = malloc(length);
                if (content)
				{
                    itemsRead = fread(content, 1, length, file);
                    if (itemsRead < length)
					{
                        if (ferror(file))
						{
                            message.str(EMPTY);
                            message << READ_FILE_ERROR;
                        }
						else
						{
                            message.str(EMPTY);
                            message << PARTIAL_READ_ERROR;
                        }
                    }
					else
					    message.write(static_cast<const char*>(content), itemsRead);
                    free(content);
                }
				else
				{
                    message.str(EMPTY);
                    message << INTERNAL_SERVER_ERROR;
                }
                if (fclose(file) != 0)
				{
                    message.str(EMPTY);
                    message << FILE_CLOSE_ERROR;
                }
            }
			else
			{
                message.str(EMPTY);
                message << FILE_NOT_FOUND;
            }
        }
    }
    // Intenta enviar la respuesta al cliente
    send_response(socket_id, message.str());
}
