#pragma once

#include "Socket.hpp"
#include "Server.hpp"


class Client
{
private:
	int			_socket_client;
	std::string	_request;
	int			_request_bytes_read;

public:

	Client();
	Client &operator=(const Client &other);
	~Client();

	void	setSocketClient(int fd) { this->_socket_client = fd; };
	void	setRequest(std::string request){ this->_request = request; };
	void	setRequest(char buffer[], int size){ this->_request.append(buffer, size); };
	void	setRequestBytesRead(int bytes_read) {this->_request_bytes_read = bytes_read; };
};