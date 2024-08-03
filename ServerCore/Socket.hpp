#pragma once

#include <string>
#include <iostream>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <cstring>
#include <iostream>
#include <string>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

class Socket
{
private:
	std::string			_ip;
	uint16_t			_port;
	bool				_binded;
	int					_fd;
	int					_domain;
	int					_type;
	int					_protocol;
	struct sockaddr_in	_sockaddr;
public:

	Socket();
	Socket(const Socket &other);
	Socket& operator=(const Socket &other);

	Socket(const std::string & ip, uint16_t port);

	void bind(void);
	void listen(void);
	void close(void);

	int getFd() const;
	struct sockaddr_in	getSockAddr() const;
	void setFd(int fd);
	void setSockAddr(const struct sockaddr_in &addr);
};
