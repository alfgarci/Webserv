# include "../tester.hpp"

void	tester::test_check_syntax(int &test_number)
{
	std::fstream	fs;
	string			str;
	bool			flag;
	int				line;

	flag = true;
	line = -1;
	fs.open("tester/test_files/check_syntax.test", std::fstream::in);
	//-------------------------------TEST
	std::getline(fs, str);
	try
	{
		check_syntax(str, base_level, ++line);
	}
	catch (const std::exception &e)
	{
		flag = false;
	}
	if (flag)
		cout << RED << TEST_FAILED;
	else
		cout << GREEN << TEST_PASSED;
	cout << RESET << test_number << endl;
	test_number++;
	//-------------------------------TEST
	flag = true;
	std::getline(fs, str);
	try
	{
		check_syntax(str, base_level, ++line);
	}
	catch(const std::exception& e)
	{
		flag = false;
	}
	if (flag)
		cout << RED << TEST_FAILED;
	else
		cout << GREEN << TEST_PASSED;
	cout << RESET << test_number << endl;
	test_number++;
	//-------------------------------TEST
	flag =  true;
	std::getline(fs, str);
	try
	{
		check_syntax(str, base_level, ++line);
	}
	catch(const std::exception& e)
	{
		flag = false;
	}
	if (flag)
		cout << RED << TEST_FAILED;
	else
		cout << GREEN << TEST_PASSED;
	cout << RESET << test_number << endl;
	test_number++;
	//-------------------------------TEST
	std::getline(fs, str);
	try
	{
		check_syntax(str, base_level, ++line);
	}
	catch(const std::exception& e)
	{
		cout << e.what() << endl;
		flag = true;
	}
	if (flag)
		cout << RED << TEST_FAILED;
	else
		cout << GREEN << TEST_PASSED;
	cout << RESET << test_number << endl;
	test_number++;
	//-------------------------------TEST
	flag = false;
	std::getline(fs, str);
	try
	{
		check_syntax(str, server_level, ++line);
	}
	catch(const std::exception& e)
	{
		flag = true;
	}
	if (flag)
		cout << RED << TEST_FAILED;
	else
		cout << GREEN << TEST_PASSED;
	cout << RESET << test_number << endl;
	test_number++;
	//-------------------------------TEST
	flag = false;
	std::getline(fs, str);
	try
	{
		check_syntax(str, server_level, ++line);
	}
	catch(const std::exception& e)
	{
		flag = true;
	}
	if (flag)
		cout << RED << TEST_FAILED;
	else
		cout << GREEN << TEST_PASSED;
	cout << RESET << test_number << endl;
	test_number++;
	//-------------------------------TEST
	flag = false;
	std::getline(fs, str);
	try
	{
		check_syntax(str, route_level, ++line);
	}
	catch(const std::exception& e)
	{
		flag = true;
	}
	if (flag)
		cout << RED << TEST_FAILED;
	else
		cout << GREEN << TEST_PASSED;
	cout << RESET << test_number << endl;
	test_number++;
	//-------------------------------TEST
	flag = false;
	std::getline(fs, str);
	try
	{
		check_syntax(str, route_level, ++line);
	}
	catch(const std::exception& e)
	{
		flag = true;
	}
	if (flag)
		cout << RED << TEST_FAILED;
	else
		cout << GREEN << TEST_PASSED;
	cout << RESET << test_number << endl;
	test_number++;
	fs.close();
}
