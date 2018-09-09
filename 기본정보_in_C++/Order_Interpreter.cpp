#include "Order_Interpreter.h"
Person * Order_Interpreter::person = nullptr;
std::string Order_Interpreter::now_loaded_file_name;

namespace arg = option::argument;
namespace err_exp = option::expression::error;
namespace normal_exp = option::expression::normal;
namespace compile = option::parameters::compile;
void Order_Interpreter::init()
{
	std::string load_file_name = compile::default_load_file_name; //가장 처음은 default로 지정된 파일 이름으로 적재를 시도한다.
	while (1)
	{
		if (Order_Interpreter::init_person(load_file_name) == false)
		{
			std::cout << "새 파일 이름을 입력해주시겠습니까? ";
			std::cout << "( 원래 불러오려던 파일 이름 : " << load_file_name << " )" << std::endl;
			std::cout << "새 파일 이름 > ";
			std::string reload_file_name;
			General_Function::order_color_input(reload_file_name);
			load_file_name = reload_file_name;
			continue;
		}
		break;
	}
}
bool Order_Interpreter::init_person(std::string file_name)
{
	Importer importer(file_name);
	Person * imported_person = importer.return_person();
	bool is_success = change_person(imported_person);
	if (is_success == true)
	{
		init_person_success_action(file_name);
		Log_Recorder::clear_itself();
	}
	return is_success;
}
void Order_Interpreter::init_person_success_action(std::string loaded_file_name)
{
	General_Function::print_thin_line();
	Status::set_is_person_loaded(true);
	Order_Interpreter::now_loaded_file_name = loaded_file_name;
	std::cout << Order_Interpreter::person->get_site_count() << " 개의 사이트 정보가 적재되었습니다." << std::endl;
	std::cout << "도움말 : help" << std::endl;
}

Order_Interpreter::~Order_Interpreter()
{
	if (this->person != nullptr)	delete this->person;
}
bool Order_Interpreter::interprete_order(Order_token * order)///★★★★★★★★★★★★★★★★★★★★★★★★
{
	arg::order_type op = operation_translate(order->tokens[arg::operation_position]);
	bool is_exit = false;
	order_forwarding(order, op, &is_exit);
	return is_exit;
}

std::string Order_Interpreter::get_loaded_file_name()
{
	return Order_Interpreter::now_loaded_file_name;
}

void Order_Interpreter::order_forwarding(Order_token * order, argument::order_type op, bool * is_exit)
{
	switch (op)
	{
	case arg::order_type::clear_screen_:
		system("cls");
		break;
	case arg::order_type::add_:
	case arg::order_type::del_:
	case arg::order_type::update_:
	case arg::order_type::load_:
		wanna_filling_sometimse(order, op);
		break;
	case arg::order_type::reload_:
		init_person(Order_Interpreter::now_loaded_file_name);
		break;
	case arg::order_type::log_:
		Log_Recorder::print_log();
		break;
	case arg::order_type::sort_:
		sort(option::argument::instruction::sort::ascending);
		break;
	case arg::order_type::sort_reverse_:
		sort(option::argument::instruction::sort::descending);
		break;
	case arg::order_type::show_site_list_:
	case arg::order_type::show_all_site_information_:
	case arg::order_type::show_one_site_information_with_site_name_:
	case arg::order_type::show_one_site_information_with_number_:
		show(op);
		break;
	case arg::order_type::save_:
	{
		Exporter exp(Order_Interpreter::person, Order_Interpreter::now_loaded_file_name);
		exp.save();
	}
	break;
	case arg::order_type::help_:
		General_Function::help();
		break;
	case arg::order_type::test_:
		Module_tester::module_test();
		break;
	case arg::order_type::exit_:
		exit_precess(is_exit);
		/* (디버그됨)
		로그 기록 때 set_is_person_loaded 이걸 반영 안 하니까 프로그램을 종료하면서
		delete_~종류의 함수들이 소멸자로써 계속 호출될 때 계속 로그를 남기는 add_log()함수가 덩달아 호출됐는데,
		Order가 초기화된 상태에서 로그를 남기려 했으므로 에러가 떴다..
		다행히 호출스택구조 분석을 통해 디버깅을 하였다.
		*/
		break;
	default:
		std::cout << err_exp::msg_not_defined_operation << std::endl;
	}
}

void Order_Interpreter::wanna_filling_sometimse(Order_token * order, argument::order_type op)
{
	try {
		switch (op)
		{
		case arg::order_type::add_:
			add(order);
			break;
		case arg::order_type::del_:
			del(order);
			break;
		case arg::order_type::update_:
			update(order);
			break;
		case arg::order_type::load_:
			load(order);
			break;
		default:
			assert(0);
		}
	}
	catch (Form_Filling_Exception& ex) {
		ex.error_reporting();
	}
}

void Order_Interpreter::exit_precess(bool * is_exit)
{
	if (Log_Recorder::has_log() == true)
	{	//작업 도중에 작업 진행 상황을 잃게 될 수도 있으므로 경고한다.
		if (General_Function::ask_continue_or_not(err_exp::msg_job_unset_warning + " 종료하시겠습니까?") == false) {
			return;
		}
	}
	Status::set_is_person_loaded(false);
	*is_exit = true;
}

arg::order_type Order_Interpreter::operation_translate(std::string query_op)
{
	arg::order_type interpreted_op = option::expression::Translation::operation_translate(query_op);
	if (interpreted_op == arg::order_type::not_translated_but_should_calculated_)
	{
		if (General_Function::is_natural_number(query_op) == true) //사이트 번호 입력
			interpreted_op = arg::order_type::show_one_site_information_with_number_;
		else if (Order_Interpreter::person->find_Site(query_op) != nullptr) //사이트 이름 입력
			interpreted_op = arg::order_type::show_one_site_information_with_site_name_;

		//다만, 번호랑 이름 무엇을 우선시할지는 개발 철학에 달림. 지금의 경우엔 번호가 우선
		else
			interpreted_op = arg::order_type::no_operation_input_;
	}
	return interpreted_op;
}

void Order_Interpreter::add(Order_token * order)
{
	Status::set_is_form_filling_successful(true);
	using namespace arg::instruction::add;
	if (order->token_count == add_form_use)
	{	//order가 완전하지 않을 시엔 Form 입력받기 필요
		Order_Form_Filler(Order_Interpreter::person).add_form_filler();
	}
	if (Status::get_is_form_filling_successful() == true)
		Order_Interpreter::person->add(order);
}

void Order_Interpreter::del(Order_token * order)
{
	Status::set_is_form_filling_successful(true);
	using namespace argument::instruction::del;
	if (order->token_count == delete_form_use)
	{	//order가 완전하지 않을 시엔 Form 입력받기 필요
		Order_Form_Filler(Order_Interpreter::person).del_form_filler();
	}
	if (Status::get_is_form_filling_successful() == true)
		Order_Interpreter::person->del(order);
}

void Order_Interpreter::update(Order_token * order)
{
	Status::set_is_form_filling_successful(true);
	using namespace argument::instruction::update;
	if (order->token_count == modify_form_use)
	{	//order가 완전하지 않을 시엔 Form 입력받기 필요
		Order_Form_Filler(Order_Interpreter::person).update_form_filler();
	}
	if (Status::get_is_form_filling_successful() == true)
		Order_Interpreter::person->update(order);
}

void Order_Interpreter::load(Order_token * order)
{
	Status::set_is_form_filling_successful(true);
	using namespace arg::instruction::load;
	if (Main_Order::get_type() == load_in_default_file_name)
	{	//order가 완전하지 않을 시엔 Form 입력받기 필요
		Order_Form_Filler(Order_Interpreter::person).load_form_filler();
	}
	if (Status::get_is_form_filling_successful() == true) {
		init_person(order->tokens[file_name_position]);
	}
}

void Order_Interpreter::show(int what_type_of_showing)
{	//각 if~else if 문의 순서를 변경할 때는 의미가 달라질 수 있으므로 주의.
	if (Order_Interpreter::person->get_site_count() == 0)
		std::cout << err_exp::msg_person_hasnt_site << std::endl;

	switch (what_type_of_showing)
	{
	case arg::order_type::show_site_list_:// "ls"
		Order_Interpreter::person->show_site_name_list();
		break;
	case arg::order_type::show_all_site_information_:// "ll"
		Order_Interpreter::person->show_all_sites_information();
		break;
	case arg::order_type::show_one_site_information_with_site_name_:// "google"
		show_site_in_site_name();
		break;
	case arg::order_type::show_one_site_information_with_number_: // "12"
		show_site_in_number();
		break;
	default:
		std::cout << err_exp::msg_unsupport_order_form << std::endl;
		assert(0);
	}
}

void Order_Interpreter::sort(bool is_ascending)
{
	Order_Interpreter::person->sort(is_ascending);
}


void Order_Interpreter::show_site_in_number()//숫자로 사이트 찾아주기
{	//"12" 처럼 사이트 번호만으로 정보를 찾는다.
	try { //token 수가 1개가 아니면 함수 종료.
		if (Main_Order::get_type() != argument::instruction::show::no_additional_arguments)
			throw err_exp::msg_unsupport_order_form;
	}
	catch (std::string error_message) {
		std::cout << error_message << std::endl;
		return;
	}
	int number = General_Function::string_to_integer(Main_Order::get_content(arg::operation_position));
	//order의 첫번째 토큰을 숫자로 바꾼다. "12" -> 12
	if (number == 0) { //0번 사이트는 없으나, 사이트 목록을 출력하는 것으로 대신한다.
		Order_Interpreter::person->show_site_name_list();
	}
	else if ((1 <= number) && (number <= Order_Interpreter::person->get_site_count()))
	{
		Site * temp_site = Order_Interpreter::person->find_Site(number);
		Order_Interpreter::person->show_one_site_information(temp_site, number);
	}
	else {
		std::cout << err_exp::msg_no_existing_site_number << std::endl;
	}
	return;
}

void Order_Interpreter::show_site_in_site_name()
{	//"google" 처럼 사이트 이름만으로 정보를 찾는다.
	try { //token 수가 1개가 아니면 함수 종료.
		if (Main_Order::get_type() != argument::instruction::show::no_additional_arguments)
			throw err_exp::msg_unsupport_order_form;
	}
	catch (std::string error_message) {
		std::cout << error_message << std::endl;
		return;
	}
	Site * temp_site = Order_Interpreter::person->find_Site(Main_Order::get_content(arg::operation_position));
	try {
		if (temp_site == nullptr)
			throw err_exp::msg_no_existing_site_name;
	}
	catch (std::string error_message) {
		std::cout << error_message << std::endl;
		return;
	}
	int site_number = Order_Interpreter::person->find_Site_number(temp_site->get_site_name());
	Order_Interpreter::person->show_one_site_information(temp_site, site_number);
}

bool Order_Interpreter::change_person(Person * person_to_change)
{
	if (person_to_change->get_is_alive() == false) {
		delete person_to_change;
		return false;
	}
	else
	{
		if (Log_Recorder::continue_although_unsaved() == true)
		{
			if (Order_Interpreter::person != nullptr) delete Order_Interpreter::person;
			Order_Interpreter::person = person_to_change;
			return true;
		}
		return false;
	}
}
