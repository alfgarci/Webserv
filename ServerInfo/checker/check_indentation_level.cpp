#include "../ServerInfo.hpp"

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
