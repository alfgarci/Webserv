#include "../tester.hpp"

void	tester::test_is_char_in_keyword_set(int &test_number)
{
	bool	flag;

	flag = false;

	if (!is_char_in_keyword_set('c'))
		flag = true;
	if (!is_char_in_keyword_set('A'))
		flag = true;
	if (!is_char_in_keyword_set('_'))
		flag = true;
	if (is_char_in_keyword_set('9'))
		flag = false;
	if (is_char_in_keyword_set('.'))
		flag = false;
	if (is_char_in_keyword_set('+'))
		flag = false;
	if (is_char_in_keyword_set('-'))
		flag = false;
	if (is_char_in_keyword_set('>'))
		flag = false;
	if (is_char_in_keyword_set(':'))
		flag = false;
	if (flag)
		cout << RED << TEST_FAILED;
	else
		cout << GREEN << TEST_PASSED;
	cout << RESET << test_number << endl;
	test_number++;
}
