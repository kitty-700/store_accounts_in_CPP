#pragma once
#ifndef _LOG_H_ 
#define _LOG_H_
#include "Structs.h"
class Log {
public:
	option::argument::order_type order_type;
	Order_token order_was;
	std::string original_value;
	std::stack<Order_token *>roll_back_orders;
	Log();
};
#endif