#include "ServerCore.hpp"

ServerCore::ServerCore( std::vector<t_server> servers )
{
	Server server_tmp;
	for (std::vector<t_server>::iterator it = servers.begin(); it != servers.end(); ++it)
	{
		_servers.push_back(Server(&(*it)));
	}
	_max_fd = 0;
	_select_timer.tv_sec = 1;
	_select_timer.tv_usec = 0;
}

// ServerCore::ServerCore( std::vector<Server> servers )
// {
// 	_servers = servers;
// 	_max_fd = 0;
// 	_select_timer.tv_sec = 1;
// 	_select_timer.tv_usec = 0;
// }

void	ServerCore::prepareServer()
{
	list<int>	mains_fd;
	FD_ZERO(&_recv_pool);
	FD_ZERO(&_wrt_pool);
	for (std::vector<Server>::iterator it = _servers.begin(); it != _servers.end(); ++it)
	{
		std::cout << "Server [" << it->getIp() << "] :" << std::endl;
		it->setupSocket();
		mains_fd = it->getSocketFd();
		for (std::list<int>::iterator it2 = mains_fd.begin(); it2 != mains_fd.end(); ++it2)
		{
			std::cout <<  "SOCKET FD: " << *it2 << std::endl;
			if (*it2 < 0)
				continue ;
			addFdSet(*it2, this->_recv_pool);
			_servers_fd_map.insert(std::make_pair(*it2, *it));
		}
		std::cout << std::endl << std::endl;
	}
	_max_fd = _servers.back().getSocketFd().back();
}

void	ServerCore::launchServers()
{
	// fd_set	recv_tmp;
	// fd_set	wrt_tmp;
	
	while(true)
	{
		_select_timer.tv_sec = 1;
		_select_timer.tv_usec = 0;
		// recv_tmp = _recv_pool;
		// wrt_tmp = _wrt_pool;

		if (select(_max_fd + 1, &_recv_pool, &_wrt_pool, NULL, &_select_timer) < 0)
		{
			std::cout << "FAIL select" << std::endl;
		}
		else
		{
			std::cout << "TEST" << std::endl;
			for (int i = 0; i <= _max_fd; ++i)
			{
				std::cout << "FD: " << i << "| COUNT: " << _servers_fd_map.count(i) << std::endl;
				if (FD_ISSET(i, &_recv_pool) && _servers_fd_map.count(i))
				{
					newConnection(_servers_fd_map.find(i)->second, i); //pasamos el server
					std::cout << "NUEVO CLIENTE CONECTADO: " << i << std::endl;
					write(i, "HOLA QUE TAL", strlen("HOLA QUE TAL "));
				}
				else if (FD_ISSET(i, &_recv_pool) && _client_map.count(i))
				{
					readRequest(i, _client_map[i]);
					std::cout << "RECIBIENDO INFORMACION DEL CLIENTE: " << std::endl;
					std::cout << "FD TO CLR: " << i << std::endl;
				}
				else if (FD_ISSET(i, &_wrt_pool) && _client_map.count(i))
				{
					//se envian datos
					std::cout << "ENVIANDO INFORMACION AL CLIENTE: " << std::endl;
					write(i, "ESTAS CONECTADO!", strlen("ESTAS CONECTADO!"));
					FD_CLR(i, &_wrt_pool);
					close(i);
					_client_map.erase(i);
					_max_fd--;
				}
			}
		}
	}
}

void	ServerCore::newConnection(Server &server, int server_fd)
{
	struct	sockaddr_in client_addr;
	long	client_addr_size = sizeof(client_addr);
	Client	client_tmp(server);
	int		client_fd;

	client_fd = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t *)&client_addr_size);
	if (client_fd == -1)
	{
		std::cout << "FAIL acept" << std::endl;
	}
	
	addFdSet(client_fd, _recv_pool);

	if (fcntl(client_fd, F_SETFL, O_NONBLOCK) < 0)
	{
		std::cout << "FAIL fnc" << std::endl;
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
		std::cout << "No se ha leido nada" << std::endl;
	}
	else if (bytes_read < 0)
	{
		std::cout << "Ha habido un error al leer" << std::endl;
	}
	else
	{
		client.setRequest(buffer, bytes_read);
		client.setRequestBytesRead(bytes_read);
		client.doParseRequest();
		FD_CLR(fd, &_recv_pool);
		FD_SET(fd, &_wrt_pool);
	}
}

void	ServerCore::addFdSet(int fd, fd_set &set)
{
	FD_SET(fd, &set);
	if (fd > this->_max_fd)
		_max_fd = fd;
}
