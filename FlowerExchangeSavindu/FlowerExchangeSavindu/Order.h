#pragma once
#include <string>

using namespace std;

class Order
{
public:
	Order(string symbol, int side, int quantity, float price,
		string traderID, string orderID, long timestamp);
	~Order();
	string getSymbol();
	int getSide();
	int& getQuantity();
	float getPrice() const;
	string getTraderID();
	string getOrderID();
	long getTimestamp();
	void setQuantity(int newQty);

	bool operator < (const Order&) const;
	bool operator > (const Order&) const;


private:
	string symbol;
	int side;
	int qty;
	float price;
	string traderID;
	string orderID;
	long timestamp;
};