#include "../ServerInfo.hpp"

/*
@brief This funtion check if the given string contain the right indentation,
a set of '\\t' followed by a alphabetic char.
@param s the string to check.
@return True if it have the right structure, False if not.
*/
bool	ServerInfo::check_indentation(string s)
{
	string::iterator	it = s.begin();

	it = s.begin();
	while
	(
		it != s.end()
		&& *it == TOKEN_SPACE 
	)
		it++;
	if
	(
		*it != TOKEN_SPACE
		&& !isalpha(*it)
		&& *it != NEW_LINE
	)
	{
		return (false);
	}
	return (true);
}
