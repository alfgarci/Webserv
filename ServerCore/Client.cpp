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

	Response res(_request, _host_server);
	res.doParseRequest();
	res.makeResponse();

	cout << "-------------------------------------------"<< endl;
	cout << res.getResponse() << endl;
	cout << "-------------------------------------------"<< endl;
	send_response(_socket_client, res.getResponse());

	sleep(100000);
	/*
	_parse_request = HTTPRequestParse(_request);
	get_request(_socket_client, _parse_request, _host_server);
	//post_request(_socket_client, _parse_request, _host_server);

	_parse_finish =	true;
	*/
}

void	Client::makeResponse()
{
	HTTPRequestCreator	response;
	if (_parse_request.getField(HTTPRequestParse::METHOD) == "GET" )
		get_request(_socket_client, _parse_request, _host_server);

/*	else if (_parse_request.getField(HTTPRequestParse::METHOD) == "POST" )
		post_request(_socket_client, _parse_request, _host_server);
	else if (_parse_request.getField(HTTPRequestParse::METHOD) == "DELETE" )
		//delete_request(_socket_client, _parse_request);
	else
	*/

	//_response = response.createHTTPRequest()
}
