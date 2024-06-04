#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include <algorithm>
#include <cctype>
#include <cerrno>
#include <cstdio>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <cstring>
#include <vector>

// HTTPRequest class
class HTTPRequest
{
public:
    enum FieldType {
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

private:
    std::map<FieldType, std::string> fieldValues;
    std::map<FieldType, bool> fieldFound;
    std::map<FieldType, bool> fieldSet;
    static std::vector<std::string> validMethods;
    static bool initialized;
    static void initializeValidMethods();
    static bool isValidHTTPMethod(const std::string& method);
    static bool isValidHTTPVersion(const std::string& version);
    static bool isValidPathFormat(const std::string& path);
    static std::string trim(const std::string& str);

public:
    // Constructor
    explicit HTTPRequest(const std::string& request);
    // Function to check HTTP request
    void parse(const std::string& request);
    // Retrieve valid HTTP methods
    static const std::vector<std::string>& getValidMethods();
    // Get field value
    std::string getField(FieldType field) const;
    // Set field value
    void setField(FieldType field, const std::string& value);
};

#endif // HTTP_REQUEST_HPP
