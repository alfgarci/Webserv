#include "../ServerInfo.hpp"

/*
@brief Verify that no camp has been left behind
@param lst the content of the file to check
@return True if the content is right, False if not.
*/
bool	ServerInfo::verify_no_defaults(list<t_server> &lst)
{
	list<t_server>::iterator	server_it;
	list<t_route>::iterator		route_it;
	list<int>::iterator			port_it;

	if (lst.empty())
		return (false);
	server_it = lst.begin();
	while (server_it != lst.end())
	{
		if (server_it->body_size_limit == DEFAULT_BODY_SIZE)
			return (false);
		if (server_it->host == DEFAULT_HOST)
			return (false);
		if (server_it->name == DEFAULT_NAME)
			return (false);
		if (server_it->port.empty())
			return (false);
		port_it = server_it->port.begin();
		while (port_it != server_it->port.end())
		{
			if (*port_it == DEFAULT_PORT)
				return (false);
			port_it++;
		}
		if (server_it->routes.empty())
			return (false);
		route_it = server_it->routes.begin();
		while (route_it != server_it->routes.end())
		{
			if (route_it->cgi == DEFAULT_CGI)
				return (false);
			if (route_it->default_file_to_answer == DEFAULT_FILE_TO_ANSWER)
				return (false);
			if (route_it->http_redirections == DEFAULT_HTTP_REDI)
				return (false);
			if (route_it->search_dir == DEFAULT_SEARCH_DIR)
				return (false);
			route_it++;
		}
		server_it++;
	}
	return (true);
}
