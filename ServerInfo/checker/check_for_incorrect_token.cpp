#include "../ServerInfo.hpp"

/*
@brief Check if the line contain a incorrect token, for example "server_name="
@param s the line to be checked
@return True if contain an incorrect token, False if not
*/
bool	ServerInfo::check_for_incorrect_token(string s)
{
	bool				flag;
	string::iterator	it;

	it = s.begin();
	flag = false;
	pass_tabulations(it, s);
	pass_keyword_set_chars(it, s);
	if (*it == TOKEN_INDENTATION)
	{
		if
		(
			!check_for_keyword(s, Base_dictionary.at(server))
			&& !check_for_keyword(s, Server_dictionary.at(route))
			&& !check_for_keyword(s, Route_dictionary.at(CGI))
		)
			flag = true;
	}
	if (*it == TOKEN_ASSIGNMENT)
	{
		if
		(
			check_for_keyword(s, Base_dictionary.at(server))
			|| check_for_keyword(s, Server_dictionary.at(route))
			|| check_for_keyword(s, Route_dictionary.at(CGI))
		)
			flag = true;
	}
	return (flag);
}
