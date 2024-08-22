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
	list<t_CGI>::iterator		CGI_it;
	list<int>::iterator			port_it;
	list<t_error>::iterator		error_it;

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
		if (server_it->search_dir == DEFAULT_SEARCH_DIR)
			return (false);
		port_it = server_it->port.begin();
		while (port_it != server_it->port.end())
		{
			if (*port_it == DEFAULT_PORT_SERVER_INFO)
				return (false);
			port_it++;
		}
		if (server_it->routes.empty())
			return (false);
		route_it = server_it->routes.begin();
		while (route_it != server_it->routes.end())
		{
			CGI_it = route_it->cgi.begin();
			while (CGI_it != route_it->cgi.end())
			{
				if (CGI_it->file_targets == DEFAULT_CGI_TARGET)
					return (false);
				if (CGI_it->path_of_cgi == DEFAULT_CGI_PATH)
					return (false);
				CGI_it++;
			}
			if (route_it->http_redirections == DEFAULT_HTTP_REDI)
				return (false);
			if (route_it->search_dir == DEFAULT_SEARCH_DIR)
				route_it->search_dir = server_it->search_dir;
			route_it++;
		}
		error_it = server_it->error_page.begin();
		while (error_it != server_it->error_page.end())
		{
			if (error_it->code == DEFAULT_SERVER_ERROR_CODE)
				return (false);
			if (error_it->path == DEFAULT_SERVER_ERROR_PATH)
				return (false);	
			error_it++;
		}
		server_it++;
	}
	return (true);
}
