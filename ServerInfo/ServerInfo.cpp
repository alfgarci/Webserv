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
