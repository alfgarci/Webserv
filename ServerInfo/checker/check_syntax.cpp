#include "../ServerInfo.hpp"

void	ServerInfo::check_syntax(string s, int indentation_level, int line)
{
	if (!s.empty())
	{
		if (!check_indentation(s))
			throw (std::logic_error(BAD_SYNTAX + to_string(line)));
		if (!check_indentation_level(s, indentation_level))
			throw (std::logic_error(BAD_INDENTATION + to_string(line)));
		if
		(
			!check_for_indentation_token(s)
			&& !check_for_assignment_token(s)
		)
			throw (std::logic_error(BAD_SYNTAX + to_string(line)));
		if (!check_for_keyword_in_line(s, indentation_level))
			throw (std::logic_error(BAD_SYNTAX + to_string(line)));
	}
}
