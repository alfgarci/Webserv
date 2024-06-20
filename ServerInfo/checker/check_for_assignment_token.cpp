#include "../ServerInfo.hpp"

static void	pass_tabulations(string::iterator &it, string &s)
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

static void pass_keyword_set_chars(string::iterator &it, string &s)
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

/*
@brief Check if the line contain an assignment token and has the right format for it:
 {TABULATION}{KEYWORD}{TOKEN}{VALUE}{EOL}.
@param s the line to check.
@return True if it contais the token, false if dosen't contain the token.
*/
bool	ServerInfo::check_for_assignment_token(string s)
{
	string::iterator	it;
	bool				flag;

	flag = false;
	it = s.begin();
	pass_tabulations(it, s);
	pass_keyword_set_chars(it, s);
	if
	(
		*it == TOKEN_ASSIGNMENT
	)
	{
		flag = true;
		it++;
		if (it == s.end())
			flag = false;
	}
	return (flag);
}
