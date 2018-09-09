#include "Log.h"

Log::Log(const Order_token * order)
{
	General_Function::order_copy(&this->order_was, order);
}
