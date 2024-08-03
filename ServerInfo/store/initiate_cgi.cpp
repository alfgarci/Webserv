#include "../ServerInfo.hpp"

/*
@brief Sets default values to a CGI
*/
t_CGI	ServerInfo::initiate_cgi()
{
	t_CGI	cgi_node;

	cgi_node.path_of_cgi = DEFAULT_CGI_PATH;
	cgi_node.file_targets = DEFAULT_CGI_TARGET;
	return (cgi_node);
}
