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
	_last_message = time(NULL);
}

Client::~Client()
{
}

bool isDirectory(string path) 
{
    struct stat info;

    if (stat(path.c_str(), &info) != 0) 
    {
        std::cerr << "Error: No se pudo acceder a la ruta." << std::endl;
        return false;
    }

    return (info.st_mode & S_IFDIR) != 0;
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
		string pathTmp = _resObj.getHTTPRequest().getField(HTTPRequestParse::PATH);
		if(isDirectory(pathTmp) == true)
		{
			_response = _resObj.parseErrorPage("404");
			_response_code = 400;
			return ;
		}
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

bool Client::isRequestComplete(const std::vector<char>& data)
{
    std::string requestData(data.begin(), data.end());

    size_t pos = requestData.find("Content-Length:");
    if (pos != std::string::npos)
    {
        size_t endPos = requestData.find("\r\n", pos);
        std::string contentLengthStr = requestData.substr(pos + 15, endPos - (pos + 15));

        // Convertir la cadena de texto a un tamaño (size_t)
        std::stringstream ss(contentLengthStr);
        size_t contentLength = 0;
        ss >> contentLength;

        size_t headerEnd = requestData.find("\r\n\r\n");

        if (headerEnd != std::string::npos)
        {
            size_t bodyStart = headerEnd + 4;
            size_t bodyLength = data.size() - bodyStart;

            return bodyLength >= contentLength;
        }
    }
    return false;
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
