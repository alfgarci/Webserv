#include "../tester.hpp"

void	tester::test_check_for_indentation_token(int &test_number)
{
	std::fstream	fs;
	string			str;
	bool			flag;

	flag = false;
	fs.open("tester/test_files/test_indentation_token.test", std::fstream::in);
	std::getline(fs, str);
	if (!check_for_indentation_token(str))
		flag = true;
	std::getline(fs, str);
	if (check_for_indentation_token(str))
		flag = true;
	std::getline(fs, str);
	if (check_for_indentation_token(str))
		flag = true;
	std::getline(fs, str);
	if (check_for_indentation_token(str))
		flag = true;
	std::getline(fs, str);
	if (check_for_indentation_token(str))
		flag = true;
	std::getline(fs, str);
	if (!check_for_indentation_token(str))
		flag = true;
	fs.close();
	if (flag)
		cout << RED << TEST_FAILED;
	else
		cout << GREEN << TEST_PASSED;
	cout << RESET << test_number << endl;
	test_number++;
}
