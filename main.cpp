#include "HTTPRequestParse.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Use: " << argv[0] << " <HTTP request>" << std::endl;
        return 1;
    }

    std::string HTTPRequest = argv[1];
    try {
        HTTPRequestParse request(HTTPRequest);
        std::cout << "Method: " << request.getField(HTTPRequestParse::METHOD) << std::endl;
        std::cout << "Path: " << request.getField(HTTPRequestParse::PATH) << std::endl;
        std::cout << "Version: " << request.getField(HTTPRequestParse::HTTP_VERSION) << std::endl;
        std::cout << "Host: " << request.getField(HTTPRequestParse::HOST) << std::endl;
        std::cout << "Port: " << request.getField(HTTPRequestParse::PORT) << std::endl;
        std::cout << "Connection: " << request.getField(HTTPRequestParse::CONNECTION) << std::endl;
        if (request.getField(HTTPRequestParse::METHOD) == "POST")
        {
            std::string test;
            if (!test.empty())
                std::cout << "Content-Type: " << request.getField(HTTPRequestParse::CONTENT_TYPE) << std::endl;
            test = request.getField(HTTPRequestParse::CONTENT_LENGTH);
            if (!test.empty())
                std::cout << "Content-Length: " << request.getField(HTTPRequestParse::CONTENT_LENGTH) << std::endl;
            test = request.getField(HTTPRequestParse::TRANSFER_ENCODING);
            if (!test.empty())
                std::cout << "Transfer-Encoding: " << request.getField(HTTPRequestParse::TRANSFER_ENCODING) << std::endl;
            test = request.getField(HTTPRequestParse::BODY);
            if (!test.empty())
                std::cout << "Body: " << request.getField(HTTPRequestParse::BODY) << std::endl;
            test = request.getField(HTTPRequestParse::CONTENT_TYPE);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}

