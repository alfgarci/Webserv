#include "../ServerInfo.hpp"

/*
@brief Store the content of a cgi file into a cgi
@param s the line with the content
@param server_struct the server reference
*/
void	ServerInfo::store_cgi(string s, t_server &server_structs)
{
	t_CGI &CGI_node = server_structs.routes.front().cgi.front();
 
	if (check_for_keyword(s, CGI_dictionary.at(path_of_cgi)))
	{
		CGI_node.path_of_cgi = get_line_content(s);
	}
	if (check_for_keyword(s, CGI_dictionary.at(file_targets)))
	{
		CGI_node.file_targets = get_line_content(s);
	}
}
