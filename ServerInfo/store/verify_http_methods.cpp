#include "../ServerInfo.hpp"

/*
@brief Verify if the http methods are contain in the list of accepted methods
@param lst the servers to verify
@return True if they are correct, false if not
*/
bool	ServerInfo::verify_http_methods(list<t_server> &lst)
{
	list<t_server>::iterator	server_it;
	list<t_route>::iterator		route_it;
	list<string>::iterator		it;
	bool						get_flag;
	bool						post_flag;
	bool						delete_flag;

	get_flag = false;
	post_flag = false;
	delete_flag = false;
	server_it = lst.begin();
	while (server_it != lst.end())
	{
		route_it = server_it->routes.begin();
		while (route_it != server_it->routes.end())
		{
			if (route_it->accepted_http_methods.empty())
				return (true);
			it = route_it->accepted_http_methods.begin();
			while (it != route_it->accepted_http_methods.end())
			{
				if
				(
					*it != DEFAULT_METHOD_GET
					&& *it != DEFAULT_METHOD_POST
					&& *it != DEFAULT_METHOD_DELETE
				)
					return (false);
				if (*it == DEFAULT_METHOD_GET && get_flag)
					return (false);
				else if (*it == DEFAULT_METHOD_GET)
					get_flag = true;
				if (*it == DEFAULT_METHOD_POST && post_flag)
					return (false);
				else if (*it == DEFAULT_METHOD_POST)
					post_flag = true;
				if (*it == DEFAULT_METHOD_DELETE && delete_flag)
					return (false);
				else if (*it == DEFAULT_METHOD_DELETE)
					delete_flag = true;
				it++;
			}
			get_flag = false;
			post_flag = false;
			delete_flag = false;
			route_it++;
		}
		get_flag = false;
		post_flag = false;
		delete_flag = false;
		server_it++;
	}
	return (true);
}
