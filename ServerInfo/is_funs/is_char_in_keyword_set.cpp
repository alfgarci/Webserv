#include "../ServerInfo.hpp"

/*
@param c the char to check.
@brief this funtion check if said char is in the "set" of accepted chars for a keyword.
@return True if the char is in the set and False if not.
*/
bool	ServerInfo::is_char_in_keyword_set(char c)
{
	if (c >= 'a' && c <= 'z')
		return (true);
	else if (c >= 'A' && c <= 'Z')
		return (true);
	else if (c == '_')
		return (true);
	return (false);
}
