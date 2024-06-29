#include "../tester.hpp"

void	tester::test_is_keyword_in_set(int &test_number)
{
	bool	flag;
	string	s;

	flag = false;
	s = "hello";
	if (is_keyword_in_set(s, Base_dictionary))
		flag = true;
	s = SERVER_KEYWORD;
	if (!is_keyword_in_set(s, Base_dictionary))
		flag = true;
	if (is_keyword_in_set(s, Server_dictionary))
		flag = true;
	s = ROUTE_KEYWORD;
	if (!is_keyword_in_set(s, Server_dictionary))
		flag = true;
	if (is_keyword_in_set(s, Route_dictionary))
		flag = true;
	if (is_keyword_in_set(s, Route_dictionary))
		flag = true;
	s = ACCEPTED_HTTP_METHODS_KEYWORD;
	if (!is_keyword_in_set(s, Route_dictionary))
		flag = true;
	if (!is_keyword_in_set(s, Route_dictionary))
		flag = true;
	if (flag)
		cout << RED << TEST_FAILED;
	else
		cout << GREEN << TEST_PASSED;
	cout << RESET << test_number << endl;
	test_number++;
}
