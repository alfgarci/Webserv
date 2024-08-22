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
	int	error;
	Response res(_request, _host_server, _port);
	_resObj = res;
	_resObj.doParseRequest();
	//aqui ya se si es cgi
	if (_resObj.isCgi() == false)
	{
		_resObj.makeResponse();
		_isKeepAlive = _resObj.isKeepAlive();
		_response = _resObj.getResponse();
		_response_code = _resObj.getResponseCode();
	}
	else
	{
		//check si el cgi tiene la extension correspondiente
		//check si tengo permisos de ejecucion
		_cgi = Cgi(_resObj.getHTTPRequest(), _host_server, _port, _resObj.getFileAceptedCgi());
		error = _cgi.initEnvCgi();
		if (error > 0)
		{
			if (error == 404)
				_response = _resObj.parseErrorPage("404");
			else if (error == 500)
				_response = _resObj.parseErrorPage("500");
			_response_code = error;
		}
		else
		{
			_cgi.executeCgi();
			setCgiState(CGIPendingWrite);
		}
	}
}

size_t Client::extractContentLength(const std::string& requestData)
{
	size_t contentLength = 0;
	std::string contentLengthHeader = "Content-Length: ";
	size_t pos = requestData.find(contentLengthHeader);
	
	if (pos != std::string::npos)
	{
		pos += contentLengthHeader.length();
		size_t endPos = requestData.find("\r\n", pos);
		if (endPos != std::string::npos)
		{
			std::string contentLengthStr = requestData.substr(pos, endPos - pos);
			std::stringstream ss(contentLengthStr);
			ss >> contentLength;
		}
	}
	
	return contentLength;
}

void Client::reset()
{
	_request.clear();
	_response.clear();

	_isKeepAlive = true;
	
	_isCgi = false;
	_cgi.reset();

	_response_code = 0;
}
