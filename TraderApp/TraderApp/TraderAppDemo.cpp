#include "Connector.h"
#include <thread>
#include <iostream>

int main()
{
	thread listeningThread(listen_message);

	printf("Welcome to Flower Exchange..... \nFollowing Commands are permited in this system\n\t"
		"1: trading_app register <Trader ID>\n\t"
		"2: trading_app <Trader ID> <side> <symbol> <quantity@price>\n\t"
		"3: trading_app show_orders <Trader ID>\n\t"
		"4: trading_app check_market <symbol>\n");

	while (true)
	{
		string traderCommand;
		cout << "trader app>";
		getline(cin, traderCommand);
		//send_message("127.0.0.1", traderCommand);
		if (strcmp(traderCommand.c_str(), "help") == 0) 		{	
			printf("\nFollowing Commands are permited in this system\n\t"
			"1: trading_app register <Trader ID>\n\t"
			"2: trading_app <Trader ID> <side> <symbol> <quantity@price>\n\t"
			"3: trading_app show_orders <Trader ID>\t==\tso\n\t"
			"4: trading_app check_market <symbol>\t==\tcm\n"); 
		}


		else if (strcmp(traderCommand.c_str(), "1") == 0) {
			send_message("127.0.0.1", "TR1 A sell rose 150@10.50");
		}
		else if (strcmp(traderCommand.c_str(), "2") == 0) {
			send_message("127.0.0.1", "TR1 A sell rose 300@10");
		}
		else if (strcmp(traderCommand.c_str(), "3") == 0) {
			send_message("127.0.0.1", "TR1 A sell rose 200@10");
			send_message("127.0.0.1", "TR1 B buy rose 200@12");
		}
		else if (strcmp(traderCommand.c_str(), "4") == 0) {
			send_message("127.0.0.1", "TR1 A buy rose 400@10");
			send_message("127.0.0.1", "TR1 B buy rose 400@11");
			send_message("127.0.0.1", "TR1 C buy rose 400@12");
		}
		else if (strcmp(traderCommand.c_str(), "cm") == 0) {
			send_message("127.0.0.1", "check_market rose");
		}
		else if (strcmp(traderCommand.c_str(), "so") == 0) {
			send_message("127.0.0.1", "show_orders TR1");
		}
		else if (strcmp(traderCommand.c_str(), "5") == 0) {
			send_message("127.0.0.1", "TR1 A sell rose 100@10");
			send_message("127.0.0.1", "TR1 B sell rose 100@11");
			send_message("127.0.0.1", "TR1 C sell rose 100@12");
			send_message("127.0.0.1", "TR1 D sell rose 100@13");
			send_message("127.0.0.1", "TR1 E sell rose 100@14");
			send_message("127.0.0.1", "TR1 F buy rose 600@14");
		}
		else if (strcmp(traderCommand.c_str(), "6") == 0) {
			send_message("127.0.0.1", "TR1 A buy rose 100@10");
			send_message("127.0.0.1", "TR1 B buy rose 100@11");
			send_message("127.0.0.1", "TR1 C buy rose 100@12");
			send_message("127.0.0.1", "TR1 D buy rose 100@13");
			send_message("127.0.0.1", "TR1 E buy rose 100@14");
			send_message("127.0.0.1", "TR1 F sell rose 600@14");
		}
		else {
			send_message("127.0.0.1", traderCommand);
		}
		
	}

	send_message("127.0.0.1", "TR1 A sell rose 150@10.50");
	send_message("127.0.0.1", "TR1 A sell rose 300@10");
	
	listeningThread.join();

	/*char str[] = "TR1 A sell rose 150@10.50";
	rsize_t strmax = sizeof str;
	const char *delim = " ";
	char *next_token;
	char *token = strtok_s(str, &strmax, delim, &next_token);



	char * pch;
	strtok_s(str, " ", &pch);
	cout << pch << endl;*/

	//orderValues.push_back(pch);
	//while (pch != NULL)
	//{
	//	strtok_s(NULL, " @", &pch);
	//	if (pch != NULL) {
	//		//orderValues.push_back(pch);
	//		cout << pch << endl;
	//	}
	//}

	return 0;
}


