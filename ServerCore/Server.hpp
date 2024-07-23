#pragma once

#include "Socket.hpp"
#include "../ServerInfo/structs.hpp"
#include <map>
#include <fcntl.h>

class Server
{
private:
	list<Socket>	_main_socket;
	std::string	_ip;
	list<int>	_port;
	list<int>	_socket_fd;
	int			_client_limit_body_size;
	std::string	_server_name;
	std::string	_root;
	std::string	_index;
	bool		_auto_index;
	std::map<int, std::string>	_error_pages;
	//locations

public:
	fd_set current_socket, ready_socket;

	Server();
	Server(t_server *info_server);
	Server(const Server &other);
	Server& operator=(const Server &other);

	void			setupSocket();
	list<int>		getSocketFd() { return this->_socket_fd; };
	list<int>		getPorts() { return this->_port; };
	std::string 	getIp() {return this->_ip; };
	~Server(){ this->close(); }

	void close();
}; 