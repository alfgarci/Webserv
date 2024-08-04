#ifndef CGI_HANDLER_HPP
# define CGI_HANDLER_HPP

#include <cstring>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <sys/wait.h>
#include <sys/socket.h>

using std::stringstream;

bool handle_cgi_request(const std::string& path, const std::string& postData, stringstream& message);

void send_response(int socket_id, const std::string& response);

#endif // CGI_HANDLER_HPP
