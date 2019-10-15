//#include "gtest/gtest.h"
#include "Order.h"
#include <fstream>
#include <vector>
#include <sstream>
#include "Flower.h"
#include "OrderBook.h"
#include "ConnectorExchange.h"
#include <thread>
#include "Market.h"
#include "FlowerExchangeDemo.h"


//bool func()
//{
//	return true;
//}
Market* market;

void waitingForCommand() {
	cout << "Exchange server" << endl;
	while (true)
	{
		string exchangeCommand;
		cout << "Exchange app>";
		getline(cin, exchangeCommand);
		if (exchangeCommand == "exchange_app market_open" || exchangeCommand == "open")
		{
			//marketOpen();
			market->setStatus(true);
			send_message("127.0.0.1", "Market is now open");
		}
		else if (exchangeCommand == "exchange_app market_close" || exchangeCommand == "close")
		{
			//marketClose();
			market->expireOrders();
			market->setStatus(false);
			send_message("127.0.0.1", "Trading ended, Market closed");
		}
		else
		{
			cout << "Enter a valid Exchange Command" << endl;
		}
		//send_message("127.0.0.1", message);
	}
}

int main(int argc, char** argv)
{
	//testing::InitGoogleTest(&argc, argv);
	//return RUN_ALL_TESTS();
	
	market = new Market();
	ConnectorExchange conn = ConnectorExchange(market);

	thread CommandThread(waitingForCommand); //only the name of the method

	conn.listen_message();
	
	CommandThread.join();
	

	return 0;

}

