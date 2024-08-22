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

void printServerInfo(Server server)
{
    std::ostringstream oss;

    string name = server.getName();
    string ip = server.getIp();

    oss << "> Server [" << name << "][" << ip << "] ready listening on ports {";

    list<int> ports = server.getPorts();
    for (list<int>::iterator it = ports.begin(); it != ports.end(); ++it)
    {
        oss << *it;
        if (it != --ports.end())
            oss << ", ";
    }
    oss << "}";

    std::cout << oss.str() << std::endl;
}

void	ServerCore::prepareServer()
{
	list<int>	mains_fd;
	_max_fd = 0;
	FD_ZERO(&_recv_pool);
	FD_ZERO(&_wrt_pool);
	for (vector<Server>::iterator it = _servers.begin(); it != _servers.end(); ++it)
	{
		it->setupSocket();
		mains_fd = it->getSocketFd();
		for (list<int>::iterator it2 = mains_fd.begin(); it2 != mains_fd.end(); ++it2)
		{
			if (*it2 < 0)
				continue ;
			addFdSet(*it2, this->_recv_pool);
			_servers_fd_map.insert(std::make_pair(*it2, *it));
		}
		printServerInfo(*it);
	}
	_max_fd = _servers.back().getSocketFd().back();
}

void	ServerCore::launchServers()
{
	fd_set	recv_tmp;
	fd_set	wrt_tmp;
	
	while(true)
	{
		recv_tmp = _recv_pool;
		wrt_tmp = _wrt_pool;

		if (select(_max_fd + 1, &recv_tmp, &wrt_tmp, NULL, &_select_timer) < 0)
		{
			std::cerr << "error: fail select" << std::endl;
		}
		else
		{
			for (int i = 0; i <= _max_fd; ++i)
			{
				if (FD_ISSET(i, &recv_tmp) && _servers_fd_map.count(i))
				{
					newConnection(_servers_fd_map.find(i)->second, i); //pasamos el server
					std::cout << "> New client connected at socket: " << i << std::endl;
				}
				else if (FD_ISSET(i, &recv_tmp) && _client_map.count(i))
				{
					readRequest(i, _client_map[i]);
					if (_client_map[i].getCgiState() == CGIPendingWrite)
					{
						Cgi Cgi = _client_map[i].getCgi();
                    	addFdSet(Cgi.pipeIn[1], _wrt_pool);
					}
				}
				else if (FD_ISSET(i, &wrt_tmp) && _client_map.count(i))
				{
					Cgi Cgi = _client_map[i].getCgi();
					int stateCgi = _client_map[i].getCgiState();

					if (stateCgi == CGIPendingWrite && FD_ISSET(Cgi.pipeIn[1], &wrt_tmp))
					{
						writeCGI(_client_map[i], Cgi);
						_client_map[i].setCgiState(CGIPendingRead);
						eraseFdSet(Cgi.pipeIn[1], _wrt_pool);
						addFdSet(Cgi.pipeOut[0], _recv_pool);
					}
					else if (stateCgi == CGIPendingRead && FD_ISSET(Cgi.pipeOut[0], &recv_tmp))
					{
						readCGI(_client_map[i], Cgi);
						eraseFdSet(Cgi.pipeOut[0], _recv_pool);
						_client_map[i].setCgiState(CGIDone);
					}
					else if ((stateCgi == NoCGI || stateCgi == CGIDone) && FD_ISSET(i, &wrt_tmp))
					{
						sendResponse(i, _client_map[i]);
					}
				}
			}
		}
	}
}

void	ServerCore::newConnection(Server &server, int server_fd)
{
	struct	sockaddr_in client_addr;
	long	client_addr_size = sizeof(client_addr);
	int		portNewCliente = server.getPortByFd(server_fd);
	Client	client_tmp(server, portNewCliente);
	int		client_fd;

	client_fd = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t *)&client_addr_size);
	if (client_fd == -1)
	{
		std::cerr << "error: fail accept" << std::endl;
	}
	
	addFdSet(client_fd, _recv_pool);

	if (fcntl(client_fd, F_SETFL, O_NONBLOCK) < 0)
	{
		std::cerr << "error: fail fcntl" << std::endl;
	}
	client_tmp.setSocketClient(client_fd);
	_client_map.insert(std::make_pair(client_fd, client_tmp));
}

void	ServerCore::readRequest(int fd, Client &client)
{
	char			buffer[BUFFER_SIZE];
	vector<char>	data;
	data.clear();
	
	while (true)
	{
		memset(buffer, 0, BUFFER_SIZE);

		ssize_t bytesRead = recv(fd, buffer, BUFFER_SIZE, 0);

		if (bytesRead < 0)
		{
			break ;
		}
		else if (bytesRead == 0)
		{
			break ;
		}
		data.insert(data.end(), buffer, buffer + bytesRead);
	}
	std::cout << "> Request received from socket: "<< fd << endl;
	
	//analizamos solicitud
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
	int		codeResponse = client.getResponseCode();
	int	bytes_sent = write(fd, response.c_str(), response.length());

	if (bytes_sent < 0)
	{
		std::cerr << "error: fail to send response" << std::endl;
		closeConection(fd);
	}
	else
	{
		std::cout << "> Response sent to socket: "<< fd << " whit code: " << codeResponse << endl;
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

void	ServerCore::writeCGI(Client &client, Cgi &Cgi)
{
	string	body = client.getHTTPRequest().getField(HTTPRequestParse::BODY);
	ssize_t	bytes_written = write(Cgi.pipeIn[1], body.c_str(), body.size());

	if (bytes_written < 0)
	{
		std::cerr << "error: failed to write to Cgi pipe" << endl;
		closeConection(client.getSocketClient());
		return ;
	}

	close(Cgi.pipeIn[1]);
	client.setCgiState(CGIPendingRead);
}

void	ServerCore::readCGI(Client &client, Cgi &Cgi)
{
	char	buffer[BUFFER_SIZE];
	string	response;
	ssize_t	bytes_read;

	while((bytes_read = read(Cgi.pipeOut[0], buffer, sizeof(buffer))) > 0)
	{
		response.append(buffer, bytes_read);
	}


	if (bytes_read < 0)
	{
		std::cerr << "error: failed to read from Cgi pipe" << endl;
		closeConection(client.getSocketClient());
		return;
	}

	client.setResponse(response);
	client.setCgiState(CGIDone);

	close(Cgi.pipeOut[0]);
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
