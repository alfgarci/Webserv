#include "ServerCore.hpp"

ServerCore::ServerCore( list<t_server> servers )
{
    Server server_tmp;
    for (list<t_server>::iterator it = servers.begin(); it != servers.end(); ++it)
    {
        _servers.push_back(Server(&(*it)));
    }
    _max_fd = 0;
    _select_timer.tv_sec = 1;
    _select_timer.tv_usec = 0;
}

void	ServerCore::prepareServer()
{
	list<int>	mains_fd;
	_max_fd = 0;
	FD_ZERO(&_recv_pool);
	FD_ZERO(&_wrt_pool);
	for (vector<Server>::iterator it = _servers.begin(); it != _servers.end(); ++it)
	{
		std::cout << "Server [" << it->getIp() << "] :" << std::endl;
		it->setupSocket();
		mains_fd = it->getSocketFd();
		for (list<int>::iterator it2 = mains_fd.begin(); it2 != mains_fd.end(); ++it2)
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
	fd_set	recv_tmp;
	fd_set	wrt_tmp;
	
	while(true)
	{
		_select_timer.tv_sec = 1;
		_select_timer.tv_usec = 0;
		recv_tmp = _recv_pool;
		wrt_tmp = _wrt_pool;

		if (select(_max_fd + 1, &recv_tmp, &wrt_tmp, NULL, &_select_timer) < 0)
		{
			std::cout << "FAIL select" << std::endl;
		}
		else
		{
			for (int i = 0; i <= _max_fd; ++i)
			{
				if (FD_ISSET(i, &recv_tmp) && _servers_fd_map.count(i))
				{
					newConnection(_servers_fd_map.find(i)->second, i); //pasamos el server
					std::cout << "New client connected: " << i << std::endl;
				}
				else if (FD_ISSET(i, &recv_tmp) && _client_map.count(i))
				{
					readRequest(i, _client_map[i]);
				}
				else if (FD_ISSET(i, &wrt_tmp) && _client_map.count(i))
				{
					sendResponse(i, _client_map[i]);
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
	char			buffer[BUFFER_SIZE];
	vector<char>	data;
	
	while (true)
	{
		memset(buffer, 0, BUFFER_SIZE);

		ssize_t bytesRead = recv(fd, buffer, BUFFER_SIZE, 0);

		if (bytesRead < 0)
		{
			std::cout << "Ha habido un error al leer" << std::endl;
			break ;
		}
		else if (bytesRead == 0)
		{
			std::cout << "No se ha leido nada" << std::endl;
			break ;
		}
		data.insert(data.end(), buffer, buffer + bytesRead);
	}
	client.setRequest(std::string(data.begin(), data.end()));
	client.setRequestBytesRead(data.size());
	client.doParseRequest();
	eraseFdSet(fd, _recv_pool);
	addFdSet(fd, _wrt_pool);
	data.clear();
}


void	ServerCore::sendResponse(int fd, Client &client)
{
	string response = client.getResponse();
	int	bytes_sent = write(fd, response.c_str(), response.length());

	if (bytes_sent < 0)
	{
		std::cout << "ERROR AL ENVIAR" << std::endl;
		closeConection(fd);
	}
	else
	{
		std::cout << "Socket: "<< fd << endl;
		std::cout << "STRING enviada al socket: "<< response << endl;
		if (client.getKeepAlive() == false || client.getResponseCode())
		{
			closeConection(fd);
		}
		else
		{
			eraseFdSet(fd, _wrt_pool);
			addFdSet(fd, _recv_pool);
		}
	}
}

void	ServerCore::addFdSet(int fd, fd_set &set)
{
	FD_SET(fd, &set);
	if (fd > this->_max_fd)
		_max_fd = fd;
}

void	ServerCore::eraseFdSet(int fd, fd_set &set)
{
	FD_CLR(fd, &set);
	if (fd == this->_max_fd)
		_max_fd--;
}

void	ServerCore::closeConection(int fd)
{
	if (FD_ISSET(fd, &_recv_pool))
		eraseFdSet(fd, _recv_pool);
	if (FD_ISSET(fd, &_wrt_pool))
		eraseFdSet(fd, _wrt_pool);
	
	close(fd);
	_client_map.erase(fd);
}
