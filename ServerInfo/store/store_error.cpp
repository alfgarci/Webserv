#include "../ServerInfo.hpp"

void	ServerInfo::store_error(string s, t_error	&error)
{
	if (check_for_keyword(s, error_pages_dictionary.at(error_code)))
	{
		if (check_overflow(get_line_content(s)))
			throw (std::logic_error(ERROR_OVERFLOW_GENERIC));
		error.code = atoi(get_line_content(s).c_str());
	}
	if (check_for_keyword(s, error_pages_dictionary.at(path_to_error)))
	{
		error.path = get_line_content(s);
	}
}
