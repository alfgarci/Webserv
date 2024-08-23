#pragma once

#include "Socket.hpp"
#include "Server.hpp"
#include "../HTTPRequestParse/HTTPRequestParse.hpp"
#include "../Response/Response.hpp"
#include "../Cgi/Cgi.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>

using std::string;

enum CGIState
{ 
	NoCGI,
	CGIPendingWrite,
	CGIPendingRead,
	CGIDone 
};

class Client
{
private:
	int					_socket_client;
	string				_request;
	Server				_host_server;
	int					_request_bytes_read;
	time_t				_last_message;
	int					_response_code;
	bool				_parse_finish;
	bool				_isKeepAlive;
	HTTPRequestParse	_parse_request;
	string				_response;
	int					_port;
	Response			_resObj;
		
	Cgi					_cgi;
	bool				_isCgi;
	int					_stateCgi;

public:

	Client();
	Client(Server serv, int port);
	Client &operator=(const Client &other);
	~Client();

	void				setSocketClient(int fd) { this->_socket_client = fd; };
	void				setRequest(string request){ this->_request = request; };
	void				setRequest(char buffer[], int size){ this->_request.append(buffer, size); };
	void				setRequestBytesRead(int bytes_read) {this->_request_bytes_read = bytes_read; };
	void				setCgiState(int state){ this->_stateCgi = state; };
	void				setResponse(string response){ this->_response = response; };
	void				setResponseCode(int code){ this->_response_code = code; };
	void				setLastMessage(time_t time){ this->_last_message = time; };

	int					getSocketClient(){ return this->_socket_client; };
	string				getResponse(){ return this->_response; };
	int					getResponseCode(){ return this->_response_code; };
	bool				getKeepAlive(){ return this->_isKeepAlive; };
	Response			getResponseObj(){ return this->_resObj; };
	HTTPRequestParse	getHTTPRequest(){ return this->_parse_request; };
	int					getCgiState(){ return this->_stateCgi; };
	Cgi					getCgi(){ return this->_cgi; };
	time_t				getLastMessage(){ return this->_last_message; };

	void				resetTimer(){ _last_message = time(NULL); };

	size_t 				extractContentLength(const std::string& requestData);

	void				doParseRequest();
	void				makeResponse();

	void 				reset();

	bool				isRequestComplete(const std::vector<char>& data);
};
