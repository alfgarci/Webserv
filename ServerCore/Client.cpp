#include "Client.hpp"

Client::Client()
{
}

Client::Client(Server serv)
{
	_host_server = serv;
}

Client::~Client()
{
}

void	Client::doParseRequest()
{
	_parse_request = HTTPRequestParse(_request);
}
