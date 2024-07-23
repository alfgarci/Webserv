#include "ServerCore.hpp"

ServerCore::ServerCore( std::vector<Server> servers )
{
	_servers = servers;
	_max_fd = 0;
	_select_timer.tv_sec = 1;
	_select_timer.tv_usec = 0;

	FD_ZERO(&_recv_pool);
	FD_ZERO(&_wrt_pool);
	for (std::vector<Server>::iterator it = _servers.begin(); it != _servers.end(); ++it)
	{
		it->startListenNonBlock();
		addFdSet(it->getSocketFd(), this->_recv_pool);
		_servers_fd_map.insert(std::make_pair(it->getSocketFd(), *it));
	}
	_max_fd = _servers.back().getSocketFd();
}

void	ServerCore::setupServers()
{
	for (std::vector<Server>::iterator it = _servers.begin(); it != _servers.end(); ++it)
	{
		it->setupSocket();
	}
}

void	ServerCore::launchServers()
{
	fd_set	recv_tmp;
	fd_set	wrt_tmp;
	
	while(1)
	{
		_select_timer.tv_sec = 1;
		_select_timer.tv_usec = 0;
		recv_tmp = _recv_pool;
		wrt_tmp = _wrt_pool;

		if (select(_max_fd + 1, &recv_tmp, &wrt_tmp, NULL, &_select_timer) < 0 )
		{
			std::cout << "FAIL" << std::endl;
		}
		for (int i = 0; i <= _max_fd; ++i)
		{
			if (FD_ISSET(i, &_recv_pool) && _servers_fd_map.count(i))
			{
				newConnection(_servers_fd_map.find(i)->second); //pasamos el server
			}
			else if (FD_ISSET(i, &_recv_pool) && _client_map.count(i))
			{
				readRequest(i, _client_map[i]);
			}
			else //else if
			{
				//se envian datos
			}
		}
	}
}

void	ServerCore::newConnection(Server &server)
{
	struct	sockaddr_in client_addr;
	long	client_addr_size = sizeof(client_addr);
	Client	client_tmp;
	int		client_fd;

	client_fd = accept(server.getSocketFd(), (struct sockaddr *)&client_addr, (socklen_t *)&client_addr_size);
	if (client_fd == -1)
	{
		std::cout << "FAIL" << std::endl;
	}
	
	addFdSet(client_fd, _recv_pool);

	if (fcntl(client_fd, F_SETFL, O_NONBLOCK) < 0)
	{
		std::cout << "FAIL" << std::endl;
	}
	client_tmp.setSocketClient(client_fd);
	_client_map.insert(std::make_pair(client_fd, client_tmp));
}

void	ServerCore::readRequest(int fd, Client &client)
{
	char	buffer[50000];
	int		bytes_read = recv(fd, buffer, sizeof(buffer), 0);

	if (bytes_read == 0)
	{
		std::cout << "nada leido" << std::endl;
	}
	else if (bytes_read < 0)
	{
		std::cout << "error al leer" << std::endl;
	}
	else
	{
		client.setRequest(buffer, bytes_read);
		client.setRequestBytesRead(bytes_read);
	}

	//aqui no seeeeeee, se mandara respuesta

}

void	ServerCore::addFdSet(int fd, fd_set &set)
{
	FD_SET(fd, &set);
	if (fd > this->_max_fd)
		_max_fd = fd;
}