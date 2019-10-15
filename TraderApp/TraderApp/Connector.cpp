#include "Connector.h"
#include <winsock2.h>
#include <iostream>
#include <tchar.h>
#include <ws2tcpip.h>
#include <vector>


#pragma comment(lib, "Ws2_32.lib")

using namespace std;

Connector::Connector()
{

}


Connector::~Connector()
{

}

void listen_message()
{
	WSADATA WSAData;
	SOCKET server, client;
	SOCKADDR_IN serverAddr, clientAddr;
	WSAStartup(MAKEWORD(2, 0), &WSAData);

	server = socket(AF_INET, SOCK_STREAM, 0);
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(5556);

	//puts("Listening...");
	while (true) {
		bind(server, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
		listen(server, 0);
		char buffer[1024];
		memset(buffer, 0, sizeof(buffer));
		int clientAddrSize = sizeof(clientAddr);
		if ((client = accept(server, (SOCKADDR *)&clientAddr, &clientAddrSize)) != INVALID_SOCKET)
		{
			//char *ip = inet_ntoa(clientAddr.sin_addr);
			recv(client, buffer, sizeof(buffer), 0);
			string message = buffer;
			cout << message << endl;
			cout << "trader app>";
			closesocket(client);
		}
	}
}

void send_message(string IP, string message)
{
	WSADATA WSAData;
	SOCKET server;
	SOCKADDR_IN addr;

	WSAStartup(MAKEWORD(2, 0), &WSAData);
	server = socket(AF_INET, SOCK_STREAM, 0);

	InetPton(AF_INET, IP.c_str(), &addr.sin_addr.s_addr);		//InetPton()
	addr.sin_family = AF_INET;
	addr.sin_port = htons(2005);

	connect(server, (SOCKADDR *)&addr, sizeof(addr));
	send(server, message.c_str(), strlen(message.c_str()), 0);
	closesocket(server);
	WSACleanup();
}
