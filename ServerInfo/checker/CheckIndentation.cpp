#include "../ServerInfo.hpp"

# define TABULATION '\t'

/*
@brief This funtion check if the given string contain the right indentation,
a set of \t followed by a alphabetic char.void
@param s the string to check.
@return True if it have the right structure, False if not.
*/
bool	ServerInfo::CheckIndentation(string s)
{
	string::iterator	it = s.begin();

	it = s.begin();
	while
	(
		it != s.end()
		&& *it == TABULATION
	)
		it++;
	if
	(
		*it != TABULATION
		&& !isalpha(*it)
	)
	{
		return (false);
	}
	return (true);
}
