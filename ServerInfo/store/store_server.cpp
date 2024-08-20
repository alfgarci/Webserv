#include "../ServerInfo.hpp"

void	ServerInfo::store_server(string s, t_server &server_struct)
{
	if (check_for_keyword(s, Server_dictionary.at(port)))
	{
		if (check_overflow(get_line_content(s)))
			throw(std::logic_error(ERROR_OVERFLOW_GENERIC));
		server_struct.port.push_back(atoi(get_line_content(s).c_str()));
	}
	if (check_for_keyword(s, Server_dictionary.at(host)))
	{
		server_struct.host = store_host(s);
	}
	if (check_for_keyword(s, Server_dictionary.at(server_name)))
	{
		server_struct.name = get_line_content(s);
	}
	if (check_for_keyword(s, Server_dictionary.at(body_limit)))
	{
		if (check_overflow(get_line_content(s)))
			throw(std::logic_error(ERROR_OVERFLOW_GENERIC));
		server_struct.body_size_limit = atoi(get_line_content(s).c_str());
	}
	if (check_for_keyword(s, Server_dictionary.at(search_dir_server)))
	{
		server_struct.search_dir = get_line_content(s);
	}
}
