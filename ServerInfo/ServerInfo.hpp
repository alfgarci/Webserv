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

# define SERVERINFO_CONSTRUCTOR_LOG_COLOR "\033[1;30m"
# define SERVERINFO_RESET_COLOR "\033[0m"
# define SERVERINFO_DEFAULT_DO_LOG false

# define SERVERINFO_DEFAULT_CONSTRUCTOR_LOG "ServerInfo default constructor called"
# define SERVERINFO_COPY_CONSTRUCTOR_LOG "ServerInfo copy constructor called"
# define SERVERINFO_COPY_ASSIGNMENT_LOG "ServerInfo copy assignment called"
# define SERVERINFO_DESTRUCTOR_LOG "ServerInfo destructor called"

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

		//-------------------------------------------------------

	protected:
		bool	_do_log;

		//CHECKER
		//-------------------------------------------------------
		
		bool	CheckIndentation(string s);

		//-------------------------------------------------------

	private:
		//LOG
		//-------------------------------------------------------

		void	constructor_log(string s);
};

#endif
