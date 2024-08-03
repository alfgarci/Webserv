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

	/*
	if (_parse_request.getField(HTTPRequestParse::METHOD) == "GET" )
		get_request(_socket_client, _parse_request, _host_server);
	else if (_parse_request.getField(HTTPRequestParse::METHOD) == "POST" )
		post_request(_socket_client, _parse_request, _host_server);
	else if (_parse_request.getField(HTTPRequestParse::METHOD) == "DELETE" )
		//delete_request(_socket_client, _parse_request);
	else
	*/

	//_response = response.createHTTPRequest()
}
