#pragma once

# include <iostream>
# include <fstream>
# include <string>
# include <sstream>
# include <vector>
# include <dirent.h>
# include <filesystem>
# include <sys/stat.h>
# include "../HTTPRequestParse/HTTPRequestParse.hpp"
# include "../ServerCore/Server.hpp"
# include "../libs/to_int.hpp"
# include "../Cgi/Cgi.hpp"
# include "HTTPDefines.hpp"

using std::string;

class Response
{
	private:
		string  			_request_raw;
		HTTPRequestParse    _request_parse;
		Server				_server;
		
		int					_port;

		int					_response_code;
		ostringstream 		_response;

		bool				_isCgi;
		string				_fileAcepted;
		
	public:
		Response();
		Response(string	request_raw, Server server, int port);

		Response(const Response &other);
		Response& operator=(const Response &other);

		void	doParseRequest();
		void	makeResponse();

		void	handleGet();
		void	handlePost();
		void	handleDelete();

		string	parseErrorPage(string errorCode);

		string	getResponse(){ return _response.str(); };
		int		getResponseCode(){ return _response_code; };
		HTTPRequestParse	getHTTPRequest(){ return _request_parse; };
		string	getFileAceptedCgi(){ return _fileAcepted; };

		bool	checkCgiRequest(string path, list<t_route> routes);
		bool	isCgi() { return _isCgi; };

		bool	isKeepAlive();

		bool	isValidRoute(string &path, list<t_route> routes, t_route &matchedRoute);
		bool 	isValidMethod(string &method, list<string> accepted_http_methods);
		bool	hasReadPermission(string& path);
		bool 	hasWritePermission(string& path);

		bool	isDirectory(string& path);
		bool	isFile(string& path);
		string 	getContentType(string& filePath);
		string	getFileExtension(string& filePath);
		string	listDirectory(string& path);
		bool	appendFileToString(string& filePath, string& output);

		string	generateFileResponse(string &path);

		//procesar el cuerpo
		void	handleMultipartFormData(string &body, string &contentType, string &path);
};
