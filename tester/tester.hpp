#ifndef TESTER_HPP
# define TESTER_HPP

# pragma once

# include <iostream>
# include <string>
# include "../ServerInfo/ServerInfo.hpp"

using std::cout;
using std::string;
using std::cin;
using std::endl;
using std::cerr;

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define TEST_PASSED "Test Passed "
# define TEST_FAILED "Test Failed "
# define RESET "\033[0m"

# define TESTER_CONSTRUCTOR_LOG_COLOR "\033[1;30m"
# define TESTER_RESET_COLOR "\033[0m"
# define TESTER_DEFAULT_DO_LOG false

# define TESTER_DEFAULT_CONSTRUCTOR_LOG "tester default constructor called"
# define TESTER_COPY_CONSTRUCTOR_LOG "tester copy constructor called"
# define TESTER_COPY_ASSIGNMENT_LOG "tester copy assignment called"
# define TESTER_DESTRUCTOR_LOG "tester destructor called"

class tester : public ServerInfo
{
	public:
		//CONSTRUCTORS
		//-------------------------------------------------------

		tester();
		tester(bool log);
		tester(const tester &tester);
		~tester();
		tester & operator = (const tester &tester);

		//TEST_CHECKER
		//-------------------------------------------------------

		void	test_check_indentation(int &test_number);
		void	test_check_indentation_level(int &test_number);
		void	test_check_for_indentation_token(int &test_number);

		//TEST_IS_FUNS
		//-------------------------------------------------------

		void	test_is_char_in_keyword_set(int &test_number);

		//-------------------------------------------------------

	protected:
		bool	_do_log;

	private:
		//LOG
		//-------------------------------------------------------

		void	constructor_log(string s);
};

#endif
