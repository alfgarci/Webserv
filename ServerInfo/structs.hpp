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

typedef struct 	s_error
{
	unsigned int	code;
	string			path;
}				t_error;

typedef	struct	s_route
{
	list<string>		accepted_http_methods;
	string				http_redirections;
	string				search_dir; //equal to root
	string				default_file_to_answer; //equal to index
	bool				dir_to_listen; //equal to autoindex
	list<t_CGI>			cgi;
	list<t_error>		error_page;
}				t_route;

typedef struct	s_server
{
	list<int>			port;
	string				host;
	string				name;
	unsigned int		body_size_limit;
	string				search_dir; //equal to root
	list<t_route>		routes;
	list<t_error>		error_page;
}				t_server;

#endif
