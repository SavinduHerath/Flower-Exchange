//#include "gtest/gtest.h"
//#include "Order.h"
//#include "OrderBook.h"
//#include "Market.h"
//#include "Flower.h"
//#include "ExecutionReport.h"
//#include "ConnectorExchange.h"
//
//
//TEST(OrderBook, PriorityQueueBuy)
//{
//	//Arrange
//	Order order1("Rose", 1, 100, 5,
//		"TR1", "A", 123123123);
//	Order order2("Rose", 1, 300, 4,
//		"TR3", "C", 123123123);
//	Order order3("Rose", 1, 200, 7,
//		"TR1", "B", 123123123);
//	Market  test_market = Market();
//	OrderBook OB1 = test_market.getOrderBooks().find("rose")->second;
//
//	//Act
//	OB1.matchOrder(order1);
//	OB1.matchOrder(order2);
//	OB1.matchOrder(order3);
//	OB1.getBuySide(); 
//	
//	//Assert
//	Order oo = OB1.getBuySide().top();	
//	EXPECT_FLOAT_EQ(7.0, oo.getPrice());
//
//	OB1.getBuySide().pop();
//	oo = OB1.getBuySide().top();
//	EXPECT_FLOAT_EQ(5.0, oo.getPrice());
//
//	OB1.getBuySide().pop();
//	oo = OB1.getBuySide().top();
//	EXPECT_FLOAT_EQ(4, oo.getPrice());
//
//	EXPECT_EQ(1, test_market.getExecutionReportMap().find("TR3")->second.size());
//
//}
//
//
//TEST(OrderBook, PriorityQueueSell)
//{
//	Order order1("Rose", 2, 100, 5,
//		"TR1", "A", 123123123);
//	Order order2("Rose", 2, 300, 4,
//		"TR1", "C", 123123123);
//	Order order3("Rose", 2, 200, 7,
//		"TR1", "B", 123123123);
//	Market  test_market = Market();
//	OrderBook OB1 = test_market.getOrderBooks().find("rose")->second;
//	OB1.matchOrder(order1);
//	OB1.matchOrder(order2);
//	OB1.matchOrder(order3);
//
//
//	Order oo = OB1.getSellSide().top();
//	EXPECT_FLOAT_EQ(4.0, oo.getPrice());
//
//	OB1.getSellSide().pop();
//	oo = OB1.getSellSide().top();
//	EXPECT_FLOAT_EQ(5.0, oo.getPrice());
//
//	OB1.getSellSide().pop();
//	oo = OB1.getSellSide().top();
//	EXPECT_FLOAT_EQ(7, oo.getPrice());
//
//	EXPECT_EQ(3, test_market.getExecutionReportMap().find("TR1")->second.size());
//}
//
//TEST(Market, test_constructor) {
//
//	Market test_market; // t = Market();
//	unordered_map<string, OrderBook> test_map = test_market.getOrderBooks();
//
//	EXPECT_EQ(100, test_map.find("rose")->second.getFlower().lotSize);
//	//cout << test_map.find("tulip")->second.getFlower().lotSize << endl;
//}
//
//TEST(OrderBook, matchOrder_finish_newBuy) {
//	Order order1("Rose", 2, 100, 5,
//		"TR1", "A", 123123123);
//	Order order2("Rose", 2, 300, 4,
//		"TR3", "C", 123123123);
//	Order order3("Rose", 2, 200, 7,
//		"TR2", "B", 123123123);
//	Order order4("Rose", 1, 200, 4,
//		"TR4", "D", 123123123);
//	Market*  test_market = new Market();
//	OrderBook OB1 = test_market->getOrderBooks().find("rose")->second;
//	OB1.matchOrder(order1);
//	OB1.matchOrder(order2);
//	OB1.matchOrder(order3);
//	OB1.matchOrder(order4);
//
//	Order oo = OB1.getSellSide().top();
//	EXPECT_EQ(100, oo.getQuantity());
//
//
//	EXPECT_EQ(2, test_market->getExecutionReportMap().find("TR3")->second.size());
//	EXPECT_EQ(1, test_market->getExecutionReportMap().find("TR4")->second.size());
//	EXPECT_EQ(1, test_market->getExecutionReportMap().find("TR2")->second.size());
//}
//
//
//TEST(OrderBook, matchOrder_finish_existingSell) {
//	Order order1("Rose", 2, 100, 5,
//		"TR1", "A", 123123123);
//	Order order2("Rose", 2, 300, 4,
//		"TR3", "C", 123123124);
//	Order order3("Rose", 2, 300, 4,
//		"TR2", "B", 123123123);
//	Order order4("Rose", 1, 400, 4,
//		"TR4", "D", 123123123);
//	Market  test_market = Market();
//	OrderBook OB1 = test_market.getOrderBooks().find("rose")->second;
//	OB1.matchOrder(order1);
//	OB1.matchOrder(order2);
//	OB1.matchOrder(order3);
//	OB1.matchOrder(order4);
//
//	Order oo = OB1.getSellSide().top();
//
//	EXPECT_FLOAT_EQ(4.0, oo.getPrice());
//	EXPECT_EQ(200, oo.getQuantity());
//
//	EXPECT_EQ(1, test_market.getExecutionReportMap().find("TR4")->second.size());
//	EXPECT_EQ(2, test_market.getExecutionReportMap().find("TR3")->second.size());
//	EXPECT_EQ(2, test_market.getExecutionReportMap().find("TR2")->second.size());
//}
//
//TEST(OrderBook, matchOrder_finish_existingBuy) {
//	Order order1("Rose", 1, 100, 5,
//		"TR1", "A", 123123123);
//	Order order2("Rose", 1, 300, 4,
//		"TR3", "C", 123123124);
//	Order order3("Rose", 1, 300, 4,
//		"TR2", "B", 123123123);
//	Order order4("Rose", 2, 400, 4,
//		"TR4", "D", 123123123);
//	Market  test_market = Market();
//	OrderBook OB1 = test_market.getOrderBooks().find("rose")->second;
//	OB1.matchOrder(order1);
//	OB1.matchOrder(order2);
//	OB1.matchOrder(order3);
//	OB1.matchOrder(order4);
//
//	//Order oo = OB1.getSellSide().top();
//	//EXPECT_EQ(200, oo.getQuantity());
//
//	Order oo = OB1.getBuySide().top();
//
//	EXPECT_FLOAT_EQ(4.0, oo.getPrice());
//	EXPECT_EQ(300, oo.getQuantity());
//}
//
//TEST(OrderBook, matchOrder_finish_newSell) {
//	Order order1("Rose", 1, 100, 5,
//		"TR1", "A", 123123123);
//	Order order2("Rose", 1, 300, 4,
//		"TR3", "C", 123123123);
//	Order order3("Rose", 1, 300, 7,
//		"TR2", "B", 123123123);
//	Order order4("Rose", 2, 200, 7,
//		"TR4", "D", 123123123);
//	Market*  test_market = new Market();
//	OrderBook OB1 = test_market->getOrderBooks().find("rose")->second;
//	OB1.matchOrder(order1);
//	OB1.matchOrder(order2);
//	OB1.matchOrder(order3);
//	OB1.matchOrder(order4);
//
//	//Order oo = OB1.getSellSide().top();
//	//EXPECT_EQ(200, oo.getQuantity());
//
//
//	EXPECT_EQ(1, test_market->getExecutionReportMap().find("TR3")->second.size());
//	EXPECT_EQ(1, test_market->getExecutionReportMap().find("TR4")->second.size());
//
//	//EXPECT_EQ(2, test_market->getExecutionReportMap().find("TR3")->second.size());
//	//EXPECT_EQ(1, test_market->getExecutionReportMap().find("TR4")->second.size());
//	EXPECT_EQ(2, test_market->getExecutionReportMap().find("TR2")->second.size());
//}
//
//TEST(ExecutionReport, setExecutionReportMap)
//{
//	Order order1("Rose", 1, 100, 5,
//		"TR1", "A", 123123123);
//	Order order2("Rose", 1, 300, 4,
//		"TR3", "C", 123123123);
//	Order order3("Rose", 1, 200, 7,
//		"TR2", "B", 123123123);
//	Market  test_market = Market();
//	OrderBook OB1 = test_market.getOrderBooks().find("rose")->second;
//	OB1.matchOrder(order1);
//	Market  test_market = Market();
//	OrderBook OB1 = test_market.getOrderBooks().find("rose")->second;
//	OB1.matchOrder(order1);
//}
//
//TEST(stringSpliterFunction, orderGeneration)
//{
//	Order* order = convertOrder("TR1 A buy rose 150@10.50");
//	Market  test_market = Market();
//	OrderBook OB1 = test_market.getOrderBooks().find("rose")->second;
//	OB1.matchOrder(order1);
//	Market  test_market = Market();
//	OrderBook OB1 = test_market.getOrderBooks().find("rose")->second;
//	OB1.matchOrder(order1);
//	Market  test_market = Market();
//	OrderBook OB1 = test_market.getOrderBooks().find("rose")->second;
//	OB1.matchOrder(*order);
//
//
//	EXPECT_EQ(1, order->getSide());
//	EXPECT_EQ(150, order->getQuantity());
//	EXPECT_EQ("A", order->getOrderID());
//
//	//Order oo = ;
//	EXPECT_FLOAT_EQ(10.50, OB1.getBuySide().top().getPrice());
//}
//
////TEST(marketDataSetterFunction, mktData)
////{
////	OrderBook OB = OrderBook();
////	//marketDataSetter()
////}
//
//TEST(MarketClass, addOrderFromString)
//{
//	Order* order = convertOrder("TR1 A buy rose 150@10.50");
//	Market  test_market = Market();
//	test_market.addOrder(order);
//
//
//	OrderBook OB1 = test_market.getOrderBooks().find("rose")->second;
//	Order od = OB1.getBuySide().top();
//	EXPECT_EQ(1,  od.getSide());
//	EXPECT_EQ(150, od.getQuantity());
//	EXPECT_EQ("A", od.getOrderID());
//
//	//Order oo = ;
//	//EXPECT_FLOAT_EQ(10.50, OB1.getBuySide().top().getPrice());
//}
//
///*TEST(ConnectorExchange, validateOrder)
//{
//	Market* market = new Market;
//	ConnectorExchange conn = ConnectorExchange(market);
//	conn.v
//}*/