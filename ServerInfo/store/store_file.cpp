#include "../ServerInfo.hpp"

static void change_indenation_level(int &indentation_level, string s)
{
	if (s.empty())
	{
		if (indentation_level != base_level)
		{
			if (indentation_level == server_level)
				indentation_level = base_level;
			if (indentation_level == route_level)
				indentation_level = server_level;
			if (indentation_level == cgi_level)
				indentation_level = route_level;
			if (indentation_level == error_level)
				indentation_level = server_level;
		}
	}
	else
	{
		if (ServerInfo::check_for_indentation_token(s))
		{
			if (ServerInfo::check_for_keyword(s, Base_dictionary.at(server)))
				indentation_level = server_level;
			if (ServerInfo::check_for_keyword(s, Server_dictionary.at(route)))
				indentation_level = route_level;
			if (ServerInfo::check_for_keyword(s, Route_dictionary.at(CGI)))
				indentation_level = cgi_level;
			if (ServerInfo::check_for_keyword(s, Server_dictionary.at(error_page)))
				indentation_level = error_level;
		}
	}
}

static void enforce_syntax(string path)
{
	std::fstream	file;
	int				line;
	int				indentation_level;
	string			s;

	line = 1;
	indentation_level = base_level;
	file.open(path.c_str(), std::fstream::in);
	if (!file.is_open())
		throw std::logic_error(ERROR_CANT_OPEN_FILE);
	while (std::getline(file, s))
	{
		if (!s.empty())
			ServerInfo::check_syntax(s, indentation_level, line);
		change_indenation_level(indentation_level, s);
		line++;
	}
	file.close();
}

static void start_store_file (std::fstream &file, int &indentation_level, string path)
{
	indentation_level = base_level;
	file.open(path.c_str(), std::fstream::in);
	if (!file.is_open())
		throw std::logic_error(ERROR_CANT_OPEN_FILE);
	enforce_syntax(path);
}

/*
@brief Store the given file, into a list of list<t_server>, would throw errors if at any point
the requirements fail, if the file dosent comply, etc
@param path the path to the file
@return all the server configs that have been founded in the file
*/
list<t_server>	ServerInfo::store_file(string path)
{
	list<t_server>		lst_server;
	std::fstream		file;
	string				s;
	int					indentation_level;

	start_store_file(file, indentation_level, path);
	while (std::getline(file, s))
	{
		if (!s.empty())
			select_store_method(lst_server, indentation_level, s);
		change_indenation_level(indentation_level, s);
	}
	file.close();
	if (!verify_no_defaults(lst_server))
		throw (std::logic_error(ERROR_CAMP_UNINITIALIZE));
	if (!verify_http_methods(lst_server))
		throw (std::logic_error(ERROR_DUPLICATED_HTTP_METHODS));
	return (lst_server);
}
