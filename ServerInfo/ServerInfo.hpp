#ifndef SERVERINFO_HPP
# define SERVERINFO_HPP

# pragma once

# include <iostream>
# include <string>
# include <fstream>
# include <sstream>

# include "keywords.hpp"
# include "structs.hpp"

using std::cout;
using std::string;
using std::cin;
using std::endl;
using std::cerr;

# define TOKEN_SPACE '\t'
# define TOKEN_INDENTATION ':'
# define TOKEN_ASSIGNMENT '='
# define NEW_LINE '\n'

# define SERVERINFO_CONSTRUCTOR_LOG_COLOR "\033[1;30m"
# define SERVERINFO_RESET_COLOR "\033[0m"
# define SERVERINFO_DEFAULT_DO_LOG false

# define SERVERINFO_DEFAULT_CONSTRUCTOR_LOG "ServerInfo default constructor called"
# define SERVERINFO_COPY_CONSTRUCTOR_LOG "ServerInfo copy constructor called"
# define SERVERINFO_COPY_ASSIGNMENT_LOG "ServerInfo copy assignment called"
# define SERVERINFO_DESTRUCTOR_LOG "ServerInfo destructor called"

# define ERROR_CANT_OPEN_FILE "Can't open file, check that you send the right route, i have the \
access to the file, and that it exist, thanks ^^"
# define BAD_SYNTAX "Bad syntax at line: "
# define BAD_INDENTATION "Bad indentation at line: "

class ServerInfo
{
	public:
		//CONSTRUCTORS
		//-------------------------------------------------------

		ServerInfo();
		ServerInfo(bool log);
		ServerInfo(const ServerInfo &ServerInfo);
		~ServerInfo();
		ServerInfo & operator = (const ServerInfo &ServerInfo);

		//CHECKER
		//-------------------------------------------------------
		
		static bool	check_indentation(string s);
		static bool check_indentation_level(string s, int expected_level);
		static bool check_for_indentation_token(string s);
		static bool	check_for_assignment_token(string s);
		static bool check_for_keyword_in_line(string s, int indentation_level);
		static void	check_syntax(string s, int indentation_level, int line);

		//IS_FUNS
		//-------------------------------------------------------

		static bool	is_char_in_keyword_set(char c);
		static bool	is_keyword_in_set(string keyword, Dictionary set);

		//STORE
		//-------------------------------------------------------

		static void				store_server(std::fstream &file);
		static void				store_route(std::fstream &file);
		static list<t_server>	store_file(string route);

		//-------------------------------------------------------

	protected:
		bool	_do_log;

	private:
		//LOG
		//-------------------------------------------------------

		void	constructor_log(string s);

		//CHECKER
		//-------------------------------------------------------

		static void	pass_tabulations(string::iterator &it, string &s);
		static void pass_keyword_set_chars(string::iterator &it, string &s);
};

template <typename T>
std::string to_string(const T& value)
{
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

#endif
