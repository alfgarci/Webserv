#include "HTTPRequestParse/HTTPRequestParse.hpp"
#include "ServerInfo/ServerInfo.hpp"
#include "tester/tester.hpp"

int test_HttpRequestParser(int argc, char *argv[])
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

void	test_ServerInfo(void)
{
	tester	t;
	int		test_number;

	test_number = 1;
	cout << "TEST_CHECKER" << endl;
	cout << "----------------------------------" << endl;
	t.test_check_indentation(test_number);
	t.test_check_indentation_level(test_number);
	t.test_check_for_indentation_token(test_number);
	t.test_check_for_assignment_token(test_number);
	t.test_check_for_keyword_in_line(test_number);
	t.test_check_syntax(test_number);
	t.test_check_for_keyword(test_number);
	cout << endl << "TEST IS_FUNS" << endl;
	cout << "----------------------------------" << endl;
	t.test_is_char_in_keyword_set(test_number);
	t.test_is_keyword_in_set(test_number);
}

# define RUN_TEST_INFO 0
# define RUN_TEST_HTTPRREQUESTPARSE 0

int	main(int argc, char **argv)
{
	if (RUN_TEST_HTTPRREQUESTPARSE)
		test_HttpRequestParser(argc, argv);
	if (RUN_TEST_INFO)
	{
		test_ServerInfo();
		try
		{
			list<t_server> s = ServerInfo::store_file("tester/test_files/right_file.test");
			ServerInfo::print_t_server(s.front());
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
}
