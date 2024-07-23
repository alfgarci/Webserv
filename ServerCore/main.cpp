#include "ServerCore.hpp"
#include "../ServerInfo/structs.hpp"
#include "Server.hpp"
#include "Client.hpp"

int main()
{
	std::vector<Server>	server;
	std::vector<t_server>	sss;

	t_server server1;
    server1.host = "127.0.0.1";        // Rellenar el host
    server1.port.push_back(8000);      // Rellenar la lista de puertos
    server1.port.push_back(8001);
    server1.port.push_back(8002);

    t_server server2;
    server2.host = "192.168.1.1";      // Rellenar el host
    server2.port.push_back(8080);      // Rellenar la lista de puertos
    server2.port.push_back(8081);

    t_server server3;
    server3.host = "10.0.0.1";         // Rellenar el host
    server3.port.push_back(1234);      // Rellenar la lista de puertos
    server3.port.push_back(5678);

	Server s1(&server1);
	Server s2(&server2);
	Server s3(&server3);

	sss.push_back(server1);
	sss.push_back(server2);
	sss.push_back(server3);

	ServerCore core(sss);

	//core.launchServers();

	return 0;
}