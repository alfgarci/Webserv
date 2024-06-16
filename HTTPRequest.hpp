// HTTPRequest.hpp

#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

// Files included
#include <algorithm>
#include <cctype>
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <vector>

// HTTPRequest class
class HTTPRequest
{
    public:
        enum FieldType
        {
            METHOD,
            PATH,
            HTTP_VERSION,
            HOST,
            CONNECTION,
            CONTENT_LENGTH,
            CONTENT_TYPE,
            TRANSFER_ENCODING,
            BODY
        };
        // Constructors
        HTTPRequest(void);
        explicit HTTPRequest(const std::string& request);
        // Destructor
        ~HTTPRequest();
        // Copy constructor
        HTTPRequest(const HTTPRequest &httpRequest);
        // Assignation operator
        HTTPRequest &operator=(HTTPRequest const &httpRequest);
        // Function to check HTTP request
        void parse(const std::string& request);
        // Get field value
        std::string getField(FieldType field) const;
        // Set field value
        void setField(FieldType field, const std::string& value);

    private:
        // For storing field values
        std::map<FieldType, std::string> fieldValues;
        // For checking is field is included into the HTTP
        std::map<FieldType, bool> fieldFound;
        // For checking if field value is set
        std::map<FieldType, bool> fieldSet;
        // Function to check if method is valid
        static bool isValidHTTPMethod(const std::string& method);
        // Function to check if HTTP versión is valid
        static bool isValidHTTPVersion(const std::string& version);
        // Function to check if path versión is valid
        static bool isValidPathFormat(const std::string& path);
        // Function to erase unnecessary spaces
        static std::string trim(const std::string& str);
};

#endif // HTTP_REQUEST_HPP
