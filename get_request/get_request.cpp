#include "get_request.hpp"

// Function to handle the GET request
void get_request(int socket_id, HTTPRequestParse request, Server server)
{
	void *content;
	FILE *file;
	size_t length;
	size_t itemsRead;
	stringstream message;
	int intPort;
	std::list<t_route> routes;
	//ssize_t bytes_sent;
	//const int MAX_SEND_ATTEMPTS = 3;

	// Send attempts initialized to 0

	// Get the host, path and port from the request
	string host = request.getField(HTTPRequestParse::HOST);
	string path = request.getField(HTTPRequestParse::PATH);
	string port = request.getField(HTTPRequestParse::PORT);

	// port is a string, convert it to int
	std::istringstream iss(port);


	intPort = to_int(port);

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
	{
		cout << "\033[0;31m" << "HOST RECUPERADO " << server.getIp() << "\n\033[0m" << endl;       
		message << NOT_VALID_HOST;
	}    
	// Check if path is valid
	else if (it_2 == routes.end())
		message << PATH_VALIDATION_ERROR;

	cout << "\033[0;31m"<< "PUERTO: " << port << " - HOST: " << host << " - PATH: " << path << "\n\033[0m" << endl;
	cout << "\033[0;31m"<< "MESSAGE: " << message.str() << "\n\033[0m" << endl;

	// Handling file or directory serving
	struct stat path_stat;
	stat(path.c_str(), &path_stat);
	if (S_ISDIR(path_stat.st_mode))
	{
		DIR *dir;
		struct dirent *ent;
		if ((dir = opendir(path.c_str())) != NULL)
		{
			message.str(EMPTY);
			message << OK_GET << CONNECTION_KEEP_REQUEST_GET;
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
			message << OK_GET << CONNECTION_KEEP_REQUEST_GET;
			message << "Content-Type: text/html; charset=UTF-8\r\n";
			message << "Content-Length: ";
			fseek(file, 0, SEEK_END);
			length = ftell(file);
			message << length << "\r\n\r\n";
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
				message << "HTTP/1.1 500 Internal Server Error\r\n";
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

	std::string tmp =
    "HTTP/1.1 200 OK\r\n"
    "Connection: keep-alive\r\n"
    "Content-Type: text/html; charset=UTF-8\r\n"
    "Content-Length: 2384\r\n"
    "\r\n"
    "<!DOCTYPE html>\n"
    "<html lang=\"en\">\n"
    "<head>\n"
    "    <meta charset=\"UTF-8\">\n"
    "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
    "    <title>WebServer Project</title>\n"
    "    <style>\n"
    "        body {\n"
    "            font-family: 'Helvetica Neue', Arial, sans-serif;\n"
    "            background-color: #f5f5f5;\n"
    "            color: #333;\n"
    "            text-align: center;\n"
    "            margin: 0;\n"
    "            padding: 0;\n"
    "            display: flex;\n"
    "            justify-content: center;\n"
    "            align-items: center;\n"
    "            height: 100vh;\n"
    "        }\n"
    "        .container {\n"
    "            max-width: 800px;\n"
    "            margin: auto;\n"
    "            padding: 20px;\n"
    "            background: #fff;\n"
    "            border-radius: 8px;\n"
    "            box-shadow: 0 4px 8px rgba(0,0,0,0.1);\n"
    "        }\n"
    "        h1 {\n"
    "            font-size: 60px;\n"
    "            color: #3498db;\n"
    "            margin: 0;\n"
    "        }\n"
    "        h2 {\n"
    "            font-size: 36px;\n"
    "            color: #333;\n"
    "            margin: 20px 0 10px;\n"
    "        }\n"
    "        p {\n"
    "            font-size: 20px;\n"
    "            line-height: 1.6;\n"
    "            margin: 10px 0;\n"
    "        }\n"
    "        .authors {\n"
    "            font-size: 18px;\n"
    "            margin-top: 20px;\n"
    "        }\n"
    "        .authors a {\n"
    "            color: #3498db;\n"
    "            text-decoration: none;\n"
    "            font-weight: bold;\n"
    "        }\n"
    "        .authors a:hover {\n"
    "            text-decoration: underline;\n"
    "        }\n"
    "    </style>\n"
    "</head>\n"
    "<body>\n"
    "    <div class=\"container\">\n"
    "        <h1>WebServer Project</h1>\n"
    "        <h2>About the Project</h2>\n"
    "        <p>\n"
    "            Welcome to the WebServer project! This project aims to create a custom web server\n"
    "            with various features, including handling HTTP requests, serving static files, and\n"
    "            managing client connections efficiently. The server supports multiple HTTP methods\n"
    "            and provides a robust platform for serving web content.\n"
    "        </p>\n"
    "        <p>\n"
    "            This project is a part of the 42 coding curriculum, focusing on low-level server\n"
    "            development and network programming.\n"
    "        </p>\n"
    "        <h2>Authors</h2>\n"
    "        <div class=\"authors\">\n"
    "            <p>Vicente García Andrade (<a href=\"https://github.com/Quierounnombre\">vicgarci</a>)</p>\n"
    "            <p>Alfonso García Peñas (<a href=\"https://github.com/Alfgarci\">alfgarci</a>)</p>\n"
    "            <p>Antonio Oteo Bedoya (<a href=\"https://github.com/Naholos\">aoteo-be</a>)</p>\n"
    "        </div>\n"
    "    </div>\n"
    "</body>\n"
    "</html>\n";

	send_response(socket_id, message.str());
}
