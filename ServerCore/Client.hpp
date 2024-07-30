#pragma once

#include "Socket.hpp"
#include "Server.hpp"
#include "../HTTPRequestParse/HTTPRequestParse.hpp"

class Client
{
private:
	int			_socket_client;
	std::string	_request;
	Server		_host_server;
	int			_request_bytes_read;

	HTTPRequestParse	_parse_request;

public:

	Client();
	Client(Server serv);
	Client &operator=(const Client &other);
	~Client();

	void	setSocketClient(int fd) { this->_socket_client = fd; };
	void	setRequest(std::string request){ this->_request = request; };
	void	setRequest(char buffer[], int size){ this->_request.append(buffer, size); };
	void	setRequestBytesRead(int bytes_read) {this->_request_bytes_read = bytes_read; };
	void	doParseRequest();
};