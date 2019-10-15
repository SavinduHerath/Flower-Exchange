#pragma once
#include <string>
#include <vector>
#include <ctime>
#include "Order.h"
#include "Market.h"

using namespace std;

class ConnectorExchange
{
public:
	Market * market;
	ConnectorExchange(Market *market_);
	~ConnectorExchange();
	void listen_message();

private:
	int validate(vector<string> vec);
	void processString(string str);
};

Order* convertOrder(string str);   //vector<string>


void send_message(string IP, string message);
