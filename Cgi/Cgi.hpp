#pragma once

# include "../HTTPRequestParse/HTTPRequestParse.hpp"
# include "../ServerCore/Server.hpp"
# include <map>
# include <unistd.h>
#	include <sys/stat.h>


class Cgi
{
	private:
		HTTPRequestParse    _request;
		string              _path;
		pid_t               _pid;
		map<string, string> _env;
		Server              _serverInfo;
		string				_validFiles;

		int                 _port;

	public:

		Cgi();
		Cgi(const Cgi &other);
		Cgi& operator=(const Cgi &other);
		Cgi(HTTPRequestParse request, Server server, int port, string validFiles);

		int    	initEnvCgi();
		string  getFilePath(string fullPath);
		string  getQueryString(string fullPath);
		char    **mapToCharArr();

		string  handleGetCgi();
		string  handlePostCgi();

		void    executeCgi();

		void	reset();

		int pipeIn[2]; //para escribir en el CGI
		int pipeOut[2]; //para leer del cgi
};
