#include "../ServerInfo.hpp"

void	ServerInfo::pass_tabulations(string::iterator &it, string &s)
{

	while 
	(
		it != s.end()
		&& *it == TOKEN_SPACE
	)
	{
		it++;
	}
}
