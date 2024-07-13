#include "Server.hpp"

Server::Server()
    :main_socket("127.0.0.1", 1234)
{
    main_socket.bind();
    main_socket.listen();

    FD_ZERO(&this->current_socket);
    FD_SET(this->main_socket.getFd(), &(this->current_socket));
}

void Server::run()
{

    int max_socket = this->main_socket.getFd() + 1;
    std::cout << "Max_socket: " << max_socket << std::endl;

    while (true)
    {
        this->ready_socket = this->current_socket;
        if (select(max_socket , &(this->ready_socket), NULL, NULL, NULL) < 0)
            std::cout << "FAIL" << std::endl;
        for (int i = 0; i < max_socket; i++)
        {
            if (FD_ISSET(i, &(this->ready_socket)))
            {
                if (i == this->main_socket.getFd())
                {
                    struct sockaddr_in client_addr;
                    int addr_size = sizeof(struct sockaddr_in);
                    int client_socket = accept(this->main_socket.getFd(),
                                        (struct sockaddr *)&client_addr,
                                        (socklen_t*)&addr_size);
                    FD_SET(client_socket, &(this->current_socket));
                    if (client_socket + 1 > max_socket)
                        max_socket = client_socket + 1;
                    std::cout << "Nuevo cliente conectado: " << client_socket << std::endl;
                }
                else
                {
                    std::cout << "recieving\n";
                    char request[512];
                    /* Recibir lo que esta enviando el cliente  */
                    recv(i, request, sizeof(request), 0);
                    /* Enviar una respuesta en base a la peticion */
                    std::string response = "I RECIEVED YOUR RESPONSE!";
                    std::cout << request << std::endl;
                    send(i, response.c_str(), response.size(), 0);
                    FD_CLR(i, &(this->current_socket));

                }
            }
        }
    }
}

void Server::close()
{
    this->main_socket.close();
}