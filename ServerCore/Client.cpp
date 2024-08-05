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
	_response = res.getResponse();

	/*
	cout << "-------------------------------------------"<< endl;
	cout << _response << endl;
	cout << "-------------------------------------------"<< endl;
	send_response(_socket_client, res.getResponse());

	sleep(100000);
	*/
}
