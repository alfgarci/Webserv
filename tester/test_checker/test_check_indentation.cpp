#include "../tester.hpp"

static void	test_bad(int &test_number)
{
	std::fstream	fs;
	string			str;
	bool			flag;

	flag = false;
	fs.open("tester/test_files/bad_indentation.test", std::fstream::in);
	while (std::getline(fs, str))
	{
		if (tester::ServerInfo::check_indentation(str))
			flag = true;
	}
	fs.close();
	if (!flag)
		cout << RED << TEST_FAILED;
	else
		cout << GREEN << TEST_PASSED;
	cout << RESET << test_number << endl;
	test_number++;
}

static void test_good(int &test_number)
{
	std::fstream	fs;
	string			str;
	bool			flag;

	flag = false;
	fs.open("tester/test_files/good_indentation.test", std::fstream::in);
	while (std::getline(fs, str))
	{
		if (tester::ServerInfo::check_indentation(str))
			flag = true;
	}
	fs.close();
	if (!flag)
		cout << RED << TEST_FAILED;
	else
		cout << GREEN << TEST_PASSED;
	cout << RESET << test_number << endl;
	test_number++;
}

void	tester::test_check_indentation(int &test_number)
{
	test_bad(test_number);
	test_good(test_number);
}
