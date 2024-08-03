#include "../ServerInfo.hpp"

/*
@brief generate t_route struct
*/
t_route	ServerInfo::initiate_route()
{
	t_route	route_struct;

	route_struct.default_file_to_answer = DEFAULT_FILE_TO_ANSWER;
	route_struct.dir_to_listen = DEFAULT_DIR_TO_LISTEN;
	route_struct.http_redirections = DEFAULT_HTTP_REDI;
	route_struct.search_dir = DEFAULT_SEARCH_DIR;
	return (route_struct);
}
