#include "../ServerInfo.hpp"

static void	check_limits(int value)
{
	if (value < MIN_BYTE_VALUE || value >= MAX_BYTE_VALUE)
		throw (std::logic_error(ERROR_OVERFLOW_IN_IP_DEFINITION));
}

static void check_string(string s)
{
	string::iterator	it;
	int					dot_counter;
	int					digit_counter;
	bool				dot_flag;

	dot_counter = 0;
	digit_counter = 0;
	dot_flag = false;
	it = s.begin();
	while (it != s.end())
	{
		if (isdigit(*it))
		{
			digit_counter++;
			dot_flag = false;
			if (digit_counter > MAX_DIGITS_IN_BYTE)
				throw (std::logic_error(ERROR_ILLEGAL_TOKEN));
		}
		else if (*it == '.')
		{
			if (dot_flag)
				throw(std::logic_error(ERROR_ILLEGAL_TOKEN));
			dot_flag = true;
			digit_counter = 0;
			dot_counter++;
			if (dot_counter > MAX_SEPARATORS_IN_BYTE)
				throw (std::logic_error(ERROR_ILLEGAL_TOKEN));
		}
		else
			throw (std::logic_error(ERROR_ILLEGAL_TOKEN));
		it++;
	}
	if (dot_counter != MAX_SEPARATORS_IN_BYTE)
		throw (std::logic_error(ERROR_ILLEGAL_TOKEN));
}

//NOTE conversión value is made for IPV4, and is the multiplication factor
//NOTE_2 Originaly this was intended to return a int

string	ServerInfo::store_host(string s)
{
	string				content;
	string::iterator	it;
	int					tmp_value;
	int					conversion_value;

	content = get_line_content(s);
	check_string(content);
	it = content.begin();
	conversion_value = IPV4_CONVERSION_VALUE;
	while (it != content.end())
	{
		if (check_overflow(content))
			throw(std::logic_error(ERROR_OVERFLOW_GENERIC));
		tmp_value = atoi(content.c_str());
		check_limits(tmp_value);
		while (it != content.end() && *it != '.')
			it++;
		if (it != content.end())
			it++;
		if (conversion_value > -BYTE)
		{
			content = string(it, content.end());
			it = content.begin();
		}
	}
	content = get_line_content(s);
	return (content);
}
