#include "../tester.hpp"

void	tester::test_check_for_keyword(int &test_number)
{
	bool	flag;
	string	s;

	flag = false;
	s = "		hello=a";
	if (check_for_keyword(s, Base_dictionary.at(server)))
		flag = true;
	s = (string)(SERVER_KEYWORD) + ":";
	if (!check_for_keyword(s, Base_dictionary.at(server)))
		flag = true;
	if (check_for_keyword(s, Route_dictionary.at(http_redirections)))
		flag = true;
	if (flag)
		cout << RED << TEST_FAILED;
	else
		cout << GREEN << TEST_PASSED;
	cout << RESET << test_number << endl;
	test_number++;
}
