#include "../ServerInfo.hpp"

/*
@brief generate a t_server struct
*/
t_server	ServerInfo::initiate_server(void)
{
	t_server	server_struct;

	server_struct.body_size_limit = DEFAULT_BODY_SIZE;
	server_struct.host = DEFAULT_HOST;
	server_struct.name = DEFAULT_NAME;
	server_struct.search_dir = DEFAULT_DIR_TO_LISTEN;
	return (server_struct);
}
