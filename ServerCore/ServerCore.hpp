#pragma once

#include "../ServerInfo/structs.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include <vector>
#include <map>

class ServerCore
{
	private:
		std::vector<Server>		_servers;
		std::map<int, Server>	_servers_fd_map;
		std::map<int, Client>	_client_map;
		fd_set						_recv_pool;
		fd_set						_wrt_pool;
		int							_max_fd;
		struct timeval				_select_timer;
	
	public:

		struct timeval	select_timer;

		ServerCore( std::vector<Server> servers );

		void	setupServers();
		void	launchServers();

		void	addFdSet(int fd, fd_set &set);
		void	newConnection(Server &server);
		void	readRequest(int fd, Client &client);
};