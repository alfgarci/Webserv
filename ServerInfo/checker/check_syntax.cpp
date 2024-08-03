#include "../ServerInfo.hpp"

/*
@brief Check if the syntax is correct for the selected line
@param s the line to check
@param indentation_level the level of indentation
@param line the line number in the file, for throw purpose
*/
void	ServerInfo::check_syntax(string s, int indentation_level, int line)
{
	if (!s.empty())
	{
		if (!check_indentation(s))
		{	
			cout<<"1"<<endl;
			throw (std::logic_error(BAD_SYNTAX + to_string(line)));
		}
		if (!check_indentation_level(s, indentation_level))
		{
			cout<<"2"<<endl;
			throw (std::logic_error(BAD_INDENTATION + to_string(line)));
		}
		if
		(
			!check_for_indentation_token(s)
			&& !check_for_assignment_token(s)
		)
		{
			cout<<"3"<<endl;
			throw (std::logic_error(BAD_SYNTAX + to_string(line)));
		}
		if (!check_for_keyword_in_line(s, indentation_level))
		{
			cout<<"4"<<endl;
			throw (std::logic_error(BAD_SYNTAX + to_string(line)));
		}
	}
}
