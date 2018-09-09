#include "Log.h"

Log::Log()
{
	General_Function::order_copy(&this->order_was, Main_Order::get());
}
