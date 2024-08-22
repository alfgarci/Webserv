// HTTPRequestParse.cpp

// Files included
#include "HTTPRequestParse.hpp"

// Default constructor
HTTPRequestParse::HTTPRequestParse(void)
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
HTTPRequestParse::HTTPRequestParse(const string& request)
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
HTTPRequestParse::~HTTPRequestParse()
{

}

bool HTTPRequestParse::isValidHTTPMethod(const string& method)
{
    if (method == METHOD_GET || method == METHOD_POS || method == METHOD_DEL)
        return (true);
    return (false);
}

bool HTTPRequestParse::isValidHTTPVersion(const string& version)
{
    if (version.substr(0, HTTP_LENGTH) == HTTP)
    {
        string versionNumber = version.substr(HTTP_LENGTH);
        return (versionNumber == VERSION);
    }
    throw runtime_error(VERSION_ERROR);
}
// Check path field
bool HTTPRequestParse::isValidPathFormat(const string& path)
{
    if (path.empty() || path[0] != SLASH)
        return false;
    for (size_t i = 0; i < path.size(); ++i)
    {
        char c = path[i];
        if (!(isalnum(c) || c == SLASH || c == HYPHEN || c == UNDERSCORE || c == POINT))
            return (false);
    }
    return (true);
}
// Function to erase unnecessary spaces
string HTTPRequestParse::trim(const string& str)
{
    size_t first = str.find_first_not_of(SPACE);
    size_t last = str.find_last_not_of(SPACE);
    return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
}

// Function to check HTTP request format
void HTTPRequestParse::parse(const string& request)
{
    char *end;
    istringstream iss(request);
    string line;
    stringstream bodyStream;
    unsigned long length;
    string port;

    // Read request first line
    if (getline(iss, line))
    {
        // If there is an '\r' it is erased
        if (!line.empty() && line[line.size() - 1] == CR)
            line.erase(line.size() - 1);
        istringstream lineStream(line);
        string method, path, httpVersion;
        lineStream >> method >> path >> httpVersion;
        // Checking if method is valid
        if (!isValidHTTPMethod(method))
            throw runtime_error(METHOD_ERROR);
        // Checking if HTTP version is valid
        if (!isValidHTTPVersion(httpVersion))
            throw runtime_error(VERSION_ERROR);
        // Checking if path is valid
        if (!isValidPathFormat(path))
            throw runtime_error(PATH_ERROR);
        // Method is set
        setField(METHOD, method);
        // Path is set
        path = "." + path;
        setField(PATH, path);
        // HTTP versión is set
        setField(HTTP_VERSION, httpVersion);
    }
    else
        return ;
        //throw runtime_error(EMPTY_REQUEST);
    // Read and process remaining lines
    while (getline(iss, line))
    {
        // Erase '\r' if present
        if (!line.empty() && line[line.size() - 1] == CR)
            line.erase(line.size() - 1); 
        // Find headers end
        if (line.empty())
            break;
        size_t pos = line.find(COLON);
        pos += 1;
        if (pos != string::npos)
        {
            string fieldName = line.substr(0, pos);
            string fieldValue = trim(line.substr(pos + 1));
            transform(fieldName.begin(), fieldName.end(), fieldName.begin(), ::tolower); 
            if (fieldName == HOST_FIELD)
            {
                // Host and port (if exists) are extracted
                size_t colonPos = fieldValue.find(COLON);
                if (colonPos != string::npos)
                {
                    // If ':' is found we assume there is a port
                    // Host and port are stablished
                    if (fieldValue.substr(0, colonPos) == "localhost")
                        setField(HOST, "127.0.0.1");
                    else    
                        setField(HOST, fieldValue.substr(0, colonPos));
                    fieldFound[HOST] = true;
                    setField(PORT, fieldValue.substr(colonPos + 1));
                    if (fieldValues[PORT].empty())
                        throw runtime_error(EMPTY_PORT);
                    for (size_t i = 0; i < fieldValues[PORT].length(); ++i)
                    {
                        if (!isdigit(fieldValues[PORT][i]))
                            throw runtime_error(PORT_ERROR);
                    }
                    int port;
                    istringstream(fieldValues[PORT]) >> port;
                    if (port < LOWER_PORT_LIMIT || port > UPPER_PORT_LIMIT)
                        throw runtime_error(OUT_OF_RANGE);
                }
                else
                {
                    // If not ':' is found we assume there is no port field and take thedefault value
                    setField(HOST, fieldValue);
                    fieldFound[HOST] = true;
                    setField(PORT, DEFAULT_PORT);
                }    
            }
            else if (fieldName == CONNECTION_FIELD)
            {
                setField(CONNECTION, fieldValue);
                fieldFound[CONNECTION] = true;
            }
            else if (fieldName == CONTENT_LENGTH_FIELD)
            {
                setField(CONTENT_LENGTH, fieldValue);
                fieldFound[CONTENT_LENGTH] = true;
            }
            else if (fieldName == CONTENT_TYPE_FIELD)
            {
                setField(CONTENT_TYPE, fieldValue);
                fieldFound[CONTENT_TYPE] = true;
            }
            else if (fieldName == TRANSFER_ENCODING_FIELD)
            {
                setField(TRANSFER_ENCODING, fieldValue);
                fieldFound[TRANSFER_ENCODING] = true;
            }
        }
    }
    // If host is not found or it is empty throw an exception
    if (!fieldFound[HOST] || fieldValues[HOST].empty())
        throw runtime_error(HOST_ERROR);
    // If connection is not given, then connection value is "keep-alive"
    if (!fieldFound[CONNECTION])
    {
        setField(CONNECTION, KEEP_ALIVE_MODE);
        fieldFound[CONNECTION] = true;
    }
    // POST body management
    if ((fieldValues[METHOD]) == (METHOD_POS))
    {
        if ((!fieldFound[CONTENT_LENGTH] || fieldValues[CONTENT_LENGTH].empty()) && (!fieldFound[TRANSFER_ENCODING] || fieldValues[TRANSFER_ENCODING].empty()))
            throw runtime_error(CL_OR_TE);
        if (fieldFound[CONTENT_LENGTH] && fieldFound[TRANSFER_ENCODING])
            throw runtime_error(ONLY_CL_OR_TE);
        if (fieldFound[CONTENT_TYPE] && fieldValues[CONTENT_TYPE].find(SLASH) == string::npos)
            throw runtime_error(CONTENT_ERROR);
        if (fieldFound[CONTENT_LENGTH])
        {
            // Clean errno to detect overflow errors
            errno = 0;
            length = strtoul(fieldValues[CONTENT_LENGTH].c_str(), &end, DEC_MODE);
            // If end does not point to the end of the string or if an overflow is detected
            if (*end != LINE_END || errno == ERANGE)
                throw runtime_error(CONVERSION_ERROR);
            // Read body
            string bodyTemp(length, 0);
            iss.read(&bodyTemp[0], length);
            setField(BODY, bodyTemp);
            /*
            string bodyTemp;
            getline(iss, bodyTemp);
            // If \r is present it is erased
            if (!bodyTemp.empty() && bodyTemp[bodyTemp.size() - 1] == CR)
                bodyTemp.erase(bodyTemp.size() - 1);
            setField(BODY, trim(bodyTemp));
            */
            if (fieldValues[BODY].size() != length)
                throw runtime_error(CONTENT_LENGHT_ERROR);
        }
        else if (fieldFound[TRANSFER_ENCODING] && fieldValues[TRANSFER_ENCODING] == CHUNKED_MODE)
        {
            // Read and process chunks
            // Checks chunks lengths against HTTP request leghts
            // Last chunk lenght must be 0
            // Checks If any of the lengths is not a number o there is an overflow 
            while (getline(iss, line))
            {
                // If '\r' is present it is erased
                if (!line.empty() && line[line.size() - 1] == CR)
                    line.erase(line.size() - 1);
                // errno is cleaned to detect overflow errors
                errno = 0;
                length = strtoul(line.c_str(), &end, HEX_MODE);
                if (*end != LINE_END || errno == ERANGE)
                    // if end doesn't points to string end or there is an overflow an exception is thrown
                    throw runtime_error(CHUNK_CONVERSION_ERROR);
                // If length is 0 the loop is broken (end of body)
                if (length == 0)
                    break;
                 // Read chunk
                string chunk;
                getline(iss, chunk);
                // if '\r' is present it is erased 
                if (!chunk.empty() && chunk[chunk.size() - 1] == CR)
                    chunk.erase(chunk.size() - 1);
                // Comparison between chunk real length and HTTP request length
                if (chunk.size() != length)
                {
                    // If both lenghts are not equal an exception is thrown
                    if (chunk.size() > length)
                        throw runtime_error(CHUNK_LENGTH_LESS);
                    else
                        throw runtime_error(CHUNK_LENGTH_GREATER);
                }
                // Add chunk to body
                bodyStream << chunk;
            }
            // If last chunk length is not 0 an exception is thrown
            if (length != 0)
                throw runtime_error(LAST_CHUNK_LENGTH_ERROR);
            // Body is added
            setField(BODY, bodyStream.str());
        }
        // If Transfer-Encoding is not chunked an exception is thrown
        else
            throw runtime_error(TRANSFER_ERROR);
    }
}

// Get field value
string HTTPRequestParse::getField(FieldType field) const
{
    map<FieldType, string>::const_iterator it = fieldValues.find(field);
    if (it != fieldValues.end())
        return it->second;
    return ("");
}
// Set field value
void HTTPRequestParse::setField(FieldType field, const string& value)
{
    if (!fieldSet[field])
    {
        fieldValues[field] = value;
        fieldSet[field] = true;
    }
    else
        throw runtime_error(FIELD_MULTIPLE_VALUES);
}
// Copy constructor
HTTPRequestParse::HTTPRequestParse(const HTTPRequestParse &HTTPRequestParse)
{
    fieldValues = HTTPRequestParse.fieldValues;
    fieldSet = HTTPRequestParse.fieldSet;
    fieldFound = HTTPRequestParse.fieldFound;
}
// Assignation operator
HTTPRequestParse& HTTPRequestParse::operator=(const HTTPRequestParse &HTTPRequestParse)
{
    if (this != &HTTPRequestParse)
    {
        fieldValues = HTTPRequestParse.fieldValues;
        fieldSet = HTTPRequestParse.fieldSet;
        fieldFound = HTTPRequestParse.fieldFound;
    }
    return (*this);
}
