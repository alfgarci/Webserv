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

#define BAD_REQUEST_ERROR "HTTP/1.1 400 Bad Request\r\n" \
						  "Content-Type: text/html\r\n\r\n" \
						  "<html><body><h1>400 Bad Request</h1>" \
						  "<p>The server could not understand the request due to invalid syntax.</p>" \
						  "</body></html>"

#define FORBIDDEN_ERROR "HTTP/1.1 403 Forbidden\r\n" \
						"Content-Type: text/html\r\n\r\n" \
						"<html><body><h1>403 Forbidden</h1>" \
						"<p>You do not have permission to access the requested resource.</p>" \
						"</body></html>"

#define NOT_FOUND_ERROR "HTTP/1.1 404 Not Found\r\n" \
						"Content-Type: text/html\r\n\r\n" \
						"<html><body><h1>404 Not Found</h1>" \
						"<p>The requested resource could not be found on this server.</p>" \
						"</body></html>"

#define METHOD_NOT_ALLOWED_ERROR "HTTP/1.1 405 Method Not Allowed\r\n" \
								 "Allow: GET, POST\r\n" \
								 "Content-Type: text/html\r\n\r\n" \
								 "<html><body><h1>405 Method Not Allowed</h1>" \
								 "<p>The requested method is not allowed for the URL.</p>" \
								 "</body></html>"

#define INTERNAL_SERVER_ERROR "HTTP/1.1 500 Internal Server Error\r\n" \
							  "Content-Type: text/html\r\n\r\n" \
							  "<html><body><h1>500 Internal Server Error</h1>" \
							  "<p>The server encountered an internal error and could not complete your request.</p>" \
							  "</body></html>"

#define UNSUPPORTED_MEDIA_TYPE_ERROR "HTTP/1.1 415 Unsupported Media Type\r\n" \
									 "Content-Type: text/html\r\n\r\n" \
									 "<html><body><h1>415 Unsupported Media Type</h1>" \
									 "<p>The server does not support the media type transmitted in the request.</p>" \
									 "</body></html>"

#define FILE_UPLOAD_SUCCESS "HTTP/1.1 200 OK\r\n" \
							"Content-Type: text/html\r\n\r\n" \
							"<html><body><h1>File uploaded successfully.</h1>" \
							"</body></html>"

#define TEXT_UPLOAD_SUCCESS "HTTP/1.1 200 OK\r\n" \
							"Content-Type: text/html\r\n\r\n" \
							"<html><body><h1>Text data submitted successfully.</h1>" \
							"</body></html>"

#define FILE_DELETE_SUCCESS "HTTP/1.1 200 OK\r\n" \
							"Content-Type: text/html\r\n\r\n" \
							"<html><body><h1>File deleted successfully.</h1>" \
							"</body></html>"

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

		string	parseErrorPage(string errorCode);

		string	getResponse(){ return _response.str(); };

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
