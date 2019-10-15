#include <iostream>
#include "Order.h"
#include <sstream>
#include "OrderBook.h"
using namespace std;


Order::Order(string symbol, int side, int quantity, float price, string traderID, string orderID, long timestamp)
	: symbol(symbol), side(side), qty(quantity), price(price), traderID(traderID), orderID(orderID), timestamp(timestamp)
{
	/*stringstream   linestream(line);

	getline(linestream, traderID, ' ');
	getline(linestream, orderID, ' ');
	getline(linestream, side, ' ');
	getline(linestream, symbol, ' ');
	getline(linestream, qty, '@');
	getline(linestream, price, ' ');

	iPrice = stoi(price);
	iQty = stoi(qty);*/
}

Order::~Order()
{}

string Order::getSymbol() { return symbol; }
int Order::getSide() { return side; }
int& Order::getQuantity() { return qty; }
float Order::getPrice() const { return price; }
string Order::getTraderID() { return traderID; }
string Order::getOrderID() { return orderID; }
long Order::getTimestamp() { return timestamp; }

void Order::setQuantity(int newQty)
{
	qty = newQty;
}


bool Order::operator < (const Order& rhs) const
{
	if (price == rhs.price)
	{
		return timestamp > rhs.timestamp;
	}
	else
	{
		if (rhs.side == 1) {
			return price < rhs.price;
		}
		else if (rhs.side == 2) {
			return price > rhs.price;
		}
		else
		{
			cout << "Side Error" << endl;
			throw exception("Side Error");
		}
	}
}

bool Order::operator > (const Order& rhs) const
{
	if (price == rhs.price)
	{
		return timestamp < rhs.timestamp;
	}
	else
	{
		if (rhs.side == 1) {
			return price > rhs.price;
		}
		else if (rhs.side == 2) {
			return price < rhs.price;
		}
		else
		{
			cout << "Side Error" << endl;
			throw exception("Side Error");
		}
	}
}