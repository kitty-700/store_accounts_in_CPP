#include "Log_Recorder.h"

Log_Recorder::Log_Recorder() : log_count(0) { }

Log_Recorder::~Log_Recorder()
{
	clear_itself();
}

void Log_Recorder::clear_itself()
{
	for (std::stack<Log*> dump = this->logstack; !dump.empty(); dump.pop())
		delete dump.top();
	this->log_count = 0;
}

void Log_Recorder::add_log(const Order_token * order, std::string original_value)
{
	if (order->token_count <= 0) assert(0);
	Log * log = new Log();
	using namespace option::argument;
	log->order_type = Natural_language::operation_translate(order->content[operation_position]);
	log->order.token_count = order->token_count;
	for (int i = 0; i < order->token_count; i++)
		log->order.tokens[i] = order->tokens[i];
	log->original_value = original_value;
	this->logstack.push(log);
	this->log_count++;
}

void Log_Recorder::print_log()
{
	SET_CONSOLE_COLOR(console_color::history_color);
	for (std::stack<Log*> dump = this->logstack; !dump.empty(); dump.pop())
	{
		General_Function::show_order(&dump.top()->order);
		switch (dump.top()->order_type)
		{
		case argument::order_type::add_:
			break;
		case argument::order_type::del_:
			std::cout << "    ( " << dump.top()->original_value << " )" << std::endl;
			break;
		case argument::order_type::update_:
			std::cout << "    ( ¿ø·¡ °ª : " << dump.top()->original_value << " )" << std::endl;
			break;
		default:
			assert(0);
		}
		std::cout << std::endl;
	}
	SET_CONSOLE_COLOR_DEFAULT;
}
