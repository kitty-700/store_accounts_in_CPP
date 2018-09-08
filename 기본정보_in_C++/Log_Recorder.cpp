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
{	//�α׸� ����� ������� Ȯ���� �Ŀ� ������ Order�� Log ����� �����Ѵ�.
	return nullptr;//�ӽ� ����
}

void  Log_Recorder::after_recording_procedure(Log * log)
{
}

void Log_Recorder::record_add_site(const Order_token * order, std::string site_name)
{
	if (Status::get_is_person_loaded() == false) return;
	if (Main_Order::get_token_count() <= 0) assert(0);
	Log_of_add * add_log = new Log_of_add;
	add_log->order_type = option::expression::Translation::operation_translate(Main_Order::get_content(option::argument::operation_position));
	Log_Recorder::order_copy(&add_log->order_was, Main_Order::get());
	Log_Recorder::undo_stack.push(add_log);
	Log_Recorder::log_count++;
}

void Log_Recorder::record_add_account(const Order_token * order, std::string site_name, std::string account_ID)
{
}

void Log_Recorder::record_del_site(const Order_token * order, Site * site)
{
}

void Log_Recorder::record_del_account(const Order_token * order, std::string site_name, std::string account_ID)
{
}

void Log_Recorder::record_update_site_name(const Order_token * order, std::string site_name, std::string account_ID, std::string original)
{
}

void Log_Recorder::record_update_account_attribute(const Order_token * order, std::string site_name, std::string account_ID, std::string attribute, std::string original)
{
}

void Log_Recorder::print_log()
{
	if (Log_Recorder::has_log() == false)
	{
		std::cout << "���� ��ϵ� �αװ� �����ϴ�."<<std::endl;
		return;
	}
	namespace color = option::parameters::console_color;
	SET_CONSOLE_COLOR(color::history_color);
	int count = Log_Recorder::log_count;
	
	for (std::stack<Log*> dump = Log_Recorder::undo_stack; !dump.empty(); dump.pop())
	{	//������ �����Ѵ�. �����͸� �����ϴ°Ŷ� ���� �����Ϳ� ��ġ�� ���� ������ �ʴ´�.
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

void Log_Recorder::order_copy(Order_token * destination_order, const Order_token * source_order)
{
	for (int i = 0; i < source_order->token_count; i++) //order copy
		destination_order->tokens[i] = source_order->tokens[i];
	destination_order->token_count = source_order->token_count;
}

bool Log_Recorder::continue_although_unsaved()
{
	if (Log_Recorder::has_log() == true)
	{	//�۾� ���߿� �۾� ���� ��Ȳ�� �Ұ� �� ���� �����Ƿ� ����Ѵ�.
		if (General_Function::ask_continue_or_not(option::expression::error::msg_job_reset_warning + " �����Ͻðڽ��ϱ�?") == true) {
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
