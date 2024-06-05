#include "../tester.hpp"

void	tester::test_CheckIndentation(int test_number)
{
	std::fstream	fs;
	string			str;
	bool			flag;

	flag = false;
	fs.open("tester/test_files/bad_indentation.test", std::fstream::in);
	while (std::getline(fs, str))
	{
		if (CheckIndentation(str))
			flag = true;
	}
	if (!flag)
		cout << RED << TEST_FAILED;
	else
		cout << GREEN << TEST_PASSED;
	cout << RESET << test_number << endl;
	fs.close();
}
