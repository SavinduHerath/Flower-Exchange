#pragma once
#include <string>
#include <queue>
#include "Order.h"
#include "Flower.h"

using namespace std;

class Market;

class OrderBook
{
public:
	OrderBook(Flower flo, Market* market);
	OrderBook();
	~OrderBook();
	float getLastTradedPrice();
	float getHighPrice();
	float getLowPrice();
	float getBestBid();
	float getBestOffer();
	Flower getFlower();

	string getMarketDataString();

	priority_queue<Order>& getBuySide();
	priority_queue<Order>& getSellSide();

	void expireOrders();
	void matchOrder(Order o);

private:
	Flower flower;
	float lastTradedPrice=0;
	float highPrice = 0;
	float lowPrice = 10000;
	float bestBid=0;				// = this->getBuySide().top().getPrice();
	float bestOffer=0;
	priority_queue<Order> buySide;
	priority_queue<Order> sellSide;
	Market* market;

	void executionReportGenerator(Order order, char c);
	void executionReportGenerator(Order order, int execQty, int remainQty, string contraID);
	void marketDataSetter(Order order);
};


