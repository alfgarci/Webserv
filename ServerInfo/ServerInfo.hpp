#ifndef SERVERINFO_HPP
# define SERVERINFO_HPP

# pragma once

# include <iostream>
# include <string>
# include <fstream>

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

enum e_name_keywords
{
	server = 0,
	port = 1,
	host = 1,
	server_name = 1,
	client_body_limit = 1,
	route = 1,
	accepted_http_metods = 2,
	http_redirections = 2,
	search_dir = 2,
	toogle_dir_listen = 2,
	default_file_to_answer = 2,
	CGI = 2
};

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

		//IS_FUNS
		//-------------------------------------------------------

		static bool	is_char_in_keyword_set(char c);

		//-------------------------------------------------------

	protected:
		bool	_do_log;


	private:
		//LOG
		//-------------------------------------------------------

		void	constructor_log(string s);
};

#endif
