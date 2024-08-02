#pragma once

#include "../ServerInfo/structs.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include <vector>
#include <map>
#include <fstream> 

class ServerCore
{
	private:
		std::vector<Server>		_servers;
		std::map<int, Server>	_servers_fd_map;
		std::map<int, Client>	_client_map;
		fd_set					_recv_pool;
		fd_set					_wrt_pool;
		int						_max_fd;
		struct timeval			_select_timer;
	
	public:
	
		struct timeval	select_timer;

		ServerCore( std::list<t_server> servers );

		void	prepareServer();
		void	launchServers();

		void	addFdSet(int fd, fd_set &set);
		void	eraseFdSet(int fd, fd_set &set);
		
		void	newConnection(Server &server, int server_fd);
		void	readRequest(int fd, Client &client);
		void	sendResponse(int fd, Client &client);

		void 	sendErrorResponse(int fd, int errorCode, const std::string& errorPage);

		void	closeConection(int fd);
};
