#ifndef KEYWORDS_HPP
# define KEYWORDS_HPP

#pragma once

# include <iostream>
# include <string>
# include <fstream>
# include <map>

using std::cout;
using std::string;
using std::cin;
using std::endl;
using std::cerr;

typedef std::map<int, string> Dictionary;

# define SERVER_KEYWORD "server"
# define PORT_KEYWORD "port"
# define HOST_KEYWORD "host"
# define SERVER_NAME_KEYWORD "server_name"
# define CLIENT_BODY_LIMIT_KEYWORD "body_limit"
# define ROUTE_KEYWORD "route"
# define ACCEPTED_HTTP_METHODS_KEYWORD "accepted_http_methods"
# define HTTP_REDIRECTIONS_KEYWORD "http_redirections"
# define SEARCH_DIR_KEYWORD "search_dir"
# define KEYWORD_ERROR_PAGE "error_page"
# define KEYWORD_ERROR_CODE "code"
# define KEYWORD_ERROR_PATH_TO_FILE "path"
# define TOOGLE_DIR_LISTEN_KEYWORD "dir_listen"
# define DEFAULT_FILE_TO_ANSWER_KEYWORD "default_file"
# define CGI_KEYWORD "CGI"
# define FILE_TARGETS "files"
# define PATH_OF_CGI "path"

enum e_base_keywords
{
	server = 0
};

enum e_server_keywords
{
	port = 0,
	host = 1,
	server_name = 2,
	body_limit = 3,
	route = 4,
	search_dir_server = 5,
	error_page = 6
};

enum e_route_keywords
{
	accepted_http_methods = 0,
	http_redirections = 1,
	search_dir = 2,
	toogle_dir_listen = 3,
	default_file_to_answer = 4,
	CGI = 5
};

enum e_CGI_keywords
{
	file_targets = 0,
	path_of_cgi = 1
};

enum e_error_page_keywords
{
	error_code = 0,
	path_to_error = 1
};

class DictionaryCreator
{
	public:
		static Dictionary create_base_dict()
		{
			Dictionary	d;

			d[server] = SERVER_KEYWORD;
			return (d);
		}
		static Dictionary create_server_dict()
		{
			Dictionary	d;

			d[port] = PORT_KEYWORD;
			d[host] = HOST_KEYWORD;
			d[server_name] = SERVER_NAME_KEYWORD;
			d[body_limit] = CLIENT_BODY_LIMIT_KEYWORD;
			d[route] = ROUTE_KEYWORD;
			d[search_dir_server] = SEARCH_DIR_KEYWORD;
			d[error_page] = KEYWORD_ERROR_PAGE;
			return (d);
		}
		static Dictionary create_route_dict()
		{
			Dictionary	d;

			d[accepted_http_methods] = ACCEPTED_HTTP_METHODS_KEYWORD;
			d[http_redirections] = HTTP_REDIRECTIONS_KEYWORD;
			d[search_dir] = SEARCH_DIR_KEYWORD;
			d[toogle_dir_listen] = TOOGLE_DIR_LISTEN_KEYWORD;
			d[default_file_to_answer] = DEFAULT_FILE_TO_ANSWER_KEYWORD;
			d[CGI] = CGI_KEYWORD;
			return (d);
		}
		static Dictionary create_CGI_dict()
		{
			Dictionary	d;

			d[file_targets] = FILE_TARGETS;
			d[path_of_cgi] = PATH_OF_CGI;
			return (d);
		}
		static Dictionary create_error_page_dict()
		{
			Dictionary	d;

			d[error_code] = KEYWORD_ERROR_CODE;
			d[path_to_error] = KEYWORD_ERROR_PATH_TO_FILE;
			return (d);
		}
};

static const Dictionary Base_dictionary = DictionaryCreator::create_base_dict();
static const Dictionary Server_dictionary = DictionaryCreator::create_server_dict();
static const Dictionary Route_dictionary = DictionaryCreator::create_route_dict();
static const Dictionary CGI_dictionary = DictionaryCreator::create_CGI_dict();
static const Dictionary error_pages_dictionary = DictionaryCreator::create_error_page_dict();

enum e_indentation_level_keywords
{
	base_level = 0,
	server_level = 1,
	route_level = 2,
	cgi_level = 3,
	error_level = 4
};

class IndentationCreator
{
	public:
		static std::map<int, Dictionary> create_indentation_dict()
		{
			std::map<int, Dictionary>	d;

			d[base_level] = Base_dictionary;
			d[server_level] = Server_dictionary;
			d[route_level] = Route_dictionary;
			d[cgi_level] = CGI_dictionary;
			d[error_level] = error_pages_dictionary;
			return (d);
		}
};

static const std::map<int, Dictionary> Indentaton_dictionary = IndentationCreator::create_indentation_dict();

#endif
