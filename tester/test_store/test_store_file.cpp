#include "../tester.hpp"

void	tester::test_store_file(string path, int &test_number, bool expected_result)
{
	bool						flag;
	list<t_server>::iterator	it;

	flag = false;
	try
	{
		list<t_server> s = ServerInfo::store_file(path);
		it = s.begin();
		while (it != s.end())
		{
			print_t_server(*it);
			it++;
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		flag = true;
	}
	if (flag == expected_result)
		cout << RED << TEST_FAILED;
	else
		cout << GREEN << TEST_PASSED;
	cout << RESET << test_number << endl;
	test_number++;
}
