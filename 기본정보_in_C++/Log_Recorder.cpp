#include "Log_Recorder.h"
int Log_Recorder::log_count = 0;
std::stack <Log*> Log_Recorder::logstack;
Log_Recorder::~Log_Recorder()
{
	clear_itself();
}

void Log_Recorder::clear_itself()
{
	for (std::stack<Log*> dump = Log_Recorder::logstack; !dump.empty(); dump.pop())
		delete dump.top();
	Log_Recorder::log_count = 0;
}

void Log_Recorder::add_log(const Order_token * order, std::string original_value)
{
	if (Status::get_is_person_loaded() == false) return;
	if (order->token_count <= 0) assert(0);
	Log * log = new Log();
	using namespace option::argument;
	log->order_type = expression::Translation::operation_translate(order->content[operation_position]);
	log->order.token_count = order->token_count;
	for (int i = 0; i < order->token_count; i++) //order copy
		log->order.tokens[i] = order->tokens[i];
	log->original_value = original_value;
	Log_Recorder::logstack.push(log);
	Log_Recorder::log_count++;
}

void Log_Recorder::print_log()
{
	if (Log_Recorder::has_log() == false)
	{
		std::cout << "현재 기록된 로그가 없습니다."<<std::endl;
		return;
	}
	SET_CONSOLE_COLOR(console_color::history_color);
	int count = Log_Recorder::log_count;
	for (std::stack<Log*> dump = Log_Recorder::logstack; !dump.empty(); dump.pop())
	{
		std::cout << "[";
		std::cout.fill('0');
		std::cout.width(General_Function::get_cipher(Log_Recorder::log_count));
		std::cout << count << "] ";
		General_Function::show_order(&dump.top()->order);
		if (dump.top()->original_value != "")
		{
			switch (dump.top()->order_type)
			{
			case argument::order_type::add_:
				break;
			case argument::order_type::del_:
			case argument::order_type::update_:
				std::cout << "    ( " << dump.top()->original_value << " )" << std::endl;
				break;
			default:
				assert(0);
			}
		}
		std::cout << std::endl;
		count--;
	}
	SET_CONSOLE_COLOR_DEFAULT;
}

bool Log_Recorder::has_log()
{
	if (Log_Recorder::log_count > 0)		return true;
	else		return false;
}
