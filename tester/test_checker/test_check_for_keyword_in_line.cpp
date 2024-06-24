#include "../tester.hpp"


void	tester::test_check_for_keyword_in_line(int &test_number)
{
	bool	flag;
	string	s;

	flag = false;
	s = "		hello=a";
	if (check_for_keyword_in_line(s, base_level))
		flag = true;
	s = (string)(SERVER_KEYWORD) + ":";
	if (!check_for_keyword_in_line(s, base_level))
		flag = true;
	if (check_for_keyword_in_line(s, server_level))
		flag = true;
	if (flag)
		cout << RED << TEST_FAILED;
	else
		cout << GREEN << TEST_PASSED;
	cout << RESET << test_number << endl;
	test_number++;
}
