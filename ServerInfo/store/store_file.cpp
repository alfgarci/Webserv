#include "../ServerInfo.hpp"

/*
@brief Store the given file, into a list of list<t_server>, would throw errors if at any point
the requirements fail, if the file dosent compliy, etc
@param route the route to the file
@return all the server configs that have been founded in the file
*/
list<t_server>	ServerInfo::store_file(string route)
{
	std::fstream		file;
	string				s;

	file.open(route, std::fstream::in);
	if (!file.is_open())
		throw std::logic_error(ERROR_CANT_OPEN_FILE);
	while (std::getline(file, s))
	{
	}
}
