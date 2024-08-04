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

using std::string;
using std::list;

class Server
{
private:

	list<Socket>				_main_socket;
	list<int>					_socket_fd;
	string						_ip;
	list<int>					_port;
	string						_name;
	int							_client_limit_body_size;
	string						_root;
	string						_index;
	bool						_auto_index;
	list<t_route>				_locations;

public:

	Server();
	Server(t_server *info_server);
	Server(const Server &other);
	Server& operator=(const Server &other);

	void			setupSocket();
	list<int>		getSocketFd() { return this->_socket_fd; };
	list<int>		getPorts() { return this->_port; };
	string 			getIp() { return this->_ip; };
	list<t_route>	getLocations() { return this->_locations; };
	~Server() { /* this->close(); */ }

	void close();
};
