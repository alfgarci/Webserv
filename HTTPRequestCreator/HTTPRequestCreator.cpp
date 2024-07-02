// HTTPRequestCreator.cpp

// Included files
#include "HTTPRequestCreator.hpp"

// Macros
#define COLON ":"
#define CONNECTION "Connection: keep-alive\r\n"
#define SPACE " "

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

string HTTPRequestCreator::createHTTPRequest(const string& method, const string& host, const string& path, const string& body, unsigned short port, bool useChunked)
{
    string request;
    ostringstream oss;

    // Add method and path
    request += method + SPACE + path + HTTP_1_1 + CRLF;
    // Add host and port
    oss << port;
    request += HOST_LABEL + host + COLON + oss.str() + CRLF;
     // Add Connection field
    request += CONNECTION;
    if (method == METHOD_POST)
    {
        // Transfer-Encoding: chunked for POST if useChunked is true
        if (useChunked)
        {
            // Add Transfer-Encoding label. chunked para POST si useChunked es true
            request += TRANSFER_LABEL;
            // Chunks start
            request += body;
            // Chunks end
            request += LENGTH_ZERO;
        }
        // Content-Length for POST if useChunked is false
        else
        {
            // Clear the string stream
            oss.str(EMPTY);
            oss.clear();
            // Add Content-Length and body
            oss << body.length();
            request += CONTENT_LABEL + oss.str() + CRLF + CRLF;
            request += body;
        }
    }
    // If method is GET or DELETE, just add CRLF
    else     
        request += CRLF;
    // Return the request
    return (request);
}
