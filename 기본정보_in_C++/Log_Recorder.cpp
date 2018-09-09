#include "Log_Recorder.h"
#include "Site.h"
int Log_Recorder::log_count = 0;
std::stack <Log*> Log_Recorder::undo_stack;
std::stack <Log*> Log_Recorder::redo_stack;
Log_Recorder::~Log_Recorder()
{
	clear_itself();
}

void Log_Recorder::clear_itself()
{
	for (; !Log_Recorder::undo_stack.empty(); Log_Recorder::undo_stack.pop())
	{
		Log * log = Log_Recorder::undo_stack.top();
		delete log;
	}
	Log_Recorder::log_count = 0;
}

Log* Log_Recorder::pre_recording_procedure()
{	//로그를 기록할 대상인지 확인한 후에 현재의 Order를 Log 멤버에 복사한다.
	return nullptr;//임시 땜빵
}

void  Log_Recorder::after_recording_procedure(Log * log)
{
}

void Log_Recorder::record_add_site(std::string site_name)
{
	if (Status::get_is_person_loaded() == false) return;
	if (Main_Order::get_token_count() <= 0) assert(0);
	Log_of_add_site * add_log = new Log_of_add_site(site_name);
	Log_Recorder::undo_stack.push(add_log);
	Log_Recorder::log_count++;
}

void Log_Recorder::record_add_account(std::string site_name, std::string account_ID)
{
}

void Log_Recorder::record_del_site(Site * site)
{
}

void Log_Recorder::record_del_account(std::string site_name, std::string account_ID)
{
}

void Log_Recorder::record_update_site_name(std::string site_name, std::string account_ID, std::string original)
{
}

void Log_Recorder::record_update_account_attribute(std::string site_name, std::string account_ID, std::string attribute, std::string original)
{
}

void Log_Recorder::print_log()
{
	if (Log_Recorder::has_log() == false)
	{
		std::cout << "현재 기록된 로그가 없습니다." << std::endl;
		return;
	}
	namespace color = option::parameters::console_color;
	SET_CONSOLE_COLOR(color::history_color);
	int count = Log_Recorder::log_count;

	for (std::stack<Log*> dump = Log_Recorder::undo_stack; !dump.empty(); dump.pop())
	{	//스택을 복사한다. 포인터만 복사하는거라 실제 포인터에 위치한 값은 변하지 않는다.
		std::cout << "[";
		std::cout.fill('0');
		std::cout.width(General_Function::get_cipher(Log_Recorder::log_count));
		std::cout << count << "] ";
		General_Function::show_order(&dump.top()->order_was);
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
