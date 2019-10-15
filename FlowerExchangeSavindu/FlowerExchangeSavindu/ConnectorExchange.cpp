#include "ConnectorExchange.h"
#include <winsock2.h>
#include <iostream>
#include <tchar.h>
#include <ws2tcpip.h>
#include <string>
#include <sstream>


#pragma comment(lib, "Ws2_32.lib")
ConnectorExchange::ConnectorExchange(Market *market_)
{
	market = market_;
}


ConnectorExchange::~ConnectorExchange()
{
}

vector<string> stringSplitter(string str) {
	vector<string> vec;
	char* char_line = (char*)str.c_str();

	char* token = NULL;
	char* context = NULL;
	char delims[] = " @";
	token = strtok_s(char_line, delims, &context);
	while (token != NULL)
	{
		vec.push_back(token);
		token = strtok_s(NULL, delims, &context);
	}
	return vec;
}

int ConnectorExchange::validate(vector<string> vec) {				//2->convertOrder  -1->send 'R' Report
	//logic
	if (market->getStatus() == true)
	{
		if (vec.size() == 2)
		{
			if (strcmp(vec[0].c_str(), "check_market") == 0)
			{
				//send_message("127.0.0.1", "show market data");
				return 0;
			}
			else if (strcmp(vec[0].c_str(), "show_orders") == 0)
			{
				//send_message("127.0.0.1", "show all the Traders Exe R");
				return 1;
			}
			else
			{
				return -1;
			}
		}
		else if (vec.size() == 6)
		{
			if (market->getOrderBooks().count(vec[3]) == 1)
			{
				if (strcmp(vec[2].c_str(), "buy") == 0 || strcmp(vec[2].c_str(), "sell") == 0)
				{
					try {
						if (stoi(vec[4]) % (market->getFlowerLotSizes().find(vec[3])->second) == 0 && stoi(vec[4]) > 0)		//stoi(vec[4]) % (market->*(market->getFlowerLotSizes).find(vec[3])->second()) == 0
						{
							if (stof(vec[5]) > 0.0)
							{
								return 2;
							}
							else { return -1; }
						}
						else { return -2; }
					}
					catch (exception &e) {
						return -1;
					}
				}
				else { return -1; }
			}
			else { return -1; }
		}
		else { return -1; }
	}
	else { send_message("127.0.0.1", "Market is closed. Wait till it's open"); }
}

 Order* convertOrder(string str) {  //vector<string>
	 vector<string> vec = stringSplitter(str);

		 //validation
	
	int side;// i = 0;  //static int i
	//vector<string> orderIDs = {"A", "B", "C", "D", "E", "F", "G"};
	if (vec[2] == "buy") { side = 1;}
	else if (vec[2] == "sell") { side = 2; }

	time_t current_time = time(nullptr);	//timestamp for the creation of the order
	long timeStamp = (long)current_time;

	Order* newOrder = new Order (vec[3], side, stoi(vec[4]), stof(vec[5]), vec[0], vec[1], timeStamp);
	//i++;
	//newOrder->
	return newOrder;
}
  
 void ConnectorExchange::processString(string str) {
	 vector<string> vec = stringSplitter(str);
	 int scn = validate(vec);
	 if (scn == 2)
	 {
		 Order* newOrder = convertOrder(str);
		 market->addOrder(newOrder);
	 }
	 else if (scn == -1)
	 {
		 send_message("127.0.0.1", "Invalid command, use <help> command");
	 }
	 else if (scn == 0)
	 {
		 string fSymbol = vec.at(1);
		 OrderBook OB = market->getOrderBooks().find(fSymbol)->second;
		 send_message("127.0.0.1", OB.getMarketDataString());
	 }

	 else if (scn == 1)
	 {
		 string trID = vec.at(1);
		 try {
			 auto x = market->getExecutionReportMap();
			 if (x.count(trID) <= 0) {
				 send_message("127.0.0.1", "No such trader..");
			 }
			 else
			 {
				list<ExecutionReport> reps = x.find(trID)->second;
				 for (auto item : reps) 
				 {
					 send_message("127.0.0.1", item.getReportString());
				 }
			 }
		 }
		 catch (exception &e) {
			 send_message("127.0.0.1", "No such trader..");
		 }
	 }
	 else if (scn == -2)
	 {
		 Order* rejectedOrder = convertOrder(str);
		 ExecutionReport exeReason = ExecutionReport(vec.at(3), rejectedOrder->getSide(), stoi(vec.at(4)), 'R', 0, 0, stof(vec.at(5)), "Invalid Lot Size", vec.at(0), vec.at(1), "", rejectedOrder->getTimestamp());
		 string str = exeReason.getReportString();
		 send_message("127.0.0.1", str);
	 }
 }
 
 //string symbol, int side, int qty, char execType, int execQty, int remainQty, float price, string reason, string traderID, string orderID, string contraOrderID, long timestamp


void ConnectorExchange::listen_message()
{
	WSADATA WSAData;
	SOCKET server, client;
	SOCKADDR_IN serverAddr, clientAddr;
	WSAStartup(MAKEWORD(2, 0), &WSAData);

	server = socket(AF_INET, SOCK_STREAM, 0);
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(5555);

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
			processString(message);
			//Order* newOrder = convertOrder(message);  //vector<string>
			//market->addOrder(newOrder);

			closesocket(client);
			//cout << "Exchange app>";
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

	inet_pton(AF_INET, IP.c_str(), &addr.sin_addr.s_addr);			//_T(IP.c_str())
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5556);

	connect(server, (SOCKADDR *)&addr, sizeof(addr));
	send(server, message.c_str(), strlen(message.c_str()), 0);
	closesocket(server);
	WSACleanup();
}