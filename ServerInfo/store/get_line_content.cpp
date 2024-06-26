#include "../ServerInfo.hpp"

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

	string				result(it, line.end());

	return (result);
}
