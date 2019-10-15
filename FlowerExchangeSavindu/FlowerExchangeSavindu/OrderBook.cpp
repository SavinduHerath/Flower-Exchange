#include "OrderBook.h"
#include <iostream>
#include "ExecutionReport.h"
#include "Market.h"
#include "ConnectorExchange.h"

using namespace std;

OrderBook::OrderBook(Flower flo, Market* mar)
{
	flower = flo;
	market = mar;
}

OrderBook::OrderBook()
{
	//Second change
}



OrderBook::~OrderBook()
{
}

float OrderBook::getLastTradedPrice()
{
	return lastTradedPrice;
}


float OrderBook::getHighPrice()
{
	return highPrice;
}


float OrderBook::getLowPrice()
{
	if (lowPrice == 10000) { return 0; }
	return lowPrice;
}

float OrderBook::getBestBid()
{
	if (this->getBuySide().size() != 0) { return this->getBuySide().top().getPrice(); }
	else { return 0.0f; }
}

float OrderBook::getBestOffer()
{
	if (this->getSellSide().size() != 0) { return this->getSellSide().top().getPrice(); }
	else { return 0.0f; }
}

Flower OrderBook::getFlower()
{
	return flower;
}

priority_queue<Order>& OrderBook::getBuySide()
{
	return buySide;
}

priority_queue<Order>& OrderBook::getSellSide()
{
	return sellSide;
}

void OrderBook::expireOrders()
{
	this->bestBid = 0;
	this->bestOffer = 0;
	this->lastTradedPrice = 0;
	this->lowPrice = 10000;
	this->highPrice = 0;
	while (!this->getBuySide().empty())
	{
		executionReportGenerator(this->getBuySide().top(), 'C');
		this->getBuySide().pop();
	}
	while (!this->getSellSide().empty())
	{
		executionReportGenerator(this->getSellSide().top(), 'C');
		this->getSellSide().pop();
	}
}

void OrderBook::matchOrder(Order ord)
{
	bool isExecuted = false;
	Order order = ord;
	int execQuantity = 0;
	string contraSideIds = "";
	if (ord.getSide() == 1)
	{
		if (sellSide.size() == 0)
		{
			buySide.push(ord);
			executionReportGenerator(ord, 'N');  ////////////
		}
		else {
			isExecuted = false;
			while (sellSide.size() > 0 && ord.getQuantity() != 0)
			{
				if (sellSide.top().getPrice() <= ord.getPrice())
				{
					Order top = sellSide.top();
					Order topCopy = top;
					sellSide.pop();
					if (top.getQuantity() >= ord.getQuantity())
					{
						cout << "New order finished." << endl;
						//executionReportGenerator(ord, ord.getQuantity(), 0, top.getOrderID());   ////////////
						top.setQuantity(top.getQuantity() - ord.getQuantity());
						execQuantity += ord.getQuantity();
						executionReportGenerator(topCopy, ord.getQuantity(), top.getQuantity(), ord.getOrderID());  ///////////////
						ord.setQuantity(0);
						marketDataSetter(top);
						isExecuted = true;
						if (top.getQuantity() != 0) { sellSide.push(top); }
						if (contraSideIds.size() == 0) {
							contraSideIds += top.getOrderID();
						}
						else {
							contraSideIds += "|";
							contraSideIds += top.getOrderID();
						}
					}
					else if (top.getQuantity() < ord.getQuantity())
					{
						cout << "Top sell order finished." << endl;
						int orderQty = ord.getQuantity();
						ord.setQuantity(ord.getQuantity() - top.getQuantity());
						executionReportGenerator(top, top.getQuantity(), 0, ord.getOrderID());  /////////////////////
						marketDataSetter(top);
						isExecuted = true;
						execQuantity += top.getQuantity();
						if (contraSideIds.size() == 0) {
							contraSideIds += top.getOrderID();
						}
						else {
							contraSideIds += "|";
							contraSideIds += top.getOrderID();
						}
					}
					else { break; }
				}
				else { break; }
			}
			if (isExecuted)
			{
				executionReportGenerator(order, execQuantity, ord.getQuantity(), contraSideIds);      //////////////
				if (ord.getQuantity() != 0) { buySide.push(ord); }
			}
			else
			{
				buySide.push(ord);
				executionReportGenerator(ord, 'N');  ////////////
			}
		}
	}

	else if (ord.getSide() == 2)//sell
	{
		if (buySide.size() == 0)
		{
			sellSide.push(ord);
			executionReportGenerator(ord, 'N');    //New order ExeR generation
		}
		else {
			isExecuted = false;
			while (buySide.size() > 0 && ord.getQuantity() != 0)
			{
				if (buySide.top().getPrice() >= ord.getPrice())
				{
					Order top = buySide.top();
					Order topCopy = top;
					buySide.pop();
					if (top.getQuantity() >= ord.getQuantity())
					{
						cout << "New sell order finished." << endl;
						//executionReportGenerator(ord, ord.getQuantity(), 0, top.getOrderID());   ////////////
						top.setQuantity(top.getQuantity() - ord.getQuantity());
						execQuantity += ord.getQuantity();
						executionReportGenerator(topCopy, ord.getQuantity(), top.getQuantity(), ord.getOrderID());  ///////////////
						ord.setQuantity(0);
						marketDataSetter(top);
						isExecuted = true;
						if (top.getQuantity() != 0) { sellSide.push(top); }
						if (contraSideIds.size() == 0) {
							contraSideIds += top.getOrderID();
						}
						else {
							contraSideIds += "|";
							contraSideIds += top.getOrderID();
						}
					}
					else if (top.getQuantity() < ord.getQuantity())
					{
						cout << "Top buy order finished." << endl;
						int orderQty = ord.getQuantity();
						ord.setQuantity(ord.getQuantity() - top.getQuantity());
						executionReportGenerator(top, top.getQuantity(), 0, ord.getOrderID());  /////////////////////
						marketDataSetter(top);
						isExecuted = true;
						execQuantity += top.getQuantity();
						if (contraSideIds.size() == 0) {
							contraSideIds += top.getOrderID();
						}
						else {
							contraSideIds += "|";
							contraSideIds += top.getOrderID();
						}
					}
					else { break; }
				}
				else { break; }
			}
			if (isExecuted)
			{
				executionReportGenerator(order, execQuantity, ord.getQuantity(), contraSideIds);      //////////////
				if (ord.getQuantity() != 0) { sellSide.push(ord); }
			}
			else
			{
				sellSide.push(ord);
				executionReportGenerator(ord, 'N');  ////////////
			}
		}
	}
}


void OrderBook::executionReportGenerator(Order order, char c)
{
	ExecutionReport exR = ExecutionReport(order, c);
	send_message("127.0.0.1", exR.getReportString());
	if (market->getExecutionReportMap().count(order.getTraderID()) == 0)
	{
		list<ExecutionReport> temp = list<ExecutionReport>();
		temp.push_back(exR);
		market->getExecutionReportMap().insert({ order.getTraderID(), temp });
	}
	else
	{
		market->getExecutionReportMap().find(order.getTraderID())->second.push_back(exR);
	}
}

void OrderBook::executionReportGenerator(Order order, int execQty, int remainQty, string contraID)
{
	ExecutionReport exR = ExecutionReport(order.getSymbol(), order.getSide(), order.getQuantity(), 'E', execQty, remainQty, order.getPrice(), "", order.getTraderID(), order.getOrderID(), contraID, order.getTimestamp());
	send_message("127.0.0.1", exR.getReportString());
	if (market->getExecutionReportMap().count(order.getTraderID()) == 0)
	{
		list<ExecutionReport> temp = list<ExecutionReport>();
		temp.push_back(exR);
		market->getExecutionReportMap().insert({ order.getTraderID(), temp });
	}
	else
	{
		market->getExecutionReportMap().find(order.getTraderID())->second.push_back(exR);
	}
}

void OrderBook::marketDataSetter(Order order)
{
	if (order.getPrice() >= highPrice) { highPrice = order.getPrice(); } //``````````````
	if (order.getPrice() <= lowPrice) { lowPrice = order.getPrice(); }
	lastTradedPrice = order.getPrice();
	//bestBid = this->getBestBid();
	//bestOffer = this->getBestOffer();
	//cout << "MKT DATA SET" << endl;
}


string OrderBook::getMarketDataString()
{
	string strER = "Market Data...\n\t"
		"Symbol: " + getFlower().symbol + "\n\t"
		"Last Traded Price: " + to_string(getLastTradedPrice()) + "\n\t"
		"High price: " + to_string(getHighPrice()) + "\n\t"
		"Low price: " + to_string(getLowPrice()) + "\n\t"
		"Best Bid: " + to_string(getBestBid()) + "\n\t"
		"Best Offer: " + to_string(getBestOffer()) + "\n";
	return strER;
}