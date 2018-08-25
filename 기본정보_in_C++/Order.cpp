#include "Order.h"
Order_token * Order::order = nullptr;

Order_token * Order::get()
{
	return Order::order;
}

void Order::clear()
{
	if (Order::order != nullptr)
	{
		delete Order::order;
		Order::order = nullptr;
	}
}

void Order::set(Order_token * order)
{
	if (Order::order != nullptr)
		delete Order::order;
	if (order == nullptr)
		assert(0);
	Order::order = order;
}

void Order::change_content(const int index, const std::string value)
{
	Order::order->tokens[index] = value;
}

void Order::change_count(const int count)
{
	Order::order->token_count = count;
}

std::string Order::get_content(const int index)
{
	return Order::order->tokens[index];
}

int Order::get_type()
{
	return Order::get_token_count();
}

int Order::get_token_count()
{
	return Order::order->token_count;
}
