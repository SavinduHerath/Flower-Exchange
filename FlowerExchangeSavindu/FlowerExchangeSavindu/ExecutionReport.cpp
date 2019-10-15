#include "ExecutionReport.h"

using namespace std;

ExecutionReport::ExecutionReport(string symbol, int side, int qty, char execType, int execQty, int remainQty, float price, string reason, string traderID, string orderID, string contraOrderID, long timestamp):
	symbol(symbol), side(side), qty(qty), execType(execType), execQty(execQty), remainQty(remainQty), price(price), reason(reason), traderID(traderID), orderID(orderID), contraOrderID(contraOrderID), timestamp(timestamp)
{
}

ExecutionReport::ExecutionReport(Order ord, char exeTyp)
{
	symbol = ord.getSymbol();
	side = ord.getSide();
	qty = ord.getQuantity();
	execType = exeTyp;
	execQty = 0;
	remainQty = 0;
	price = ord.getPrice();
	//reason;
	traderID = ord.getTraderID();
	orderID = ord.getOrderID();
	//contraOrderID;
	timestamp = ord.getTimestamp();
}



ExecutionReport::~ExecutionReport()
{
}

string ExecutionReport::getReportString()
{
	string strER = "\nExecution report...\n\t"
		"Symbol: " + getSymbol() + "\n\t"
		"Side: " + to_string(getSide()) + "\n\t"
		"Quantity: " + to_string(getQuantity()) + "\n\t"
		"Execution Type: " + string(1, getExecType()) + "\n\t"
		"Executed Quantity: " + to_string(getExecutedQuantity()) + "\n\t"
		"Remaining Quantity: " + to_string(getRemainingQuantity()) + "\n\t"
		"Price: " + to_string(getPrice()) + "\n\t"
		"Reason: " + getReason() + "\n\t"
		"TraderID: " + getTraderID() + "\n\t"
		"ClientOrderID: " + getOrderID() + "\n\t";
	if (getExecType() != 'N') {
		strER += "contraSideClientOrderIDs: " + getContraSideClientOrderIDs() + "\n\t";
	}
		strER += "Timestamp: " + to_string(getTimestamp()) + "\n";
	return strER;
}

string ExecutionReport::getSymbol() { return symbol; }
int ExecutionReport::getSide() const { return side; }
int ExecutionReport::getQuantity() const { return qty; }
char ExecutionReport::getExecType() const { return execType; }
int ExecutionReport::getExecutedQuantity() const { return execQty; }
int ExecutionReport::getRemainingQuantity() const { return remainQty; }
float ExecutionReport::getPrice() const { return price; }
string ExecutionReport::getReason() const { return reason; }
string ExecutionReport::getTraderID() const { return traderID; }
string ExecutionReport::getOrderID() const { return orderID; }
string ExecutionReport::getContraSideClientOrderIDs() const { return contraOrderID; }
long ExecutionReport::getTimestamp() const { return timestamp; }

void ExecutionReport::setSymbol(string s) { symbol = s; }
void ExecutionReport::setSide(int s) { side = s; }
void ExecutionReport::setQuantity(int q) { qty = q; }
void ExecutionReport::setExecType(char e) { execType = e; }
void ExecutionReport::setExecutedQuantity(int e) { execQty = e; }
void ExecutionReport::setRemainingQuantity(int r) { remainQty = r; }
void ExecutionReport::setPrice(float p) { price = p; }
void ExecutionReport::setReason(string r) { reason = r; }
void ExecutionReport::setTraderID(string t) { traderID = t; }
void ExecutionReport::setOrderID(string c) { orderID = c; }
void ExecutionReport::setContraSideClientOrderIDs(string c) { contraOrderID = c; }
void ExecutionReport::setTimestamp(long t) { timestamp = t; }
