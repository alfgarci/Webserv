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
				indentation_level = route_level;
		}
	}
	else
	{
		if (ServerInfo::check_for_indentation_token(s))
		{
			if (ServerInfo::check_for_keyword(s, Base_dictionary.at(server)))
				indentation_level = server_level;
			if (ServerInfo::check_for_keyword(s, Server_dictionary.at(route)))
				indentation_level =  route_level;
		}
	}
}

static void enforce_syntax(string path)
{
	std::fstream	file;
	int				line;
	int				indentation_level;
	string			s;

	line = 0;
	indentation_level = base_level;
	file.open(path.c_str(), std::fstream::in);
	if (!file.is_open())
		throw std::logic_error(ERROR_CANT_OPEN_FILE);
	while (std::getline(file, s))
	{
		if (!s.empty())
			ServerInfo::check_syntax(s, indentation_level, line);
		else
			change_indenation_level(indentation_level, s);
		line++;
	}
	file.close();
}

static void start_store_file (std::fstream &file, int &indentation_level, t_server **server, string path)
{
	indentation_level = base_level;
	server = NULL;
	file.open(path.c_str(), std::fstream::in);
	if (!file.is_open())
		throw std::logic_error(ERROR_CANT_OPEN_FILE);
	enforce_syntax(path);
}

static void select_store_method(t_server *server_struct, int indentation_level, string s)
{
	if
	(
		indentation_level == base_level
		&& ServerInfo::check_for_keyword(s, Base_dictionary.at(server))
	)
		return ;
	if
	(
		indentation_level == server_level
		&& ServerInfo::check_for_keyword(s, Server_dictionary.at(route))
	)
		server_struct->routes.push_front(ServerInfo::create_route());
	if (indentation_level == base_level)
		server_struct = ServerInfo::create_server();
	if (indentation_level == server_level)
		ServerInfo::store_server(s, server_struct);
	if (indentation_level == route_level)
		ServerInfo::store_route(s, server_struct);
}

/*
@brief Store the given file, into a list of list<t_server>, would throw errors if at any point
the requirements fail, if the file dosent compliy, etc
@param path the path to the file
@return all the server configs that have been founded in the file
*/
list<t_server>	ServerInfo::store_file(string path)
{
	list<t_server>		lst_server;
	t_server			*server_struct;
	std::fstream		file;
	string				s;
	int					indentation_level;

	start_store_file(file, indentation_level, &server_struct, path);
	while (std::getline(file, s))
	{
		if (!s.empty())
			select_store_method(server_struct, indentation_level, s);
		change_indenation_level(indentation_level, s);
	}
	file.close();
	lst_server.front().
	return (lst_server);
}
