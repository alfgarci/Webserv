#pragma once

#include "Socket.hpp"
#include "Server.hpp"
#include "../HTTPRequestParse/HTTPRequestParse.hpp"
#include "../Response/Response.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>

using std::string;

class Client
{
private:
	int					_socket_client;
	string				_request;
	Server				_host_server;
	int					_request_bytes_read;
	int					_response_code;
	bool				_parse_finish;
	bool				_isKeepAlive;
	HTTPRequestParse	_parse_request;
	string				_response;

public:

	Client();
	Client(Server serv);
	Client &operator=(const Client &other);
	~Client();

	void	setSocketClient(int fd) { this->_socket_client = fd; };
	void	setRequest(string request){ this->_request = request; };
	void	setRequest(char buffer[], int size){ this->_request.append(buffer, size); };
	void	setRequestBytesRead(int bytes_read) {this->_request_bytes_read = bytes_read; };
	string	getResponse() { return _response; };
	int		getResponseCode() { return _response_code; };
	bool	getKeepAlive() { return _isKeepAlive; };
	HTTPRequestParse	getParseRequest();

	void	doParseRequest();
	void	makeResponse();
};
