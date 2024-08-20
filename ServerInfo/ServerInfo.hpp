#ifndef SERVERINFO_HPP
# define SERVERINFO_HPP

# pragma once

# include <iostream>
# include <string>
# include <fstream>
# include <sstream>
# include <cstdlib>

# include "keywords.hpp"
# include "structs.hpp"
# ifndef TO_STRING_HPP
#  include "../libs/to_string.hpp"
# endif

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
access to the file, and if the file exist, thanks ^^."
# define BAD_SYNTAX "Bad syntax at line: "
# define BAD_INDENTATION "Bad indentation at line: "
# define ERROR_NOT_ENOUGH_MEMORY "Memory reserve, fail, exiting."
# define BAD_BOOLEAN_STRING "Boolean string is badly formated, accepted formats (true/false)."
# define ERROR_CAMP_UNINITIALIZE "There are uninitialize camps, pls initialize them"
# define ERROR_DUPLICATED_HTTP_METHODS "There are duplicated http methods"
# define ERROR_OVERFLOW_IN_IP_DEFINITION "OVERFLOW in ip definition"
# define ERROR_ILLEGAL_TOKEN "Illegal token in ip definition"

# define BYTE 8
# define IPV4_CONVERSION_VALUE 24
# define MAX_BYTE_VALUE 256
# define MIN_BYTE_VALUE 0
# define MAX_DIGITS_IN_BYTE 3
# define MAX_SEPARATORS_IN_BYTE 3

# define DEFAULT_BODY_SIZE 0
# define DEFAULT_HOST ""
# define DEFAULT_PORT_SERVER_INFO 0
# define DEFAULT_NAME ""
# define DEFAULT_METHOD_GET "GET"
# define DEFAULT_METHOD_POST "POST"
# define DEFAULT_METHOD_DELETE "DELETE"
# define DEFAULT_FILE_TO_ANSWER ""
# define DEFAULT_DIR_TO_LISTEN ""
# define DEFAULT_HTTP_REDI ""
# define DEFAULT_SEARCH_DIR ""
# define DEFAULT_CGI_TARGET ""
# define DEFAULT_CGI_PATH ""
# define DEFAULT_SERVER_ERROR_CODE 0
# define DEFAULT_SERVER_ERROR_PATH ""

# define TRUE_STRING "true"
# define FALSE_STRING "false"

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
		static bool	check_for_keyword(string s, string keyword);
		static bool check_for_incorrect_token(string s);
		static void	check_syntax(string s, int indentation_level, int line);

		//IS_FUNS
		//-------------------------------------------------------

		static bool	is_char_in_keyword_set(char c);
		static bool	is_keyword_in_set(string keyword, Dictionary set);

		//STORE
		//-------------------------------------------------------

		static list<t_server>	store_file(string route); //THIS STORE EVERYTHING
		static void				store_server(string s, t_server &server_struct);
		static void				store_route(string s, t_server &server_struct);
		static void				store_cgi(string s, t_server &server_struct);
		static string			store_host(string s);
		static void				store_error(string s, t_error &error);
		static t_server			initiate_server();
		static t_route			initiate_route();
		static t_CGI			initiate_cgi();
		static t_error			initiate_error();
		static string			get_line_content(string line);
		static bool				verify_no_defaults(list<t_server> &lst);
		static bool				verify_http_methods(list<t_server> &lst);
		static void				select_store_method(list<t_server> &lst_server,
									int indentation_level, string s);

		//-------------------------------------------------------
		static void	print_t_server(t_server	&serv);

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

#endif
