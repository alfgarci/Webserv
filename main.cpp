#include "HTTPRequestCreator.hpp"

int main()
{
    HTTPRequestCreator requestCreator;
    std::string request = requestCreator.createHTTPRequest("GET", "www.google.com", "/", "", 80);
    std::cout << request << std::endl;
    request = requestCreator.createHTTPRequest("POST", "www.google.com", "/", "Hello World", 433);
    std::cout << request << std::endl;
    std::string chunk1 = "4\r\nHola\r\n";
    std::string chunk2 = "5\r\nMundo\r\n";
    std::string body = chunk1 + chunk2;
    request = requestCreator.createHTTPRequest("POST", "www.google.com", "/", body, 180, true);
    std::cout << request << std::endl;
    request = requestCreator.createHTTPRequest("DELETE", "www.google.com", "/", "", 0);
    std::cout << request << std::endl;
    return (0);
}
