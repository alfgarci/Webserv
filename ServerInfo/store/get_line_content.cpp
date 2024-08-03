#include "../ServerInfo.hpp"

/*
@brief get the content of a line after the TOKEN_ASSIGNMENT, and return it as a string
@return a string with the content
@param line the line to be extracted
*/
string	ServerInfo::get_line_content(string line)
{
	string::iterator	it;

	it = line.begin();
	while
	(
		it != line.end()
		&& *it != TOKEN_ASSIGNMENT
	)
	{
		it++;
	}
	it++;

	string				result(it, line.end());

	return (result);
}
