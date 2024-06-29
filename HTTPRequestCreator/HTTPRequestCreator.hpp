// HTTPRequestCreator.hpp
#include <iostream>
#include <sstream>

#ifndef HTTP_REQUEST_CREATOR_HPP
#define HTTP_REQUEST_CREATOR_HPP

const std::string CONNECTION = "Connection: keep-alive";
const std::string CONTENT_LABEL = "Content-Length: "; 
const std::string CRLF = "\r\n";
const std::string HOST_LABEL = "Host:";
const std::string HTTP_1_1 = "HTTP/1.1";
const std::string METHOD_POST = "POST";
const std::string TRANSFER_LABEL = "Transfer-Encoding: chunked";


class HTTPRequestCreator
{
    public:
        HTTPRequestCreator();
        ~HTTPRequestCreator();
        std::string createHTTPRequest(const std::string& method, const std::string& host, const std::string& path, const std::string& body, unsigned short port, bool useChunked = false);
    
    private:
        HTTPRequestCreator(const HTTPRequestCreator& other);
        HTTPRequestCreator& operator=(const HTTPRequestCreator& other);
};

#endif // HTTP_REQUEST_CREATOR_HPP

