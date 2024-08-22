#include "Response.hpp"

Response::Response()
{
}

Response::Response(string request_raw, Server server, int port)
{
	_request_raw = request_raw;
	_server = server;
	_port = port;
}

Response::Response(const Response &other)
{
	_request_raw = other._request_raw;
	_server = other._server;
	_port = other._port;
}

Response& Response::operator=(const Response &other)
{
	if (this != &other)
	{
		_request_raw = other._request_raw;
		_server = other._server;
		_port = other._port;
	}

	return *this;
}

void	Response::doParseRequest()
{
	_request_parse = HTTPRequestParse(_request_raw);
	_isCgi = checkCgiRequest(_request_parse.getField(HTTPRequestParse::PATH), _server.getLocations());
}

bool	Response::checkCgiRequest(string path, list<t_route> routes)
{
	for (list<t_route>::const_iterator routeIt = routes.begin(); routeIt != routes.end(); ++routeIt)
	{
		if (path.find(routeIt->search_dir) == 0)
		{
			for (list<t_CGI>::const_iterator cgiIt = routeIt->cgi.begin(); cgiIt != routeIt->cgi.end(); ++cgiIt)
			{
				if (path.find(cgiIt->file_targets) != std::string::npos)
				{
					return true;
				}
			}
		}
	}
	return false;
}


void	Response::makeResponse()
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
	else
	{
		_response << parseErrorPage("405");
		_response_code = 405;
	}
}

void	Response::handlePost()
{
	string	path = _request_parse.getField(HTTPRequestParse::PATH);
	string	method = _request_parse.getField(HTTPRequestParse::METHOD);
	string	body = _request_parse.getField(HTTPRequestParse::BODY);
	string	contentType = _request_parse.getField(HTTPRequestParse::CONTENT_TYPE);
	t_route	routeRequest;

	if (isValidRoute(path, _server.getLocations(), routeRequest) == false)
	{
		_response << parseErrorPage("404");
		_response_code = 404;
		return ;
	}
	else if (hasWritePermission(routeRequest.http_redirections) == false)
	{
		_response << parseErrorPage("403");
		_response_code = 403;
		return ;
	}
	else if (isValidMethod(method, routeRequest.accepted_http_methods) == false)
	{
		_response << parseErrorPage("405");
		_response_code = 405;
		return ;
	}
	else if (body.size() > _server.get_limit_body_size())
	{
		_response << parseErrorPage("413");
		_response_code = 413;
		return ;
	}
	//procesar el cuerpo de la solicitud
	if (body.empty())
	{
		_response << parseErrorPage("400");
		_response_code = 400;
		return;
	}
	if (contentType.find("multipart/form-data") != std::string::npos)
	{
		handleMultipartFormData(body, contentType, routeRequest.http_redirections);
		_response << HTTP_SUCCESS;
		_response << FILE_UPLOAD_SUCCESS;
		_response_code = 200;
	}
	else if (contentType.find("text/plain") != std::string::npos)
	{
		std::ofstream outFile((routeRequest.http_redirections + "/text_data.txt").c_str());
		if (outFile.is_open())
		{
			outFile << body;
			outFile.close();
		}
		_response << HTTP_SUCCESS;
		_response << TEXT_UPLOAD_SUCCESS;
		_response_code = 200;
	}
	else
	{
		_response << parseErrorPage("415");
		_response_code = 400;
	}
}

void processBody(const std::string &body, const std::string &boundary, const std::string &path)
{
	size_t start, end, filename_start, filename_end;
	std::string filename;
	std::ofstream file;

	start = body.find("Content-Disposition");
	
	if (start == std::string::npos)
		return;

	filename_start = body.find("filename=\"", start) + 10;
	filename_end = body.find("\"", filename_start);

	filename = body.substr(filename_start, filename_end - filename_start);

	start = body.find("\r\n\r\n", filename_end) + 4;
	end = body.find(boundary, start) - 2;

	file.open((path + "/" + filename).c_str(), std::ios::binary);
	
	if (!file.is_open())
		return;

	file.write(body.data() + start, end - start);
	file.close();
}

string	extractBoundary(const std::string &contentType)
{
	std::string boundaryPrefix = "boundary=";
	size_t boundaryPos = contentType.find(boundaryPrefix);
	if (boundaryPos != std::string::npos)
	{
		return "--" + contentType.substr(boundaryPos + boundaryPrefix.length());
	}
	return "";
}

void Response::handleMultipartFormData(std::string &body, std::string &contentType, std::string &path)
{

	std::string boundary = extractBoundary(contentType);
	if (boundary.empty()) {
		std::cerr << "error: boundary no encontrado en el Content-Type." << std::endl;
		return;
	}
	
	processBody(body, boundary, path);
}

void	Response::handleDelete()
{
	string	path = _request_parse.getField(HTTPRequestParse::PATH);
	string	method = _request_parse.getField(HTTPRequestParse::METHOD);
	t_route	routeRequest;

	if (isValidRoute(path, _server.getLocations(), routeRequest) == false)
	{
		_response << parseErrorPage("404");
		_response_code = 404;
		return ;
	}
	else if (hasWritePermission(routeRequest.http_redirections) == false)
	{
		_response << parseErrorPage("403");
		_response_code = 403;
		return ;
	}
	else if (isValidMethod(method, routeRequest.accepted_http_methods) == false)
	{
		_response << parseErrorPage("405");
		_response_code = 405;
		return ;
	}
	//intentamos borrar
	if (remove(path.c_str()) == 0)
	{
		_response << HTTP_SUCCESS;
		_response << FILE_DELETE_SUCCESS;
		_response_code = 200;
	}
	else
	{
		_response << parseErrorPage("500");
		_response_code = 500;
	}
}

void	Response::handleGet()
{
	string	path = _request_parse.getField(HTTPRequestParse::PATH);
	string	method = _request_parse.getField(HTTPRequestParse::METHOD);
	t_route	routeRequest;

	//Comprobamos que la ruta sea accesible, que tengamos permisos y el metodo valido para esa ruta
	if (isValidRoute(path, _server.getLocations(), routeRequest) == false || access(path.c_str(),F_OK))
	{
		_response << parseErrorPage("404");
		_response_code = 404;
		return ;
	}
	else if (hasReadPermission(path) == false)
	{
		//cout << "AQUIIIII\n"; hay un error
		_response << parseErrorPage("403");
		_response_code = 403;
		return ;
	}
	else if (isValidMethod(method, routeRequest.accepted_http_methods) == false)
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

string getBodyErrorFile(string errorCode, list<t_error> errorPages)
{
	unsigned int errorCodeInt;
	istringstream(errorCode) >> errorCodeInt;

	for (list<t_error>::iterator it = errorPages.begin(); it != errorPages.end(); ++it)
	{
		if (it->code == errorCodeInt)
		{
			if (access(it->path.c_str(), F_OK) == 0)
			{
				std::ifstream file(it->path.c_str());
				if (file.is_open())
				{
					ostringstream ss;
					ss << file.rdbuf();
					return ss.str();
				}
				else
				{
					return "";
				}
			}
			else
			{
				return "";
			}
		}
	}
	return "";
}

string	Response::parseErrorPage(string errorCode)
{
	
	ostringstream	responseError;
	list<t_error>	errorPages = _server.getErrorPages();

	string	bodyError = getBodyErrorFile(errorCode, errorPages);
	if (bodyError == "")
	{
		if (errorCode == "400")
			responseError << BAD_REQUEST_ERROR << BAD_REQUEST_ERROR_BODY;
		else if (errorCode == "403")
			responseError << FORBIDDEN_ERROR << FORBIDDEN_ERROR_BODY;
		else if (errorCode == "404")
			responseError << NOT_FOUND_ERROR << NOT_FOUND_ERROR_BODY;
		else if (errorCode == "405")
			responseError << METHOD_NOT_ALLOWED_ERROR << METHOD_NOT_ALLOWED_ERROR_BODY;
		else if (errorCode == "500")
			responseError << INTERNAL_SERVER_ERROR << INTERNAL_SERVER_ERROR_BODY;
		else if (errorCode == "415")
			responseError << UNSUPPORTED_MEDIA_TYPE_ERROR << UNSUPPORTED_MEDIA_TYPE_ERROR_BODY;
		else if (errorCode == "413")
			responseError << PAYLOAD_TOO_LARGE_ERROR << PAYLOAD_TOO_LARGE_ERROR_BODY;
	}
	else
	{
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
		else if (errorCode == "415")
			responseError << UNSUPPORTED_MEDIA_TYPE_ERROR;
		else if (errorCode == "413")
			responseError << PAYLOAD_TOO_LARGE_ERROR;

		responseError << bodyError;
	}

	return responseError.str();
}

bool	Response::isValidRoute(string &path, list<t_route> locations, t_route &matchedRoute)
{
	for (list<t_route>::iterator it = locations.begin(); it != locations.end(); ++it)
	{
		//verifica si la ruta solicitada (path) coinciide con alguna ruta de la configuracoion (http_redirections)
		if (path.find(it->http_redirections) == 0 || path == it->search_dir)
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

bool Response::isValidMethod(string &method, list<string> accepted_http_methods)
{
	for (std::list<std::string>::const_iterator it = accepted_http_methods.begin();
		 it != accepted_http_methods.end(); ++it)
	{
		if (*it == method)
		{
			return true;
		}
	}
	return false;
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

bool	Response::isKeepAlive()
{
	string connection = _request_parse.getField(HTTPRequestParse::CONNECTION);
	
	if (connection.find("keep-alive") != std::string::npos)
		return true;
	else
		return false;
}
