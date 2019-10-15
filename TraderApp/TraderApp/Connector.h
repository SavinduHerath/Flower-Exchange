#pragma once
#include <string>

using namespace std;

class Connector
{
public:
	Connector();
	~Connector();
};

void send_message(string IP, string message);

void listen_message();

