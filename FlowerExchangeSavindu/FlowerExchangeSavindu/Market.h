#pragma once
#include <string>
#include "OrderBook.h"
#include <unordered_map>
#include "Flower.h"
#include "ExecutionReport.h"
#include "Order.h"
#include <iostream>

using namespace std;

class Market
{
	bool mktStatus;//open = true
	unordered_map <string, OrderBook> OrderBooks;
	unordered_map <string, int> FlowerLotSizes;
	unordered_map <string, list<ExecutionReport>> ExecutionReportMap;	// traderID, list of ExeReports

public:
	Market();
	~Market();
	//void getFlowerData();
	unordered_map <string, OrderBook>& getOrderBooks();
	unordered_map <string, int>& getFlowerLotSizes();
	unordered_map <string, list<ExecutionReport>>& getExecutionReportMap();
	void addOrder(Order* order);
	void setStatus(bool x);
	bool getStatus();
	void expireOrders();
};

