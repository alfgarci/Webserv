#include "../ServerInfo.hpp"

void	ServerInfo::store_route(string s, t_server &server_struct)
{
	t_route	&current_route = server_struct.routes.front();

	if (check_for_keyword(s, Route_dictionary.at(accepted_http_methods)))
	{
		current_route.accepted_http_methods.push_back(get_line_content(s));
	}
	if (check_for_keyword(s, Route_dictionary.at(http_redirections)))
	{
		current_route.http_redirections = get_line_content(s);
	}
	if (check_for_keyword(s, Route_dictionary.at(search_dir)))
	{
		current_route.search_dir = get_line_content(s);
	}
	if (check_for_keyword(s, Route_dictionary.at(toogle_dir_listen)))
	{
		if (get_line_content(s) == TRUE_STRING)
			current_route.dir_to_listen = true;
		else if (get_line_content(s) == FALSE_STRING)
			current_route.dir_to_listen = false;
		else
			throw std::logic_error(BAD_BOOLEAN_STRING);
	}
	if (check_for_keyword(s, Route_dictionary.at(default_file_to_answer)))
	{
		current_route.default_file_to_answer = get_line_content(s);
	}
	if (check_for_keyword(s, Route_dictionary.at(CGI)))
	{
		current_route.default_file_to_answer = get_line_content(s);
	}
}
