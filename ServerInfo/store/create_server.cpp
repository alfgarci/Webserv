#include "../ServerInfo.hpp"

/*
@brief generate a t_server struct in heap
*/
t_server	*ServerInfo::create_server(void)
{
	t_server	*server_struct;

	server_struct = NULL;
	server_struct = new t_server;
	if (!server_struct)
		throw std::logic_error(ERROR_NOT_ENOUGH_MEMORY);
	return (server_struct);
}
