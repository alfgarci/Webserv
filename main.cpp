#include "HTTPRequest.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Use: " << argv[0] << " <HTTP request>" << std::endl;
        return 1;
    }

    std::string httpRequest = argv[1];
    try {
        HTTPRequest request(httpRequest);
        std::cout << "Method: " << request.getField(HTTPRequest::METHOD) << std::endl;
        std::cout << "Path: " << request.getField(HTTPRequest::PATH) << std::endl;
        std::cout << "Version: " << request.getField(HTTPRequest::HTTP_VERSION) << std::endl;
        std::cout << "Host: " << request.getField(HTTPRequest::HOST) << std::endl;
        std::cout << "Connection: " << request.getField(HTTPRequest::CONNECTION) << std::endl;
        if (request.getField(HTTPRequest::METHOD) == "POST")
        {
            std::string test;
            if (!test.empty())
                std::cout << "Content-Type: " << request.getField(HTTPRequest::CONTENT_TYPE) << std::endl;
            test = request.getField(HTTPRequest::CONTENT_LENGTH);
            if (!test.empty())
                std::cout << "Content-Length: " << request.getField(HTTPRequest::CONTENT_LENGTH) << std::endl;
            test = request.getField(HTTPRequest::TRANSFER_ENCODING);
            if (!test.empty())
                std::cout << "Transfer-Encoding: " << request.getField(HTTPRequest::TRANSFER_ENCODING) << std::endl;
            test = request.getField(HTTPRequest::BODY);
            if (!test.empty())
                std::cout << "Body: " << request.getField(HTTPRequest::BODY) << std::endl;
            test = request.getField(HTTPRequest::CONTENT_TYPE);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}

