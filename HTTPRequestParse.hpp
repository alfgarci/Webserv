// HTTPRequestParse.hpp

#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

// Files included 
#include <algorithm>
#include <cerrno>
#include <iostream>
#include <map>
#include <sstream>

const char COLON = ':';
const char CR = '\r';
const char HYPHEN = '-';
const char LINE_END = '\0';
const char POINT = '.';
const char SLASH = '/';
const char SPACE = ' ';
const char UNDERSCORE = '_';
const int DEC_MODE = 10;
const int HEX_MODE = 16;
const int HTTP_LENGTH = 5;
const int LOWER_PORT_LIMIT = 0;
const int UPPER_PORT_LIMIT = 65535;
const std::string CHUNKED_MODE = "chunked";
const std::string KEEP_ALIVE_MODE = "keep-alive";
const std::string CONNECTION_FIELD = "connection:";
const std::string CONTENT_LENGTH_FIELD = "content-length:";
const std::string CONTENT_TYPE_FIELD = "content-type:";
const std::string DEFAULT_PORT = "80";
const std::string HOST_FIELD = "host:";
const std::string HTTP = "HTTP/";
const std::string METHOD_DEL = "DELETE";
const std::string METHOD_GET = "GET";
const std::string METHOD_POS = "POST";
const std::string TRANSFER_ENCODING_FIELD = "transfer-encoding:";
const std::string VERSION = "1.1";

class HTTPRequestParse
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
            BODY,
            PORT
        };
        // Constructors
        HTTPRequestParse(void);
        explicit HTTPRequestParse(const std::string& request);
        // Destructor
        ~HTTPRequestParse();
        // Copy constructor
        HTTPRequestParse(const HTTPRequestParse &HTTPRequestParse);
        // Assignation operator
        HTTPRequestParse &operator=(HTTPRequestParse const &HTTPRequestParse);
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
