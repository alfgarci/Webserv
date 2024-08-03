#pragma once

#include "Socket.hpp"
#include "Server.hpp"
#include "../HTTPRequestParse/HTTPRequestParse.hpp"
#include "../HTTPRequestCreator/HTTPRequestCreator.hpp"
#include "../get_request/get_request.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>

class Client
{
private:
	int			_socket_client;
	std::string	_request;
	Server		_host_server;
	int			_request_bytes_read;
	bool		_parse_finish;

	HTTPRequestParse	_parse_request;
	std::string			_response;

public:

	Client();
	Client(Server serv);
	Client &operator=(const Client &other);
	~Client();

	void	setSocketClient(int fd) { this->_socket_client = fd; };
	void	setRequest(std::string request){ this->_request = request; };
	void	setRequest(char buffer[], int size){ this->_request.append(buffer, size); };
	void	setRequestBytesRead(int bytes_read) {this->_request_bytes_read = bytes_read; };
	std::string	getResponse() { return _response; };
	HTTPRequestParse	getParseRequest();

	void	doParseRequest();
	void	makeResponse();
};
