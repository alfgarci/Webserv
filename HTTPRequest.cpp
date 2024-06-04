// HTTPRequest.hpp

#include "HTTPRequest.hpp"

std::vector<std::string> HTTPRequest::validMethods;
bool HTTPRequest::initialized = false;
const std::string methods[] = {"GET", "POST", "DELETE"};
const int numMethods = sizeof(methods) / sizeof(methods[0]);

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

void HTTPRequest::initializeValidMethods()
{
    for (int i = 0; i < numMethods; ++i)
        validMethods.push_back(methods[i]);
}

bool HTTPRequest::isValidHTTPMethod(const std::string& method)
{
    if (!initialized)
    {
        initializeValidMethods();
        initialized = true;
    }
    return std::find(validMethods.begin(), validMethods.end(), method) != validMethods.end();
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
    return true;
}

std::string HTTPRequest::trim(const std::string& str)
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return (first == std::string::npos || last == std::string::npos) ? "" : str.substr(first, last - first + 1);
}

void HTTPRequest::parse(const std::string& request)
{
    char *end;
    std::istringstream iss(request);
    std::string line;
    std::stringstream bodyStream;
    unsigned long length;

    std::getline(iss, line);
    std::istringstream lineStream(line);
    std::string method, path, httpVersion;
    lineStream >> method >> path >> httpVersion;
    if (!isValidHTTPMethod(method))
        throw std::runtime_error("HTTP method not valid");
    if (!isValidHTTPVersion(httpVersion))
        throw std::runtime_error("HTTP version not valid");
    if (!isValidPathFormat(path))
        throw std::runtime_error("Path format not valid");
    setField(METHOD, method);
    setField(PATH, path);
    setField(HTTP_VERSION, httpVersion);

    // Leer y procesar las líneas restantes
    while (std::getline(iss, line))
    {
        // Find headers end
        if (line == "\r" || line.empty())
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
    // Si no se encontró el campo Host o está vacío, lanzar una excepción
    if (!fieldFound[HOST] || fieldValues[HOST].empty())
        throw std::runtime_error("Host field not found or empty");
    if (!fieldFound[CONNECTION] && fieldValues[HTTP_VERSION] == "HTTP/1.1")
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
            length = strtoul(fieldValues[CONTENT_LENGTH].c_str(), &end, 10);
            if (*end != '\0')
                throw std::runtime_error("Conversion error: Content-Length is not a valid number");
            // Read body
            std::string bodyTemp;
            std::getline(iss, bodyTemp);
            setField(BODY, trim(bodyTemp));
            if (fieldValues[BODY].size() != length)
                throw std::runtime_error("Content-Length does not match the body length");
        }
        else if (fieldFound[TRANSFER_ENCODING] && fieldValues[TRANSFER_ENCODING] == "chunked")
        {
            while (std::getline(iss, line))
            {
                length = strtoul(line.c_str(), &end, 16);
                if (*end != '\0')
                    throw std::runtime_error("Chunk size conversion error");
                if (length == 0)
                {
                    std::getline(iss, line); // Leer el último \r\n después del chunk 0
                    break;
                }
                std::string chunk(length, '\0');
                iss.read(&chunk[0], (std::streamsize)length);
                bodyStream << chunk;
                iss.ignore(1); // Ignorar \n después del chunk
            }
            setField(BODY, bodyStream.str());
            if (fieldValues[BODY].empty())
                throw std::runtime_error("Transfer-Encoding mismatch: body is empty for chunked encoding");
        }
    }
}

std::string HTTPRequest::getField(FieldType field) const
{
    std::map<FieldType, std::string>::const_iterator it = fieldValues.find(field);
    if (it != fieldValues.end())
        return it->second;
    return "";
}

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

const std::vector<std::string>& HTTPRequest::getValidMethods()
{
    return validMethods;
}
