// HTTPRequestParse.hpp

#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

// Files included 
#include <algorithm>
#include <cerrno>
#include <iostream>
#include <map>
#include <sstream>

using std::cout;
using std::endl;
using std::getline;
using std::isalnum;
using std::istringstream;
using std::map;
using std::ostringstream;
using std::runtime_error;
using std::string;
using std::stringstream;
using std::transform;

#define COLON ':'
#define CR '\r'
#define HYPHEN '-'
#define LINE_END '\0'
#define POINT '.'
#define SLASH '/'
#define SPACE ' '
#define UNDERSCORE '_'
#define DEC_MODE 10
#define HEX_MODE 16
#define HTTP_LENGTH 5
#define LOWER_PORT_LIMIT 0
#define UPPER_PORT_LIMIT 65535
#define CHUNKED_MODE "chunked"
#define KEEP_ALIVE_MODE "keep-alive"
#define CONNECTION_FIELD "connection:"
#define CONTENT_LENGTH_FIELD "content-length:"
#define CONTENT_TYPE_FIELD "content-type:"
#define DEFAULT_PORT "80"
#define HOST_FIELD "host:"
#define HTTP "HTTP/"
#define METHOD_DEL "DELETE"
#define METHOD_GET "GET"
#define METHOD_POS "POST"
#define TRANSFER_ENCODING_FIELD "transfer-encoding:"
#define VERSION "1.1"

// Error messages
#define CHUNK_CONVERSION_ERROR "Conversion error: Chunk length is not a valid number or out of range"
#define CHUNK_LENGTH_LESS "Chunk length is less than the real length"
#define CHUNK_LENGTH_GREATER "Chunk length is greater than the real length"
#define CL_OR_TE "Content-Length or Transfer-Encoding field must be present"
#define CONTENT_ERROR "Content-Type format is not valid"
#define CONTENT_LENGHT_ERROR "Content-Length does not match the body length"
#define CONVERSION_ERROR "Conversion error: Content-Length is not a valid number or out of range"
#define EMPTY_PORT "Port field is empty"
#define EMPTY_REQUEST "Empty HTTP request"
#define FIELD_MULTIPLE_VALUES "Only one value for each field is allowed"
#define HOST_ERROR "Host field not found or empty"
#define LAST_CHUNK_LENGTH_ERROR "Last chunk length is not 0"
#define METHOD_ERROR "HTTP method not valid"
#define ONLY_CL_OR_TE "Only one of Content-Length or Transfer-Encoding must be present"
#define OUT_OF_RANGE "Port out of range (0-65535)"
#define PORT_ERROR "Port number not valid"
#define PATH_ERROR "Path format not valid"
#define TRANSFER_ERROR "Transfer-Encoding format is not valid"
#define VERSION_ERROR "HTTP version not valid"

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
        explicit HTTPRequestParse(const string& request);
        // Destructor
        ~HTTPRequestParse();
        // Copy constructor
        HTTPRequestParse(const HTTPRequestParse &HTTPRequestParse);
        // Assignation operator
        HTTPRequestParse &operator=(HTTPRequestParse const &HTTPRequestParse);
        // Function to check HTTP request
        void parse(const string& request);
        // Get field value
        string getField(FieldType field) const;
        // Set field value
        void setField(FieldType field, const string& value);

    private:
        // For storing field values
        map<FieldType, string> fieldValues;
        // For checking is field is included into the HTTP
        map<FieldType, bool> fieldFound;
        // For checking if field value is set
        map<FieldType, bool> fieldSet;
        // Function to check if method is valid
        static bool isValidHTTPMethod(const string& method);
        // Function to check if HTTP versión is valid
        static bool isValidHTTPVersion(const string& version);
        // Function to check if path versión is valid
        static bool isValidPathFormat(const string& path);
        // Function to erase unnecessary spaces
        static string trim(const string& str);
};

#endif // HTTP_REQUEST_HPP
