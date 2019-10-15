#pragma once
#include <string>
#include "Order.h"

using namespace std;

class ExecutionReport
{
public:
	ExecutionReport(string symbol, int side, int qty, char execType, int execQty, int remainQty, float price, string reason, string traderID, string orderID, string contraOrderID, long timestamp);
	ExecutionReport(Order ord, char exeTyp);
	//ExecutionReport(Order ord, char exeTyp);
	
	~ExecutionReport();
	string getReportString();
	string getSymbol();
	int getSide() const;
	int getQuantity()const;
	char getExecType()const;
	int getExecutedQuantity()const;
	int getRemainingQuantity()const;
	float getPrice()const;
	string getReason()const;
	string getTraderID()const;
	string getOrderID()const;
	string getContraSideClientOrderIDs()const;
	long getTimestamp()const;

	void setSymbol(string symbol);
	void setSide(int side);
	void setQuantity(int quantity);
	void setExecType(char execType);
	void setExecutedQuantity(int executedQuantity);
	void setRemainingQuantity(int remainingQuantity);
	void setPrice(float price);
	void setReason(string reason);
	void setTraderID(string traderID);
	void setOrderID(string clientOrderID);
	void setContraSideClientOrderIDs(string contraSideClientOrderIDs);
	void setTimestamp(long timestamp);

private:
	string symbol;
	int side;
	int qty;
	char execType;
	int execQty;
	int remainQty;
	float price;
	string reason;
	string traderID;
	string orderID;
	string contraOrderID;
	long timestamp;
};

