#ifndef STRUCTS_H
# define STRUCTS_H

#pragma once

#include <list>
#include <string>

using std::string;
using std::list;

typedef	struct	s_CGI
{
	string	file_targets;
	string	path_of_cgi;
}				t_CGI;

typedef	struct	s_route
{
	list<string>		accepted_http_methods;
	string				http_redirections;
	string				search_dir;
	string				default_file_to_answer;
	bool				dir_to_listen;
	list<t_CGI>			cgi;
}				t_route;

typedef struct	s_server
{
	list<int>			port;
	string				host;
	string				name;
	unsigned int		body_size_limit;
	list<t_route>		routes;
}				t_server;

#endif
