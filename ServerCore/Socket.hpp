#pragma once

#include <string>
#include <iostream>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <cstring>
#include <iostream>
#include <string>
#include <unistd.h>

class Socket
{
private:
    std::string ip;
    uint16_t port;
    bool binded;
    int fd;
    int domain;
    int type;
    int protocol;
    struct sockaddr_in sockaddr;
public:
    Socket(const std::string & ip, uint16_t port);
    void bind(void);
    void listen(void);
    void close(void);

    int getFd();
};