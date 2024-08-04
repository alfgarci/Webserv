#pragma once

# include <iostream>
# include <fstream>
# include <string>
# include <sstream>
# include <dirent.h>
# include <filesystem>
# include <sys/stat.h>
# include "../HTTPRequestParse/HTTPRequestParse.hpp"
# include "../ServerCore/Server.hpp"
# include "../libs/to_int.hpp"

using std::string;

class Response
{
	private:
		string  			_request_raw;
		HTTPRequestParse    _request_parse;
		Server				_server;

		int					_response_code;
		ostringstream 		_response;


		
	public:
		Response(string	request_raw, Server server);

		void	doParseRequest();
		void	makeResponse();

		void	handleGet();
		void	handlePost();
		void	handleDelete();

		string	getResponse(){ return _response.str(); };

		bool	isValidRoute(string &path, list<t_route> routes);
		bool	isValidMethod(string &method);

		bool	isDirectory(string& path);
		bool	isFile(string& path);
		string 	getContentType(string& filePath);
		string	getFileExtension(string& filePath);
		void	listDirectory(string& path, ostringstream& response);
		bool	appendFileToString(string& filePath, string& output);
};
