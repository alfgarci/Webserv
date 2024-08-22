#include "Client.hpp"

Client::Client()
{
}

Client::Client(Server serv, int port)
{
	_host_server = serv;
	_parse_finish = false;
	_port = port;
	_stateCgi = NoCGI;
}

Client::~Client()
{
}

void	Client::doParseRequest()
{
	Response res(_request, _host_server, _port);
	_resObj = res;
	_resObj.doParseRequest();
	//aqui ya se si es cgi
	if (_isCgi == false)
	{
		_resObj.makeResponse();
		_isKeepAlive = _resObj.isKeepAlive();
		_response = _resObj.getResponse();
		_response_code = _resObj.getResponseCode();
	}
	else
	{
		_cgi = Cgi(_parse_request, _host_server, _port);
		_cgi.initEnvCgi();
		_cgi.executeCgi();
		setCgiState(CGIPendingWrite);
	}
}
