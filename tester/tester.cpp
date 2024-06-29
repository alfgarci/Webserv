#include "tester.hpp"

#pragma region CONSTRUCTOR

void	tester::constructor_log(string s)
{
	if (_do_log)
	{
		cout << TESTER_CONSTRUCTOR_LOG_COLOR;
		cout << s;
		cout << TESTER_RESET_COLOR << endl;
	}
}

tester::tester() :
_do_log(TESTER_DEFAULT_DO_LOG)
{
	constructor_log(TESTER_DEFAULT_CONSTRUCTOR_LOG);
}

tester::tester(bool log) :
_do_log(log)
{
	constructor_log(TESTER_DEFAULT_CONSTRUCTOR_LOG);
}

tester::~tester()
{
	constructor_log(TESTER_DESTRUCTOR_LOG);
}

tester::tester(const tester &tester) :
_do_log(tester._do_log)
{
	constructor_log(TESTER_COPY_CONSTRUCTOR_LOG);
}

tester & tester::operator= (const tester &tester)
{
	constructor_log(TESTER_COPY_ASSIGNMENT_LOG);
	if (this != & tester)
	{
	}
	this->_do_log = tester._do_log;
	return (*this);
}

#pragma endregion
