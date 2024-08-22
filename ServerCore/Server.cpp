#include "Server.hpp"

Server::Server()
{
}

Server::Server(t_server *info_server)
{
	_port = info_server->port;
	_ip = info_server->host;
	_name = info_server->name;
	_client_limit_body_size = info_server->body_size_limit;
	_root = info_server->search_dir;
	_index = "index.html";
	_auto_index = false;
	_locations = info_server->routes;
	_errorPages = info_server->error_page;

	_map_fd_port.clear();
}

Server::Server(const Server &other)
{
	_main_socket = other._main_socket;
	_ip = other._ip;
	_port = other._port;
	_socket_fd = other._socket_fd;
	_client_limit_body_size = other._client_limit_body_size;
	_name = other._name;
	_root = other._root;
	_index = other._index;
	_auto_index = other._auto_index;
	_locations = other._locations;
	_errorPages = other._errorPages;
	_map_fd_port = other._map_fd_port;
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
		_name = other._name;
		_root = other._root;
		_index = other._index;
		_auto_index = other._auto_index;
		_locations = other._locations;
		_errorPages = other._errorPages;
		_map_fd_port = other._map_fd_port;
	}
	return *this;
}

void Server::setupSocket()
{
	Socket tmp;
	int fd_tmp;

	for (std::list<int>::iterator it = _port.begin(); it != _port.end(); ++it)
	{
		tmp = Socket(this->_ip, *it);
		fd_tmp = tmp.getFd();
		tmp.bind();
		tmp.listen();
		
		if (fcntl(fd_tmp, F_SETFL, O_NONBLOCK) < 0)
		{
			std::cerr << "error: fail fcntl main socket " << std::endl;
		}
		_map_fd_port[fd_tmp] = *it;
		
		_socket_fd.push_back(fd_tmp);
		_main_socket.push_back(tmp);
	}
}

int Server::getPortByFd(int fd)
{
	map<int, int>::iterator it = _map_fd_port.find(fd);
	
	// Si se encuentra, devolver el puerto asociado
	if (it != _map_fd_port.end())
	{
		return it->second;
	}
	else
	{
		return -1;
	}
}



void Server::close()
{
	for (std::list<Socket>::iterator it = _main_socket.begin(); it != _main_socket.end(); ++it)
		it->close();
}
