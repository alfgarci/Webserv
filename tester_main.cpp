#include "HTTPRequestParse/HTTPRequestParse.hpp"
#include "ServerInfo/ServerInfo.hpp"
#include "tester/tester.hpp"
#include "ServerCore/ServerCore.hpp"

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
    cout << endl << "TEST STORE" << endl;
	cout << "----------------------------------" << endl;
	t.test_store_file("tester/test_files/right_file.test", test_number, true);
	t.test_store_file("tester/test_files/tricky_server.test", test_number, false);
}

# define RUN_TEST_INFO 0
# define RUN_TEST_HTTPRREQUESTPARSE 0
# define RUN_TEST_HTTPRREQUESTCREATOR 0

int	main(int argc, char **argv)
{
    (void)argc;
    ServerInfo info;
	if (RUN_TEST_INFO)
	{
		test_ServerInfo();
	}
	try
	{
		std::list<t_server> listServer = info.store_file(argv[1]);
		ServerCore core(listServer);
		core.prepareServer();
		core.launchServers();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}
