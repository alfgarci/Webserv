#include "post_request.hpp"

// Function to handle the POST request
void post_request(int socket_id, HTTPRequestParse request, Server server)
{
    FILE *file;
    size_t itemsWritten;
    stringstream message;
    //ssize_t bytes_sent;
    //int send_attempts = 0;
    //const int MAX_SEND_ATTEMPTS = 3;
    int intPort;
    std::list<t_route> routes;

    file = NULL;
    string host = request.getField(HTTPRequestParse::HOST);
    string path = request.getField(HTTPRequestParse::PATH);
    string port = request.getField(HTTPRequestParse::PORT);
    string body = request.getField(HTTPRequestParse::BODY);

     // port is a string, convert it to int
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
