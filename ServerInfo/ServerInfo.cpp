#include "ServerInfo.hpp"

#pragma region CONSTRUCTOR

void	ServerInfo::constructor_log(string s)
{
	if (_do_log)
	{
		cout << SERVERINFO_CONSTRUCTOR_LOG_COLOR;
		cout << s;
		cout << SERVERINFO_RESET_COLOR << endl;
	}
}

ServerInfo::ServerInfo() :
_do_log(SERVERINFO_DEFAULT_DO_LOG)
{
	constructor_log(SERVERINFO_DEFAULT_CONSTRUCTOR_LOG);
}

ServerInfo::ServerInfo(bool log) :
_do_log(log)
{
	constructor_log(SERVERINFO_DEFAULT_CONSTRUCTOR_LOG);
}

ServerInfo::~ServerInfo()
{
	constructor_log(SERVERINFO_DESTRUCTOR_LOG);
}

ServerInfo::ServerInfo(const ServerInfo &ServerInfo) :
_do_log(ServerInfo._do_log)
{
	constructor_log(SERVERINFO_COPY_CONSTRUCTOR_LOG);
}

ServerInfo & ServerInfo::operator= (const ServerInfo &ServerInfo)
{
	constructor_log(SERVERINFO_COPY_ASSIGNMENT_LOG);
	if (this != & ServerInfo)
	{
	}
	this->_do_log = ServerInfo._do_log;
	return (*this);
}

#pragma endregion

#pragma region PRINT

void	ServerInfo::print_t_server(t_server	&serv)
{
	list<int>::iterator		port_it;
	list<t_route>::iterator	route_it;
	list<string>::iterator	methods_it;

	port_it = serv.port.begin();
	route_it = serv.routes.begin();
	cout << CLIENT_BODY_LIMIT_KEYWORD << TOKEN_ASSIGNMENT << serv.body_size_limit << endl;
	cout << HOST_KEYWORD << TOKEN_ASSIGNMENT << serv.host << endl;
	cout << SERVER_NAME_KEYWORD << TOKEN_ASSIGNMENT << serv.name << endl;
	cout << "PORTS:" << endl;
	while (port_it != serv.port.end())
	{
		cout << PORT_KEYWORD << TOKEN_ASSIGNMENT << *port_it << endl;
		port_it++;
	}
	cout << "ROUTES:" << endl;
	while (route_it != serv.routes.end())
	{
		cout << CGI_KEYWORD << TOKEN_ASSIGNMENT << (*route_it).cgi << endl;
		cout << DEFAULT_FILE_TO_ANSWER_KEYWORD << TOKEN_ASSIGNMENT << (*route_it).default_file_to_answer << endl;
		cout << TOOGLE_DIR_LISTEN_KEYWORD << TOKEN_ASSIGNMENT << (*route_it).dir_to_listen << endl;
		cout << HTTP_REDIRECTIONS_KEYWORD << TOKEN_ASSIGNMENT << (*route_it).http_redirections << endl;
		cout << SEARCH_DIR_KEYWORD << TOKEN_ASSIGNMENT << (*route_it).search_dir << endl;
		methods_it = (*route_it).accepted_http_methods.begin();
		cout << "METHODS:" << endl;	
		while (methods_it != (*route_it).accepted_http_methods.end())
		{
			cout << ACCEPTED_HTTP_METHODS_KEYWORD << TOKEN_ASSIGNMENT << *methods_it << endl;
			methods_it++;
		}
		route_it++;
	}
}

#pragma endregion
