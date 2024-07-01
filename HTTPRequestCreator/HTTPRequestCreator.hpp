// HTTPRequestCreator.hpp
#include <iostream>
#include <sstream>

using std::cout;
using std::endl;
using std::ostringstream;
using std::string;

#ifndef HTTP_REQUEST_CREATOR_HPP
#define HTTP_REQUEST_CREATOR_HPP

#define CONNECTION "Connection: keep-alive\r\n"
#define CONTENT_LABEL "Content-Length: " 
#define CRLF "\r\n"
#define EMPTY ""
#define HOST_LABEL "Host: "
#define HTTP_1_1 "HTTP/1.1"
#define LENGTH_ZERO "0\r\n\r\n"
#define METHOD_POST "POST"
#define TRANSFER_LABEL "Transfer-Encoding: chunked\r\n\r\n"

class HTTPRequestCreator
{
	public:
		HTTPRequestCreator();
		~HTTPRequestCreator();
		string createHTTPRequest(const string& method, const string& host, const string& path, const string& body, unsigned short port, bool useChunked = false);
	
	private:
		HTTPRequestCreator(const HTTPRequestCreator& other);
		HTTPRequestCreator& operator=(const HTTPRequestCreator& other);
};

#endif // HTTP_REQUEST_CREATOR_HPP

