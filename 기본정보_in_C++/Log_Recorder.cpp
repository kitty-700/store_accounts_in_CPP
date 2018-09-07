#include "Log_Recorder.h"
#include "Site.h"
int Log_Recorder::log_count = 0;
std::stack <Log*> Log_Recorder::logstack;
Log_Recorder::~Log_Recorder()
{
	clear_itself();
}

void Log_Recorder::clear_itself()
{
	for (; !Log_Recorder::logstack.empty(); Log_Recorder::logstack.pop())
	{
		Log * log = Log_Recorder::logstack.top();
		delete log;
	}
	Log_Recorder::log_count = 0;
}

Log* Log_Recorder::pre_recording_procedure()
{	//로그를 기록할 대상인지 확인한 후에 현재의 Order를 Log 멤버에 복사한다.
	if (Status::get_is_person_loaded() == false) return nullptr;
	if (Order::get_token_count() <= 0) assert(0);
	Log * log = new Log();
	using namespace option::argument;
	log->order_type = option::expression::Translation::operation_translate(Order::get_content(operation_position));
	Log_Recorder::order_copy(&log->order_was, Order::get());
	return log;
}

void  Log_Recorder::after_recording_procedure(Log * log)
{
	Log_Recorder::logstack.push(log);
	Log_Recorder::log_count++;
}

void Log_Recorder::record_add_site(const Order_token * order, std::string site_name)
{
	Log * log = pre_recording_procedure();
	if (log == nullptr) return;
	after_recording_procedure(log);
}

void Log_Recorder::record_add_account(const Order_token * order, std::string site_name, std::string account_ID)
{
	Log * log = pre_recording_procedure();
	if (log == nullptr) return;
	after_recording_procedure(log);
}

void Log_Recorder::record_del_site(const Order_token * order, Site * site)
{
	Log * log = pre_recording_procedure();
	if (log == nullptr) return;
	after_recording_procedure(log);
}

void Log_Recorder::record_del_account(const Order_token * order, std::string site_name, std::string account_ID)
{
	Log * log = pre_recording_procedure();
	if (log == nullptr) return;
	after_recording_procedure(log);
}

void Log_Recorder::record_update_site_name(const Order_token * order, std::string site_name, std::string account_ID, std::string original)
{
	Log * log = pre_recording_procedure();
	if (log == nullptr) return;
	after_recording_procedure(log);
}

void Log_Recorder::record_update_account_attribute(const Order_token * order, std::string site_name, std::string account_ID, std::string attribute, std::string original)
{
	Log * log = pre_recording_procedure();
	if (log == nullptr) return;
	after_recording_procedure(log);
}

void Log_Recorder::print_log()
{
	if (Log_Recorder::has_log() == false)
	{
		std::cout << "현재 기록된 로그가 없습니다."<<std::endl;
		return;
	}
	namespace color = option::parameters::console_color;
	SET_CONSOLE_COLOR(color::history_color);
	int count = Log_Recorder::log_count;
	
	for (std::stack<Log*> dump = Log_Recorder::logstack; !dump.empty(); dump.pop())
	{	//스택을 복사한다. 포인터만 복사하는거라 실제 포인터에 위치한 값은 변하지 않는다.
		std::cout << "[";
		std::cout.fill('0');
		std::cout.width(General_Function::get_cipher(Log_Recorder::log_count));
		std::cout << count << "] ";
		General_Function::show_order(&dump.top()->order_was);
		if (dump.top()->original_value != "")
		{
			switch (dump.top()->order_type)
			{
			case argument::order_type::add_:
			case argument::order_type::del_:
			case argument::order_type::update_:
				std::cout << dump.top()->original_value << std::endl;
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

void Log_Recorder::order_copy(Order_token * destination_order, const Order_token * source_order)
{
	for (int i = 0; i < source_order->token_count; i++) //order copy
		destination_order->tokens[i] = source_order->tokens[i];
	destination_order->token_count = source_order->token_count;
}

bool Log_Recorder::continue_although_unsaved()
{
	if (Log_Recorder::has_log() == true)
	{	//작업 도중에 작업 진행 상황을 잃게 될 수도 있으므로 경고한다.
		if (General_Function::ask_continue_or_not(option::expression::error::msg_job_reset_warning + " 진행하시겠습니까?") == true) {
			return true;
		}
		else {
			std::cout << option::expression::error::msg_cancel << std::endl;
			return false;
		}
	}
	else {
		return true;
	}
}
