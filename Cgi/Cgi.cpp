# include "Cgi.hpp"

Cgi::Cgi()
{
}

Cgi::Cgi(const Cgi &other)
{
	_request = other._request;
	_path = other._path;
	_pid = other._pid;
	_env = other._env;
	_serverInfo = other._serverInfo;
	_port = other._port;

	pipeIn[0] = other.pipeIn[0];
	pipeIn[1] = other.pipeIn[1];
	pipeOut[0] = other.pipeOut[0];
	pipeOut[1] = other.pipeOut[1];
}


Cgi& Cgi::operator=(const Cgi &other)
{
	if (this != &other)
	{
		_request = other._request;
		_path = other._path;
		_pid = other._pid;
		_env = other._env;
		_serverInfo = other._serverInfo;
		_port = other._port;

		pipeIn[0] = other.pipeIn[0];
		pipeIn[1] = other.pipeIn[1];
		pipeOut[0] = other.pipeOut[0];
		pipeOut[1] = other.pipeOut[1];
	}

	return *this;
}


Cgi::Cgi(HTTPRequestParse request, Server server, int port)
{
	_request = request;
	_serverInfo = server;
	_port = port;

	if (pipe(pipeIn) == -1 || pipe(pipeOut) == -1)
	{
		std::cerr << "error: error in creating the Cgi pipes" << std::endl;
		exit(EXIT_FAILURE);
	}
	 
	initEnvCgi();
}

string Cgi::getFilePath(string fullPath)
{
	size_t queryPos = fullPath.find('?');
	
	if (queryPos == std::string::npos)
	{
		return fullPath;
	}
	return fullPath.substr(0, queryPos);
}

string Cgi::getQueryString(string fullPath)
{
	size_t queryPos = fullPath.find('?');
	
	if (queryPos == std::string::npos)
	{
		return "";
	}
	return fullPath.substr(queryPos + 1);
}

std::string to_string(int value)
{
	std::stringstream ss;
	ss << value;
	return ss.str();
}

std::string to_string(size_t value)
{
	std::stringstream ss;
	ss << value;
	return ss.str();
}

void    Cgi::initEnvCgi()
{

	string  CgiPath = getFilePath(_request.getField(HTTPRequestParse::PATH));
	if (CgiPath[0] != '/')
	{
		CgiPath = "/" + CgiPath;
	}
	_path = CgiPath;
	if (_request.getField(HTTPRequestParse::METHOD) == "POST")
	{
		_env["CONTENT_TYPE"] = _request.getField(HTTPRequestParse::CONTENT_TYPE);
		_env["CONTENT_LENGTH"] = to_string(_request.getField(HTTPRequestParse::CONTENT_LENGTH).size());
	}
	_env["GATEWAY_INTERFACE"] = "Cgi/1.1";
	_env["REQUEST_METHOD"] = _request.getField(HTTPRequestParse::METHOD);
	_env["SCRIPT_NAME"] = CgiPath;
	_env["QUERY_STRING"] = getQueryString(_request.getField(HTTPRequestParse::PATH));
	_env["REMOTE_ADDR"] = _serverInfo.getIp();
	_env["SERVER_NAME"] = _serverInfo.getName();
	_env["SERVER_PORT"] = to_string(_port);
	_env["SERVER_PROTOCOL"] = "HTTP/1.1";
	_env["SERVER_SOFTWARE"] = "42WebServer/1.0";
	_env["REDIRECT_STATUS"] = "200";
	_env["PATH_TRANSLATED"] = _serverInfo.getRoot() + getFilePath(_request.getField(HTTPRequestParse::PATH));
}

char **Cgi::mapToCharArr()
{
	char **env = new char*[_env.size() + 1];
	size_t i = 0;
	
	for (std::map<std::string, std::string>::iterator it = _env.begin(); it != _env.end(); ++it, ++i)
	{
		std::string env_entry = it->first + "=" + it->second;
		env[i] = new char[env_entry.size() + 1];
		std::strcpy(env[i], env_entry.c_str());
	}
	env[i] = NULL;
	return env;
}

void	Cgi::executeCgi()
{
	_pid = fork();
	if (_pid < 0)
	{
		std::cerr << "error: fork failed" << endl;
		exit(EXIT_FAILURE);
	}

	//proceso hijo
	if (_pid == 0)
	{
		dup2(pipeIn[0], STDIN_FILENO);		//entrada estandarar al pipeIn[0]
		dup2(pipeOut[1], STDOUT_FILENO);	//salida estandar al pipeOut[1]

		//cerramos los extremos que no usaremos
		close(pipeIn[1]);
		close(pipeOut[0]);

		char **envp = mapToCharArr();
		char *argv[] = {const_cast<char*>(_path.c_str()), NULL};


		execve(_path.c_str(), argv, envp);
		std::cerr << "error: execve failed" << endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		close(pipeIn[0]);
		close(pipeOut[1]);
	}
}
