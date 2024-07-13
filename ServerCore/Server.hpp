#pragma once

#include "Socket.hpp"

class Server
{
private:
    Socket main_socket;
public:
    fd_set current_socket, ready_socket;

    Server();
    ~Server(){ this->close(); }

    void run();
    void close();
};