#pragma once
#ifndef _LOG_H_ 
#define _LOG_H_
#include <string>
#include "Structs.h"
#include "Order.h"
#include "General_Function.h"
#include "Order_Token_Refiner.h"

class Log {
public:
	Order_token order_was;
	std::stack<Order_token *>roll_back_orders;
	Log(const Order_token *order);
};
#endif