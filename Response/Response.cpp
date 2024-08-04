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

}

void	Response::handleDelete()
{

}

void	Response::handleGet()
{
	string	path = _request_parse.getField(HTTPRequestParse::PATH);
	string	method = _request_parse.getField(HTTPRequestParse::PATH);

	//Comprobamos que la ruta sea accesible y el metodo valido para esa ruta
	if (isValidRoute(path, _server.getLocations()) == false)
	{
		_response << "HTTP/1.1 404 Not Found\r\n\r\n";
		_response_code = 404;
		return ;
	}
	else if (isValidMethod(method) == false)
	{
		_response << "HTTP/1.1 405 Method Not Allowed\r\n\r\n";
		_response_code = 405;
		return ;
	}
	

	if (isDirectory(path))
	{
		// Listar el contenido del directorio
		listDirectory(path, _response);
	}
	else if (isFile(path))
	{
		// Devolver el contenido del archivo
		std::string fileContent;
		if (appendFileToString(path, fileContent))
		{
			_response << "HTTP/1.1 200 OK\r\n";
			_response << "Content-Type: " << getContentType(path) << "\r\n";
			_response << "Content-Length: " << fileContent.size() << "\r\n\r\n";
			_response << fileContent;
		}
		else
		{
			_response << "HTTP/1.1 404 Not Found\r\n\r\n";
		}
	}
	else
	{
		_response << "HTTP/1.1 404 Not Found\r\n\r\n";
	}
}

bool	Response::isValidRoute(string &path, list<t_route> locations)
{
	for (list<t_route>::iterator it = locations.begin(); it != locations.end(); ++it)
	{
		// Verifica si la ruta solicitada (path) coincide con alguna ruta de la configuración (search_dir)
		if (path.find(it->search_dir) == 0) {
			return true; // Ruta válida encontrada
		}
	}
	return false; // Ninguna ruta válida encontrada
}

bool	Response::isValidMethod(string &method)
{

}


bool Response::isDirectory(string& path)
{
	struct stat info;
	// Usa stat para obtener información sobre la ruta
	if (stat(path.c_str(), &info) != 0) {
		// Error al obtener la información del archivo
		return false;
	}
	return (info.st_mode & S_IFDIR) != 0; // Verifica si es un directorio
}


bool Response::isFile(string& path)
{
	struct stat info;
	// Usa stat para obtener información sobre la ruta
	if (stat(path.c_str(), &info) != 0) {
		// Error al obtener la información del archivo
		return false;
	}
	return (info.st_mode & S_IFREG) != 0; // Verifica si es un archivo regular
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

	// Buscar la extensión en el mapa de tipos MIME
	std::map<std::string, std::string>::const_iterator it = mimeTypes.find(extension);
	if (it != mimeTypes.end())
	{
		return it->second; // Devolver el tipo MIME encontrado
	}
	// Tipo MIME por defecto si no se encuentra la extensión
	return "application/octet-stream";
}

string	Response::getFileExtension(string& filePath) 
{
	size_t dotPosition = filePath.find_last_of(".");
	if (dotPosition != std::string::npos)
	{
		return filePath.substr(dotPosition + 1);
	}
	return "";
}

void	Response::listDirectory(string& path, ostringstream& response)
{
	DIR* dir = opendir(path.c_str());
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
	}
	else
	{
		response << "HTTP/1.1 404 Not Found\r\n\r\n";
	}
}

bool	Response::appendFileToString(string& filePath, string& output)
{
	std::ifstream file(filePath.c_str(), std::ios::binary);
	if (!file)
	{
		return false; // Error al abrir el archivo
	}

	std::ostringstream oss;
	oss << file.rdbuf(); // Lee el contenido del archivo
	output += oss.str(); // Apende el contenido al string de salida

	return true;
}
