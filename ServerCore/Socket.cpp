#include "Socket.hpp"

Socket::Socket()
{
}

// Constructor de copia
Socket::Socket(const Socket &other)
{
	_ip = other._ip;
	_port = other._port;
	_binded = other._binded;
	_fd = other._fd;
	_domain = other._domain;
	_type = other._type;
	_protocol = other._protocol;
	_sockaddr = other._sockaddr;
}

// Sobrecarga del operador de asignación
Socket& Socket::operator=(const Socket &other)
{
	if (this != &other)
	{
		_ip = other._ip;
		_port = other._port;
		_binded = other._binded;
		_fd = other._fd;
		_domain = other._domain;
		_type = other._type;
		_protocol = other._protocol;
		_sockaddr = other._sockaddr;
	}
	return *this;
}

Socket::Socket(const std::string & ip, uint16_t port)
	: _ip(ip), _port(port), _binded(false), _fd(-1), _domain(AF_INET), _type(SOCK_STREAM), _protocol(0)
{
    this->_fd = socket(this->_domain, this->_type, this->_protocol);
    if (this->_fd <= -1)
		std::cout << "FAIL" << std::endl;

	/* Set the socket to reuse (makes it re-bindable directly after close) */
	int reuse_addr = true;
	setsockopt(this->_fd, SOL_SOCKET, SO_NOSIGPIPE, &reuse_addr, sizeof(reuse_addr));

	/* Init sockaddr */
	memset(&this->_sockaddr, 0, sizeof(this->_sockaddr));
	this->_sockaddr.sin_family = this->_domain;
	this->_sockaddr.sin_port = htons(this->_port);
	this->_sockaddr.sin_addr.s_addr = inet_addr(this->_ip.c_str());
}

void Socket::bind(void)
{
	int bind_status;
	if (this->_binded)
		return;
	bind_status = ::bind(this->_fd, reinterpret_cast< const struct sockaddr * >(&this->_sockaddr), sizeof(this->_sockaddr));
	if (bind_status <= -1)
        std::cout << "FAIL" << std::endl;
	this->_binded = true;
}

void Socket::listen(void)
{
	if (!this->_binded)
        std::cout << "FAIL" << std::endl;
	if (::listen(this->_fd, 128) <= -1)
        std::cout << "FAIL" << std::endl;
	std::cout << "Listening:\t" << this->_fd << "" << std::endl;
}

void Socket::close(void)
{
	if (this->_fd >= -1)
		::close(this->_fd);
}

int Socket::getFd() const
{
	return this->_fd;
}

struct sockaddr_in Socket::getSockAddr() const
{
	return this->_sockaddr;
}

void Socket::setFd(int fd)
{
	this->_fd = fd;
}

void Socket::setSockAddr(const struct sockaddr_in &addr)
{
	this->_sockaddr = addr;
}