#include "Response.hpp"

Response::Response(string request_raw, Server server)
{
	_request_raw = request_raw;
	_server = server;
}

void    Response::doParseRequest()
{
	_request_parse = HTTPRequestParse(_request_raw);
}

void    Response::makeResponse()
{
	if (_request_parse.getField(HTTPRequestParse::METHOD) == "GET")
	{
		Response::handleGet();
	}
	else if (_request_parse.getField(HTTPRequestParse::METHOD) == "POST")
	{
		Response::handlePost();
	}
	else if (_request_parse.getField(HTTPRequestParse::METHOD) == "DELETE")
	{
		Response::handleDelete();
	}
}

void	Response::handlePost()
{
	string	path = _request_parse.getField(HTTPRequestParse::PATH);
	string	method = _request_parse.getField(HTTPRequestParse::PATH);
	string	body = _request_parse.getField(HTTPRequestParse::BODY);
	string	contentType = _request_parse.getField(HTTPRequestParse::CONTENT_TYPE);
	t_route	routeRequest;

	if (isValidRoute(path, _server.getLocations(), routeRequest) == false)
	{
		_response << parseErrorPage("404");
		_response_code = 404;
		return ;
	}
	else if (hasWritePermission(path) == false)
	{
		_response << parseErrorPage("403");
		_response_code = 403;
		return ;
	}
	else if (isValidMethod(method) == false)
	{
		_response << parseErrorPage("405");
		_response_code = 405;
		return ;
	}
	//procesar el cuerpo de la solicitud
    if (body.empty())
    {
        _response << parseErrorPage("400");
        _response_code = 400;
        return;
    }
	cout << "+++++++++++++++++++++++++++++++++" << endl;
	cout << contentType << endl;
	cout << "+++++++++++++++++++++++++++++++++" << endl;

}

void	Response::handleDelete()
{

}

void	Response::handleGet()
{
	string	path = _request_parse.getField(HTTPRequestParse::PATH);
	string	method = _request_parse.getField(HTTPRequestParse::PATH);
	t_route	routeRequest;

	//Comprobamos que la ruta sea accesible, que tengamos permisos y el metodo valido para esa ruta
	if (isValidRoute(path, _server.getLocations(), routeRequest) == false)
	{
		_response << parseErrorPage("404");
		_response_code = 404;
		return ;
	}
	else if (hasReadPermission(path) == false)
	{
		_response << parseErrorPage("403");
		_response_code = 403;
		return ;
	}
	else if (isValidMethod(method) == false)
	{
		_response << parseErrorPage("405");
		_response_code = 405;
		return ;
	}

	if (isDirectory(path))
	{
		if (routeRequest.default_file_to_answer != "")
		{
			//devolver el contenido del archivo index
			_response << generateFileResponse(routeRequest.default_file_to_answer);
		}
		else if (routeRequest.dir_to_listen == true)
		{
			//listo el direcctio so dir_to_listen es truee
			_response << listDirectory(path);
		}
		else
		{
			_response << parseErrorPage("403");
			_response_code = 403;
		}
	}
	else if (isFile(path))
	{
		//devolver el contenido del archivo de la ruta
		_response << generateFileResponse(path);
	}
	else
	{
		_response << parseErrorPage("404");
		_response_code = 404;
	}
}

string	Response::generateFileResponse(string &path)
{
	ostringstream	response;
    string	fileContent;
    if (appendFileToString(path, fileContent))
    {
        response << "HTTP/1.1 200 OK\r\n";
        response << "Content-Type: " << getContentType(path) << "\r\n";
        response << "Content-Length: " << fileContent.size() << "\r\n\r\n";
        response << fileContent;
        _response_code = 200;
    }
    else
    {
        response << parseErrorPage("404");
        _response_code = 404;
    }
	return response.str();
}

string	Response::parseErrorPage(string errorCode)
{
	ostringstream	responseError;
	//IMPORTANTEEEEEEE
	//checkear que no tengo mis propias error pages

	if (errorCode == "400")
		responseError << BAD_REQUEST_ERROR;
	else if (errorCode == "403")
		responseError << FORBIDDEN_ERROR;
	else if (errorCode == "404")
		responseError << NOT_FOUND_ERROR;
	else if (errorCode == "405")
		responseError << METHOD_NOT_ALLOWED_ERROR;
	else if (errorCode == "500")
		responseError << INTERNAL_SERVER_ERROR;
	
	return responseError.str();
}

bool	Response::isValidRoute(string &path, list<t_route> locations, t_route &matchedRoute)
{
	for (list<t_route>::iterator it = locations.begin(); it != locations.end(); ++it)
	{
		//verifica si la ruta solicitada (path) coinciide con alguna ruta de la configuracoion (search_dir)
		if (path.find(it->search_dir) == 0)
		{
			matchedRoute = *it;
			return true;
		}
	}
	return false;
}

bool Response::hasReadPermission(string& path)
{
    struct stat info;

    if (stat(path.c_str(), &info) != 0)
        return false;

    return (info.st_mode & S_IRUSR) || (info.st_mode & S_IRGRP) || (info.st_mode & S_IROTH);
}

bool	Response::hasWritePermission(string& path)
{
    struct stat info;

    if (stat(path.c_str(), &info) != 0)
        return false;

    return (info.st_mode & S_IWUSR) || (info.st_mode & S_IWGRP) || (info.st_mode & S_IWOTH);
}

bool	Response::isValidMethod(string &method)
{
	(void)method;
	return true;
}

bool Response::isDirectory(string& path)
{
	struct stat info;

	//usa stat para obtener informacon sobre la ruta
	if (stat(path.c_str(), &info) != 0)
		return false;

	return (info.st_mode & S_IFDIR) != 0; //verifica si es un direectorio
}


bool Response::isFile(string& path)
{
	struct stat info;

	if (stat(path.c_str(), &info) != 0)
		return false;

	return (info.st_mode & S_IFREG) != 0;
}

std::map<std::string, std::string> initializeMimeTypes()
{
	std::map<std::string, std::string> mimeTypes;
	mimeTypes["html"] = "text/html";
	mimeTypes["htm"] = "text/html";
	mimeTypes["txt"] = "text/plain";
	mimeTypes["css"] = "text/css";
	mimeTypes["js"] = "application/javascript";
	mimeTypes["json"] = "application/json";
	mimeTypes["xml"] = "application/xml";
	mimeTypes["jpg"] = "image/jpeg";
	mimeTypes["jpeg"] = "image/jpeg";
	mimeTypes["png"] = "image/png";
	mimeTypes["gif"] = "image/gif";
	mimeTypes["bmp"] = "image/bmp";
	mimeTypes["webp"] = "image/webp";
	mimeTypes["svg"] = "image/svg+xml";
	mimeTypes["ico"] = "image/x-icon";
	mimeTypes["pdf"] = "application/pdf";
	mimeTypes["zip"] = "application/zip";
	mimeTypes["gz"] = "application/gzip";
	mimeTypes["mp3"] = "audio/mpeg";
	mimeTypes["wav"] = "audio/wav";
	mimeTypes["mp4"] = "video/mp4";
	mimeTypes["avi"] = "video/x-msvideo";
	mimeTypes["mpeg"] = "video/mpeg";
	mimeTypes["mov"] = "video/quicktime";
	return mimeTypes;
}

string 	Response::getContentType(string& filePath)
{

	static std::map<std::string, std::string> mimeTypes = initializeMimeTypes();

	size_t dotPosition = filePath.find_last_of(".");
	std::string extension;
	if (dotPosition != std::string::npos)
	{
		extension = filePath.substr(dotPosition + 1);
	}

	//buscar la extensión en el mapa de tipos MIME
	std::map<std::string, std::string>::const_iterator it = mimeTypes.find(extension);
	if (it != mimeTypes.end())
		return it->second; //devolver el tipo MIME encontrado

	//tipo MIME por defecto si noencuentra la extension
	return "application/octet-stream";
}

string	Response::getFileExtension(string& filePath) 
{
	size_t dotPosition = filePath.find_last_of(".");

	if (dotPosition != std::string::npos)
		return filePath.substr(dotPosition + 1);

	return "";
}

string	Response::listDirectory(string& path)
{
	DIR* dir = opendir(path.c_str());
	ostringstream	response;
	if (dir)
	{
		struct dirent* entry;
		response << "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
		response << "<html><body><h1>Directory listing for " << path << "</h1><ul>";
		while ((entry = readdir(dir)) != NULL)
		{
			std::string entryName = entry->d_name;
			response << "<li><a href=\"" << path << "/" << entryName << "\">" << entryName << "</a></li>";
		}
		response << "</ul></body></html>";
		closedir(dir);
		_response_code = 200;
	}
	else
	{
		response << parseErrorPage("404");
		_response_code = 404;
	}

	return response.str();
}

bool	Response::appendFileToString(string& filePath, string& output)
{
	std::ifstream file(filePath.c_str(), std::ios::binary);
	
	if (!file)
		return false; //error al abrir el archivo


	std::ostringstream oss;
	oss << file.rdbuf(); //llee el contenido del archivo
	output += oss.str(); //apendeaa el contenido al string de salida

	return true;
}
