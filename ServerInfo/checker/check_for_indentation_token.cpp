#include "../ServerInfo.hpp"

/*
@brief Check if the line contain an indentation token and has the right format for it:
 {TABULATION}{KEYWORD}{TOKEN}{EOL}.
@param s the line to check.
@return True if it contais the token, false if dosen't contain the token.
*/
bool	ServerInfo::check_for_indentation_token(string s)
{
	string::iterator	it;
	bool				flag;

	flag = false;
	it = s.begin();
	pass_tabulations(it, s);
	pass_keyword_set_chars(it, s);
	if
	(
		*it == TOKEN_INDENTATION
	)
	{
		flag = true;
		it++;
		if (it != s.end())
			flag = false;
	}
	return (flag);
}
