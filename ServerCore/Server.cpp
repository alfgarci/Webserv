#include "Server.hpp"

Server::Server()
{
}

Server::Server(t_server *info_server)
{
	_port = info_server->port;
	_ip = info_server->host;
	_server_name = info_server->name;
	_client_limit_body_size = info_server->body_size_limit;
	_root = "/";
	_index = "index.html";
	_auto_index = false;
}

Server::Server(const Server &other)
{
	_main_socket = other._main_socket;
	_ip = other._ip;
	_port = other._port;
	_socket_fd = other._socket_fd;
	_client_limit_body_size = other._client_limit_body_size;
	_server_name = other._server_name;
	_root = other._root;
	_index = other._index;
	_auto_index = other._auto_index;
	_error_pages = other._error_pages;
	current_socket = other.current_socket;
	ready_socket = other.ready_socket;
}

Server& Server::operator=(const Server &other)
{
	if (this != &other)
	{
		_main_socket = other._main_socket;
		_ip = other._ip;
		_port = other._port;
		_socket_fd = other._socket_fd;
		_client_limit_body_size = other._client_limit_body_size;
		_server_name = other._server_name;
		_root = other._root;
		_index = other._index;
		_auto_index = other._auto_index;
		_error_pages = other._error_pages;
		current_socket = other.current_socket;
		ready_socket = other.ready_socket;
	}
	return *this;
}

void	Server::setupSocket()
{
	_main_socket = Socket(this->_ip, this->_port);
	this->_socket_fd = _main_socket.getFd();
	_main_socket.bind();
}

void	Server::startListenNonBlock()
{
	_main_socket.listen();
	if (fcntl(_socket_fd, F_SETFL, O_NONBLOCK) < 0)
	{
		std::cout << "FAIL" << std::endl;
	}
}

void Server::close()
{
	this->_main_socket.close();
}