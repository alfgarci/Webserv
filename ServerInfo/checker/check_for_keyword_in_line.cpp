#include "../ServerInfo.hpp"

/*
@brief Check if the line contain a keyword
@param s the line to be checked
@param indentation_level check the level of indentation
@return True if it contains any keyword, False if not 
*/
bool	ServerInfo::check_for_keyword_in_line(string s, int indentation_level)
{
	string::iterator	it_start_of_keyword;
	string::iterator	it_end_of_keyword;

	it_start_of_keyword = s.begin();
	pass_tabulations(it_start_of_keyword, s);
	it_end_of_keyword = it_start_of_keyword;
	pass_keyword_set_chars(it_end_of_keyword, s);

	string				tmp_keyword(it_start_of_keyword, it_end_of_keyword);

	if (is_keyword_in_set(tmp_keyword, Indentaton_dictionary.at(indentation_level)))
		return (true);
	return (false);
}
