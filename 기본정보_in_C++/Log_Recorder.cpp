#include "Log_Recorder.h"
#include "Site.h"
int Log_Recorder::log_count = 0;
std::stack <Log*> Log_Recorder::order_log;
Log_Recorder::~Log_Recorder()
{
	clear_itself();
}

void Log_Recorder::clear_itself()
{
	for (; !Log_Recorder::order_log.empty(); Log_Recorder::order_log.pop())
	{
		Log * log = Log_Recorder::order_log.top();
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

void Log_Recorder::record_add_site(Order_token *order, std::string site_name)
{
	if (Status::get_is_person_loaded() == false) return;
	if (Main_Order::get_token_count() <= 0) assert(0);
	Log * new_log = new Log(order);
	//
	std::string roll_back_order = "del " + site_name;
	new_log->roll_back_orders.push(Order_Token_Refiner(new Order_token).refining(roll_back_order));
	//
	Log_Recorder::order_log.push(new_log);
	Log_Recorder::log_count++;
}

void Log_Recorder::record_add_account(Order_token *order, std::string site_name, std::string account_ID)
{
	if (Status::get_is_person_loaded() == false) return;
	if (Main_Order::get_token_count() <= 0) assert(0);
	Log * new_log = new Log(order);
	//
	std::string roll_back_order = "del " + site_name + " " + account_ID;
	new_log->roll_back_orders.push(Order_Token_Refiner(new Order_token).refining(roll_back_order));
	//
	Log_Recorder::order_log.push(new_log);
	Log_Recorder::log_count++;
}

void Log_Recorder::record_del_site(Order_token *order, Site * site)
{
	if (Status::get_is_person_loaded() == false) return;
	if (Main_Order::get_token_count() <= 0) assert(0);
	Log * new_log = new Log(order);
	//
	for (int i = 1; i <= site->get_account_count(); i++) {
		std::string roll_back_order;
		roll_back_order = "update ";
		roll_back_order += site->get_site_name() + " ";
		roll_back_order += site->find_account_with_account_number(i)->get_attribute("ID") + " ";
		roll_back_order += "date ";
		roll_back_order += site->find_account_with_account_number(i)->get_attribute("date");
		new_log->roll_back_orders.push(Order_Token_Refiner(new Order_token).refining(roll_back_order));
		roll_back_order = "add ";
		roll_back_order += site->get_site_name() + " ";
		roll_back_order += site->find_account_with_account_number(i)->get_attribute("ID") + " ";
		roll_back_order += site->find_account_with_account_number(i)->get_attribute("PW") + " ";
		roll_back_order += site->find_account_with_account_number(i)->get_attribute("Memo");
		new_log->roll_back_orders.push(Order_Token_Refiner(new Order_token).refining(roll_back_order));
	}
	//
	Log_Recorder::order_log.push(new_log);
	Log_Recorder::log_count++;
}

void Log_Recorder::record_del_account(Order_token *order, Site * site, std::string account_ID)
{
	if (Status::get_is_person_loaded() == false) return;
	if (Main_Order::get_token_count() <= 0) assert(0);
	Log * new_log = new Log(order);
	//
	std::string roll_back_order;
	roll_back_order = "update ";
	roll_back_order += site->get_site_name() + " ";
	roll_back_order += site->find_account_with_ID(account_ID)->get_attribute("ID") + " ";
	roll_back_order += "date ";
	roll_back_order += site->find_account_with_ID(account_ID)->get_attribute("date");
	new_log->roll_back_orders.push(Order_Token_Refiner(new Order_token).refining(roll_back_order));
	roll_back_order = "add ";
	roll_back_order += site->get_site_name() + " ";
	roll_back_order += site->find_account_with_ID(account_ID)->get_attribute("ID") + " ";
	roll_back_order += site->find_account_with_ID(account_ID)->get_attribute("PW") + " ";
	roll_back_order += site->find_account_with_ID(account_ID)->get_attribute("Memo");
	new_log->roll_back_orders.push(Order_Token_Refiner(new Order_token).refining(roll_back_order)); //스택이니까 넣는 순서 주의
	//
	Log_Recorder::order_log.push(new_log);
	Log_Recorder::log_count++;
}

void Log_Recorder::record_update_site_name
(Order_token *order, std::string site_name, std::string account_ID, std::string original)
{
	if (Status::get_is_person_loaded() == false) return;
	if (Main_Order::get_token_count() <= 0) assert(0);
	Log * new_log = new Log(order);
	//
	std::string roll_back_order;
	roll_back_order = "update ";
	roll_back_order += site_name + " ";
	roll_back_order += original + " ";
	new_log->roll_back_orders.push(Order_Token_Refiner(new Order_token).refining(roll_back_order)); 
	//
	Log_Recorder::order_log.push(new_log);
	Log_Recorder::log_count++;
}

void Log_Recorder::record_update_account_attribute
(Order_token *order, std::string site_name, std::string account_ID, std::string attribute, std::string original)
{
	if (Status::get_is_person_loaded() == false) return;
	if (Main_Order::get_token_count() <= 0) assert(0);
	Log * new_log = new Log(order);
	//
	std::string roll_back_order;
	roll_back_order = "update ";
	roll_back_order += site_name + " ";
	roll_back_order += account_ID + " ";
	roll_back_order += attribute + " ";
	roll_back_order += original + " ";
	new_log->roll_back_orders.push(Order_Token_Refiner(new Order_token).refining(roll_back_order));
	//
	Log_Recorder::order_log.push(new_log);
	Log_Recorder::log_count++;
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

	for (std::stack<Log*> dump = Log_Recorder::order_log; !dump.empty(); dump.pop())
	{	//스택을 복사한다. 포인터만 복사하는거라 실제 포인터에 위치한 값은 변하지 않는다.
		std::cout << "[";
		std::cout.fill('0');
		std::cout.width(General_Function::get_cipher(Log_Recorder::log_count));
		std::cout << count << "] ";
		General_Function::show_order(&dump.top()->order_was);
		std::cout << std::endl;
		std::cout << "undo orders - " << std::endl;
		for (	std::stack<Order_token *> secondary_order = dump.top()->roll_back_orders; !secondary_order.empty(); secondary_order.pop())
			General_Function::show_order(secondary_order.top());
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
