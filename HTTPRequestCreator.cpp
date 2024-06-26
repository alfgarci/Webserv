// HTTPRequestCreator.cpp

// Included files
#include "HTTPRequestCreator.hpp"

// Default constructor
HTTPRequestCreator::HTTPRequestCreator()
{
}

// Destructor
HTTPRequestCreator::~HTTPRequestCreator()
{
}

// Copy constructor
HTTPRequestCreator::HTTPRequestCreator(const HTTPRequestCreator& other)
{
    *this = other;
}

// Assignment operator
HTTPRequestCreator& HTTPRequestCreator::operator=(const HTTPRequestCreator& other)
{
    if (this == &other)
        return (*this);
    return (*this);
}

std::string HTTPRequestCreator::createHTTPRequest(const std::string& method, const std::string& host, const std::string& path, const std::string& body, unsigned short port, bool useChunked)
{
    std::string request;
    std::ostringstream oss;

    // Add method and path
    request += method + SPACE + path + HTTP + CRLF;
    // Add host and port
    oss << port;
    request += HOST_LABEL + SPACE + host + COLON + oss.str() + CRLF;
     // Add Connection field
    request += CONNECTION + CRLF;
    if (method == METHOD_POST)
    {
        // Transfer-Encoding: chunked for POST if useChunked is true
        if (useChunked)
        {
            // Add Transfer-Encoding label. chunked para POST si useChunked es true
            request += TRANSFER_LABEL + CRLF + CRLF;
            // Chunks start
            request += body;
            // Chunks end
            request += "0" + CRLF + CRLF;
        }
        // Content-Length for POST if useChunked is false
        else
        {
            // Clear the string stream
            oss.str("");
            oss.clear();
            // Add Content-Length and body
            oss << body.length();
            request += CONTENT_LABEL + SPACE + oss.str() + CRLF + CRLF; request += body;
        }
    }
    // If method is GET or DELETE, just add CRLF
    else     
        request += CRLF;
    // Return the request
    return (request);
}
