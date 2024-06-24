#include "../ServerInfo.hpp"

void ServerInfo::pass_keyword_set_chars(string::iterator &it, string &s)
{
	while
	(
		it != s.end()
		&& ServerInfo::is_char_in_keyword_set(*it)
	)
	{
		it++;
	}
}
