#ifndef SERVERCORE_HPP
#define SERVERCORE_HPP

#include <vector>
#include <map>
#include <sys/select.h>
#include "ServerConfig.hpp"
//#include "Client.hpp"

class ServerCore
{
public:
    ServerCore(std::vector<ServerConfig>& configs);
    ~ServerCore();
    void run();

private:
    std::vector<ServerConfig> _configs;
    std::map<int, ServerConfig*> _fd_to_config_map;
    std::map<int, Client> _clients;
    fd_set _read_fds;
    fd_set _write_fds;
    int _max_fd;

    void initialize();
    void acceptNewConnection(int server_fd);
    void handleClientData(int client_fd);
    void closeConnection(int fd);
};

#endif // SERVERCORE_HPP
