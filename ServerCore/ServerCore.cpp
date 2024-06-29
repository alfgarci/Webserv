#include "ServerCore.hpp"
#include <iostream>
#include <unistd.h>
#include <fcntl.h>

ServerCore::ServerCore(std::vector<ServerConfig>& configs) : _configs(configs), _max_fd(0)
{
	FD_ZERO(&_read_fds);
	FD_ZERO(&_write_fds);
	initialize();
}

ServerCore::~ServerCore()
{
	for (std::vector<ServerConfig>::iterator it = _configs.begin(); it != _configs.end(); ++it)
	{
		close(it->getFd());
	}
}

void ServerCore::initialize()
{
	for (std::vector<ServerConfig>::iterator it = _configs.begin(); it != _configs.end(); ++it)
	{
		it->setupServer();
		int server_fd = it->getFd();
		_fd_to_config_map[server_fd] = &(*it);
		FD_SET(server_fd, &_read_fds);
		if (server_fd > _max_fd)
			_max_fd = server_fd;
	}
}

void ServerCore::run()
{
	while (true)
	{
		fd_set read_fds = _read_fds;
		fd_set write_fds = _write_fds;

		int activity = select(_max_fd + 1, &read_fds, &write_fds, NULL, NULL);

		if (activity < 0)
		{
			std::cerr << "Select error" << std::endl;
			continue;
		}

		for (int fd = 0; fd <= _max_fd; ++fd)
		{
			if (FD_ISSET(fd, &read_fds))
			{
				if (_fd_to_config_map.find(fd) != _fd_to_config_map.end())
				{
					acceptNewConnection(fd);
				}
				else
				{
					handleClientData(fd);
				}
			}
		}
	}
}

void ServerCore::acceptNewConnection(int server_fd)
{
	ServerConfig* config = _fd_to_config_map[server_fd];
	int new_socket;
	struct sockaddr_in address;
	socklen_t addrlen = sizeof(address);

	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) < 0)
	{
		std::cerr << "Accept failed" << std::endl;
		return;
	}

	fcntl(new_socket, F_SETFL, O_NONBLOCK);
	_clients[new_socket] = Client(new_socket);
	FD_SET(new_socket, &_read_fds);
	if (new_socket > _max_fd)
		_max_fd = new_socket;
}

void ServerCore::handleClientData(int client_fd)
{
	Client& client = _clients[client_fd];
	char buffer[1024];
	int valread = read(client_fd, buffer, 1024);

	if (valread == 0)
	{
		closeConnection(client_fd);
	}
	else if (valread > 0)
	{
		client.appendData(buffer, valread);
		//procesar los datos del cliente, analizar la solicitud HTTP...
	}
}

void ServerCore::closeConnection(int fd)
{
	close(fd);
	FD_CLR(fd, &_read_fds);
	FD_CLR(fd, &_write_fds);
	_clients.erase(fd);
}
