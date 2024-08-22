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
using std::map;

class Server
{
private:

	list<Socket>	_main_socket;
	list<int>		_socket_fd;
	string			_ip;
	list<int>		_port;
	map<int, int>	_map_fd_port;	
	string			_name;
	unsigned int	_client_limit_body_size;
	string			_root;
	string			_index;
	bool			_auto_index;
	list<t_route>	_locations;
	list<t_error>	_errorPages;

public:

	Server();
	Server(t_server *info_server);
	Server(const Server &other);
	Server& operator=(const Server &other);

	void			setupSocket();
	string			getName() { return this->_name; };
	list<int>		getSocketFd() { return this->_socket_fd; };
	list<int>		getPorts() { return this->_port; };
	string 			getIp() { return this->_ip; };
	string 			getRoot() { return this->_root; };
	list<t_route>	getLocations() { return this->_locations; };
	list<t_error>	getErrorPages() { return this->_errorPages; };
	unsigned int	get_limit_body_size() {return this->_client_limit_body_size;};
	int				getPortByFd(int fd);
	~Server() { /* this->close(); */ }

	void close();
};
