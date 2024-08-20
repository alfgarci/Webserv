#include "../ServerInfo.hpp"

t_error	ServerInfo::initiate_error()
{
	t_error	err;

	err.code = DEFAULT_SERVER_ERROR_CODE;
	err.path = DEFAULT_SERVER_ERROR_PATH;
	return (err);
}
