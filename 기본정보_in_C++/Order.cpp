#include "Order.h"
Order_token * Main_Order::order = nullptr;
argument::order_type Main_Order::opcode = option::argument::unknown_;

Order_token * Main_Order::get()
{
	return Main_Order::order;
}

void Main_Order::clear()
{
	if (Main_Order::order != nullptr)
	{
		delete Main_Order::order;
		Main_Order::order = nullptr;
	}
}

void Main_Order::set(Order_token * order)
{
	Main_Order::clear();
	if (order == nullptr)
		assert(0);
	Main_Order::order = order;
	Main_Order::opcode = option::expression::Translation::operation_translate(Main_Order::get_content(argument::operation_position));
}

void Main_Order::set_content(const int index, const std::string value)
{
	Main_Order::order->tokens[index] = value;
}

void Main_Order::set_token_count(const int count)
{
	Main_Order::order->token_count = count;
}

std::string Main_Order::get_content(const int index)
{
	return Main_Order::order->tokens[index];
}

int Main_Order::get_opcode()
{
	return Main_Order::opcode;
}

int Main_Order::get_type()
{
	return Main_Order::get_token_count();
}

int Main_Order::get_token_count()
{
	return Main_Order::order->token_count;
}
