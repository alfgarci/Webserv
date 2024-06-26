#include "ServerInfo/ServerInfo.hpp"
#include "tester/tester.hpp"

void	test_collection(void)
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

int	main(void)
{
	test_collection();
}
