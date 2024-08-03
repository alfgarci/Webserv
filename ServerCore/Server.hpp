#pragma once

#include "Socket.hpp"
#include "../ServerInfo/structs.hpp"
#include <map>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <fcntl.h>

class Server
{
private:
	list<Socket>				_main_socket;
	std::list<int>				_socket_fd;
	std::string					_ip;
	std::list<int>				_port;
	std::string					_name;
	int							_client_limit_body_size;
	std::string					_root;
	std::string					_index;
	bool						_auto_index;
	std::list<t_route>			_locations;

public:

	Server();
	Server(t_server *info_server);
	Server(const Server &other);
	Server& operator=(const Server &other);

	void			setupSocket();
	list<int>		getSocketFd() { return this->_socket_fd; };
	list<int>		getPorts() { return this->_port; };
	std::string 	getIp() {return this->_ip; };
	~Server() { /* this->close(); */ }

	void close();
};
