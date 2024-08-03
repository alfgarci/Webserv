#include "Client.hpp"

Client::Client()
{
}

Client::Client(Server serv)
{
	_host_server = serv;
	_parse_finish = false;
}

Client::~Client()
{
}

HTTPRequestParse	Client::getParseRequest()
{
	//if (_parse_finish)
	return _parse_request;
}

void	Client::doParseRequest()
{
	_parse_request = HTTPRequestParse(_request);
	_parse_finish =	true;
}

void	Client::makeResponse()
{
	HTTPRequestCreator	response;

	//_response = response.createHTTPRequest()
}
