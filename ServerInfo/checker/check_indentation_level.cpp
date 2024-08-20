#include "../ServerInfo.hpp"

//SHIT HAPPENS
static int select_right_indentation_level(int expected_level)
{
	int		indentation_level;

	indentation_level = expected_level;
	if (expected_level == error_level)
		indentation_level = 2;
	return (indentation_level);		
}

/*
@brief Check if the indentation level is related with the expected level of indentation.
@param s string to check.
@param expected_level nº of indentation.
@return True is the level is equal to the expected, else return False.
*/
bool	ServerInfo::check_indentation_level(string s, int expected_level)
{
	int		current_level;

	current_level = 0;
	expected_level = select_right_indentation_level(expected_level);
	for
	(
		string::iterator	it = s.begin();
		it != s.end() && *it == TOKEN_SPACE;
		it++
	)
	{
		if (current_level > expected_level)
			return (false);
		current_level++;
	}
	if (current_level == expected_level)
		return (true);
	return (false);
}
