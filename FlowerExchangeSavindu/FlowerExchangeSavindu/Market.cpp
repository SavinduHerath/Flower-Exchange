#include "Market.h"
#include <fstream>
#include <vector>
#include <sstream>
#include "OrderBook.h"



Market::Market()
{
	vector<Flower> flowerData;
	
	string tmp;
	ifstream infile("flowerData.txt");
	while (getline(infile, tmp))
	{
		istringstream iss(tmp);
		string symbol, displayName;
		int lotSize;

		iss >> symbol;
		iss >> displayName;
		iss >> lotSize;

		Flower flower = { symbol, displayName, lotSize };
		flowerData.push_back(flower);
	}

	//vector<string>* symbols = new vector<string>({"rose", "carnation","gerbera" });
	for (size_t i = 0; i < flowerData.size(); i++) {
		OrderBooks.insert({ flowerData.at(i).symbol, OrderBook(flowerData.at(i), this)}); //, new Market()
		FlowerLotSizes.insert({ flowerData.at(i).symbol, flowerData.at(i).lotSize });
	}


	//OrderBook OB1;
	//OrderBooks = { {"rose", OB1}, {"carnation", OB2}, {"gerbera", OB3}, {"chrysanthemum", OB4}, {"tulip", OB5}, {"gladioli", OB6}, {"lilie", OB7}, {"alstroemeria", OB8}, {"anthurium", OB9}, {"amaryllis", OB10}, {"birds_of_paradise", OB11}, {"calla_lily", OB12}, {"gardenias", OB13}, {"lilacs", OB14}, {"lily_of_the_valley", OB15}, {"miniature_calla_lily", OB16}, {"oriental_lily", OB17}, {"heliconia_pendula", OB18}, {"musas", OB19}, {"calatheas", OB20}, {"gingers", OB21}, {"palms", OB22}, {"orchids", OB23}, {"lotus", OB24} };

}



Market::~Market()
{
}

/*void Market::getFlowerData()
{
	vector<Flower> flowerData;
	string tmp;
	ifstream infile("flowerData.txt");
	while (getline(infile, tmp))
	{
		istringstream iss(tmp);
		string symbol, displayName;
		int lotSize;

		iss >> symbol;
		iss >> displayName;
		iss >> lotSize;

		Flower flower = { symbol, displayName, lotSize };
		flowerData.push_back(flower);
	}
}*/

unordered_map <string, OrderBook>& Market::getOrderBooks()
{
	return OrderBooks;
}
unordered_map <string, int>& Market::getFlowerLotSizes()
{
	return FlowerLotSizes;
}
unordered_map <string, list<ExecutionReport>>& Market::getExecutionReportMap()
{
	return ExecutionReportMap;
}

void Market::addOrder(Order * order)
{
	OrderBook * OB1 = &(getOrderBooks().find(order->getSymbol())->second);
	OB1->matchOrder(*order);

}

void Market::setStatus(bool x)
{
	mktStatus = x;
}

bool Market::getStatus()
{
	return mktStatus;
}

void Market::expireOrders()
{
	for (auto &pair : this->getOrderBooks())
	{
		pair.second.expireOrders();
		//cout << pair.first << endl;
	}
	
	
}

//void Market::setExecutionReportMap(ExecutionReport exR)
//{
//	list<ExecutionReport> temp;
//	temp.push_back(exR);
//	ExecutionReportMap.insert({ exR.getTraderID(), temp });
//}
