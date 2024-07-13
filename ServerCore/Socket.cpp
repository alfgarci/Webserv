#include "Socket.hpp"

Socket::Socket(const std::string & ip, uint16_t port)
	: ip(ip), port(port), binded(false), fd(-1), domain(AF_INET), type(SOCK_STREAM), protocol(0)
{
    this->fd = socket(this->domain, this->type, this->protocol);
    if (this->fd <= -1)
		std::cout << "FAIL" << std::endl;

	/* Set the socket to reuse (makes it re-bindable directly after close) */
	int reuse_addr = true;
	setsockopt(this->fd, SOL_SOCKET, SO_NOSIGPIPE, &reuse_addr, sizeof(reuse_addr));

	/* Init sockaddr */
	memset(&this->sockaddr, 0, sizeof(this->sockaddr));
	this->sockaddr.sin_family = this->domain;
	this->sockaddr.sin_port = htons(this->port);
	this->sockaddr.sin_addr.s_addr = inet_addr(this->ip.c_str());
}

void Socket::bind(void)
{
	int bind_status;
	if (this->binded)
		return;
	bind_status = ::bind(this->fd, reinterpret_cast< const struct sockaddr * >(&this->sockaddr), sizeof(this->sockaddr));
	if (bind_status <= -1)
        std::cout << "FAIL" << std::endl;
	this->binded = true;
}

void Socket::listen(void)
{
	if (!this->binded)
        std::cout << "FAIL" << std::endl;
	if (::listen(this->fd, 128) <= -1)
        std::cout << "FAIL" << std::endl;
	std::cout << "Listening:\t" << this->fd << "" << std::endl;
}

void Socket::close(void)
{
	if (this->fd >= -1)
		::close(this->fd);
}

int Socket::getFd()
{
	return this->fd;
}