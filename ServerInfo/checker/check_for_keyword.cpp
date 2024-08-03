#include "../ServerInfo.hpp"

/*
@brief Check if the line contain a certain keyword
@param s the line to be checked
@param keyword the keyword to check
@return True if it contains the keyword, False if not 
*/
bool	ServerInfo::check_for_keyword(string s, string keyword)
{
	string::iterator	it_start_of_keyword;
	string::iterator	it_end_of_keyword;

	it_start_of_keyword = s.begin();
	pass_tabulations(it_start_of_keyword, s);
	it_end_of_keyword = it_start_of_keyword;
	pass_keyword_set_chars(it_end_of_keyword, s);

	string				tmp_keyword(it_start_of_keyword, it_end_of_keyword);

	if (tmp_keyword == keyword)
		return (true);
	return (false);
}
