#include "../ServerInfo.hpp"

/*
@brief Check_if_the selected_keyword_is_in_the_selected_set
@param keyword the string to check
@param set the set of keywords to check with
@return True if the keyword is in the set, False if not
*/
bool	ServerInfo::is_keyword_in_set(string keyword, Dictionary set)
{
	Dictionary::iterator	it;
	bool	flag;

	flag = false;
	it = set.begin();
	while (it != set.end())
	{
		if (it->second == keyword)
			flag = true;
		it++;
	}
	return (flag);
}
