#include "../ServerInfo.hpp"

void	ServerInfo::store_server(string s, t_server &server_struct)
{
	if (check_for_keyword(s, Server_dictionary.at(port)))
	{
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
		server_struct.body_size_limit = atoi(get_line_content(s).c_str());
	}
}
