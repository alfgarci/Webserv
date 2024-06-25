// HTTPRequest.cpp

// Files included
#include "HTTPRequest.hpp"

// Default constructor
HTTPRequest::HTTPRequest(void)
{
    fieldSet[METHOD] = false;
    fieldSet[PATH] = false;
    fieldSet[HTTP_VERSION] = false;
    fieldSet[HOST] = false;
    fieldSet[CONNECTION] = false;
    fieldSet[CONTENT_LENGTH] = false;
    fieldSet[CONTENT_TYPE] = false;
    fieldSet[TRANSFER_ENCODING] = false;
    fieldSet[BODY] = false;
    fieldFound = fieldSet;
}
// Constructor
HTTPRequest::HTTPRequest(const std::string& request)
{
    fieldSet[METHOD] = false;
    fieldSet[PATH] = false;
    fieldSet[HTTP_VERSION] = false;
    fieldSet[HOST] = false;
    fieldSet[CONNECTION] = false;
    fieldSet[CONTENT_LENGTH] = false;
    fieldSet[CONTENT_TYPE] = false;
    fieldSet[TRANSFER_ENCODING] = false;
    fieldSet[BODY] = false;

    fieldFound = fieldSet;
    parse(request);
}
// Destructor
HTTPRequest::~HTTPRequest() {}

bool HTTPRequest::isValidHTTPMethod(const std::string& method)
{
    if (method == "GET" || method == "POST" || method == "DELETE")
        return (true);
    return (false);
}

bool HTTPRequest::isValidHTTPVersion(const std::string& version)
{
    if (version.substr(0, 5) == "HTTP/")
    {
        std::string versionNumber = version.substr(5);
        return (versionNumber == "1.1");
    }
    throw std::runtime_error("HTTP version not valid");
}
// Check path field
bool HTTPRequest::isValidPathFormat(const std::string& path)
{
    if (path.empty() || path[0] != '/')
        return false;
    for (size_t i = 0; i < path.size(); ++i)
    {
        char c = path[i];
        if (!(std::isalnum(c) || c == '/' || c == '-' || c == '_' || c == '.'))
            return false;
    }
    return (true);
}
// Function to erase unnecessary spaces
std::string HTTPRequest::trim(const std::string& str)
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return (first == std::string::npos || last == std::string::npos) ? "" : str.substr(first, last - first + 1);
}

// Function to check HTTP request format
void HTTPRequest::parse(const std::string& request)
{
    char *end;
    std::istringstream iss(request);
    std::string line;
    std::stringstream bodyStream;
    unsigned long length;

    // Read request first line
    if (std::getline(iss, line))
    {
        // If there is an '\r' it is erased
        if (!line.empty() && line[line.size() - 1] == '\r')
            line.erase(line.size() - 1);
        std::istringstream lineStream(line);
        std::string method, path, httpVersion;
        lineStream >> method >> path >> httpVersion;
        // Checking if method is valid
        if (!isValidHTTPMethod(method))
            throw std::runtime_error("HTTP method not valid");
        // Checking if HTTP version is valid
        if (!isValidHTTPVersion(httpVersion))
            throw std::runtime_error("HTTP version not valid");
        // Checking if path is valid
        if (!isValidPathFormat(path))
            throw std::runtime_error("Path format not valid");
        // Method is set
        setField(METHOD, method);
        // Path is set
        setField(PATH, path);
        // HTTP versión is set
        setField(HTTP_VERSION, httpVersion);
    }
    else
        throw std::runtime_error("Empty HTTP request");
    // Read and process remaining lines
    while (std::getline(iss, line))
    {
        // Erase '\r' if present
        if (!line.empty() && line[line.size() - 1] == '\r')
            line.erase(line.size() - 1); 
        // Find headers end
        if (line.empty())
            break;
        std::size_t pos = line.find(':');
        if (pos != std::string::npos)
        {
            std::string fieldName = line.substr(0, pos);
            std::string fieldValue = trim(line.substr(pos + 1));
            std::transform(fieldName.begin(), fieldName.end(), fieldName.begin(), ::tolower);
            if (fieldName == "host")
            {
                setField(HOST, fieldValue);
                fieldFound[HOST] = true;
            }
            else if (fieldName == "connection")
            {
                setField(CONNECTION, fieldValue);
                fieldFound[CONNECTION] = true;
            }
            else if (fieldName == "content-length")
            {
                setField(CONTENT_LENGTH, fieldValue);
                fieldFound[CONTENT_LENGTH] = true;
            }
            else if (fieldName == "content-type")
            {
                setField(CONTENT_TYPE, fieldValue);
                fieldFound[CONTENT_TYPE] = true;
            }
            else if (fieldName == "transfer-encoding")
            {
                setField(TRANSFER_ENCODING, fieldValue);
                fieldFound[TRANSFER_ENCODING] = true;
            }
        }
    }
    // If host is not found or it is empty throw an exception
    if (!fieldFound[HOST] || fieldValues[HOST].empty())
        throw std::runtime_error("Host field not found or empty");
    // If connection is not given, then connection value is "keep-alive"
    if (!fieldFound[CONNECTION])
    {
        setField(CONNECTION, "keep-alive");
        fieldFound[CONNECTION] = true;
    }
    // POST body management
    if (fieldValues[METHOD] == "POST")
    {
        if ((!fieldFound[CONTENT_LENGTH] || fieldValues[CONTENT_LENGTH].empty()) && (!fieldFound[TRANSFER_ENCODING] || fieldValues[TRANSFER_ENCODING].empty()))
            throw std::runtime_error("Content-Length or Transfer-Encoding field must be present");
        if (fieldFound[CONTENT_LENGTH] && fieldFound[TRANSFER_ENCODING])
            throw std::runtime_error("Only one of Content-Length or Transfer-Encoding must be present");
        if (fieldFound[CONTENT_TYPE] && fieldValues[CONTENT_TYPE].find('/') == std::string::npos)
            throw std::runtime_error("Content-Type format is not valid");
        if (fieldFound[CONTENT_LENGTH])
        {
            // Clean errno to detect overflow errors
            errno = 0;
            length = strtoul(fieldValues[CONTENT_LENGTH].c_str(), &end, 10);
            // If end does not point to the end of the string or if an overflow is detected
            if (*end != '\0' || errno == ERANGE)
                throw std::runtime_error("Conversion error: Content-Length is not a valid number or out of range");
            // Read body
            std::string bodyTemp;
            std::getline(iss, bodyTemp);
            // If \r is present it is erased
            if (!bodyTemp.empty() && bodyTemp[bodyTemp.size() - 1] == '\r')
                bodyTemp.erase(bodyTemp.size() - 1);
            setField(BODY, trim(bodyTemp));
            if (fieldValues[BODY].size() != length)
                throw std::runtime_error("Content-Length does not match the body length");
        }
        else if (fieldFound[TRANSFER_ENCODING] && fieldValues[TRANSFER_ENCODING] == "chunked")
        {
            // Implementar el tratamiento del cuerpo de la petición HTTP cuando se utiliza la codificación de transferencia "chunked"
            // Read and process chunks
            // Checks chunks lengths against HTTP request leghts
            // Last chunk lenght must be 0
            // Checks If any of the lengths is not a number o there is an overflow 
            while (std::getline(iss, line))
            {
                // If '\r' is present it is erased
                if (!line.empty() && line[line.size() - 1] == '\r')
                    line.erase(line.size() - 1);
                // errno is cleaned to detect overflow errors
                errno = 0;
                length = strtoul(line.c_str(), &end, 16);
                if (*end != '\0' || errno == ERANGE)
                    // if end doesn't points to string end or there is an overflow an exception is thrown
                    throw std::runtime_error("Conversion error: Chunk length is not a valid number or out of range");
                // If length is 0 the loop is broken (end of body)
                if (length == 0)
                    break;
                 // Read chunk
                std::string chunk;
                std::getline(iss, chunk);
                // if '\r' is present it is erased 
                if (!chunk.empty() && chunk[chunk.size() - 1] == '\r')
                    chunk.erase(chunk.size() - 1);
                // Comparison between chunk real length and HTTP request length
                if (chunk.size() != length)
                {
                    // If both lenghts are not equal an exception is thrown
                    if (chunk.size() > length)
                        throw std::runtime_error("Chunk length is less than the real length");
                    else
                        throw std::runtime_error("Chunk length is greater than the real length");
                }
                // Add chunk to body
                bodyStream << chunk;
            }
            // If last chunk length is not 0 an exception is thrown
            if (length != 0)
                throw std::runtime_error("Last chunk length is not 0");
            // Body is added
            setField(BODY, bodyStream.str());
        }
        // If Transfer-Encoding is not chunked an exception is thrown
        else
            throw std::runtime_error("Transfer-Encoding format is not valid");
    }
}

// Get field value
std::string HTTPRequest::getField(FieldType field) const
{
    std::map<FieldType, std::string>::const_iterator it = fieldValues.find(field);
    if (it != fieldValues.end())
        return it->second;
    return ("");
}
// Set field value
void HTTPRequest::setField(FieldType field, const std::string& value)
{
    if (!fieldSet[field])
    {
        fieldValues[field] = value;
        fieldSet[field] = true;
    }
    else
        throw std::runtime_error("Only one value for each field is allowed");
}
// Copy constructor
HTTPRequest::HTTPRequest(const HTTPRequest &httpRequest)
{
    fieldValues = httpRequest.fieldValues;
    fieldSet = httpRequest.fieldSet;
    fieldFound = httpRequest.fieldFound;
}
// Assignation operator
HTTPRequest& HTTPRequest::operator=(const HTTPRequest &httpRequest)
{
    if (this != &httpRequest) // Verificar auto-asignación
    {
        fieldValues = httpRequest.fieldValues;
        fieldSet = httpRequest.fieldSet;
        fieldFound = httpRequest.fieldFound;
    }
    return (*this);
}
