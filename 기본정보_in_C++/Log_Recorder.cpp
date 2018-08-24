#include "Log_Recorder.h"

void Log_Recorder::add_log(const Order_token * order, std::string original_value)
{
	if (order->token_count <= 0) assert(0);
	Log * log = new Log();
	log->order.token_count = order->token_count;
	for (int i = 0; i < order->token_count; i++)
		log->order.tokens[i] = order->tokens[i];
	log->original_value = original_value;
	this->logstack.push(log);
}

void Log_Recorder::print_log()
{
	SET_CONSOLE_COLOR(console_color::history_color);
	for (std::stack<Log*> dump = this->logstack; !dump.empty(); dump.pop())
	{
		General_Function::show_order(&dump.top()->order);
		std::cout << "( " << dump.top()->original_value << " )" << std::endl;
	}
	SET_CONSOLE_COLOR_DEFAULT;
}
