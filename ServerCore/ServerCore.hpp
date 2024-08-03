#pragma once

#include "../ServerInfo/structs.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "../libs/to_string.hpp"

using std::string;
using std::map;
using std::list;
using std::vector;

class ServerCore
{
	private:
		vector<Server>		_servers;
		map<int, Server>	_servers_fd_map;
		map<int, Client>	_client_map;
		fd_set					_recv_pool;
		fd_set					_wrt_pool;
		int						_max_fd;
		struct timeval			_select_timer;
	
	public:
	
		struct timeval	select_timer;

		ServerCore( list<t_server> servers );

		void	prepareServer();
		void	launchServers();

		void	addFdSet(int fd, fd_set &set);
		void	eraseFdSet(int fd, fd_set &set);
		
		void	newConnection(Server &server, int server_fd);
		void	readRequest(int fd, Client &client);
		void	sendResponse(int fd, Client &client);

		void 	sendErrorResponse(int fd, int errorCode, const string& errorPage);

		void	closeConection(int fd);
};
