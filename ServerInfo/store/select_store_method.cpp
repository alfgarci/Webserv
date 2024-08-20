# include "../ServerInfo.hpp"

/*
IMPORTANT NOTE, here i use the lst_server.front() to acces the first server struct
order the servers, in order of NEWER --> OLDER in the lst, bear that in mind.
*/
void ServerInfo::select_store_method(list<t_server> &lst_server, int indentation_level, string s)
{
	if
	(
		indentation_level == base_level
		&& ServerInfo::check_for_keyword(s, Base_dictionary.at(server))
	)
		lst_server.push_front(ServerInfo::initiate_server());
	if
	(
		indentation_level == server_level
		&& ServerInfo::check_for_keyword(s, Server_dictionary.at(route))
	)
		lst_server.front().routes.push_front(ServerInfo::initiate_route());
	if
	(
		indentation_level == route_level
		&& ServerInfo::check_for_keyword(s, Route_dictionary.at(CGI))
	)
		lst_server.front().routes.front().cgi.push_front(ServerInfo::initiate_cgi());
	if
	(
		indentation_level == server_level
		&& ServerInfo::check_for_keyword(s, Server_dictionary.at(error_page))
	)
		lst_server.front().error_page.push_front(ServerInfo::initiate_error());
	if (indentation_level == server_level)
		ServerInfo::store_server(s, lst_server.front());
	if (indentation_level == route_level)
		ServerInfo::store_route(s, lst_server.front());
	if (indentation_level == cgi_level)
		ServerInfo::store_cgi(s, lst_server.front());
	if (indentation_level == error_level)
		ServerInfo::store_error(s, lst_server.front().error_page.front());
}
