#pragma once
#ifndef _ORDER_H_
#define _ORDER_H_
#include <assert.h>
#include "Argument.h"
#include "Structs.h"
class Order {
	static Order_token * order;
	static argument::order_type op;
public:
	static Order_token * get();
	static void clear();
	static void set(Order_token*order);
	static void set_content(const int index, const std::string value);
	static void set_token_count(const int count);
	static std::string get_content(const int index);
	static int get_type();
	static int get_token_count();
};
#endif