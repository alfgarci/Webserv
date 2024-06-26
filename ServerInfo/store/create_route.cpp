#include "../ServerInfo.hpp"

/*
@brief generate t_route struct in heap
*/
t_route	*ServerInfo::create_route()
{
	t_route	*route_struct;

	route_struct = NULL;
	route_struct = new t_route;
	if (!route_struct)
		throw std::logic_error(ERROR_NOT_ENOUGH_MEMORY);
	return (route_struct);
}
