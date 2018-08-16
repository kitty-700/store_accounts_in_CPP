#include "Order_Interpreter.h"

namespace arg = option::argument;
namespace err_exp = option::error_expression;
int Order_Interpreter::init_person(std::string file_name)
{
	Importer importer(file_name);
	this->person = importer.return_person();
	if (this->person->get_is_alive() == false)
	{
		delete this->person;
		return false;
	}
	return true;
}
Order_Interpreter::Order_Interpreter()
{	//당연한 소리지만, 파일을 읽어와야 프로그램을 시작할 수 있다.
	std::string load_file_name = compile::default_load_file_name;
	while (1)
	{
		if (init_person(load_file_name) == false)
		{
			std::string reload_file_name;
			std::cout << "새 파일 이름을 입력해주시겠습니까? ";
			std::cout << "( 원래 불러오려던 파일 이름 : " << load_file_name << " )" << std::endl;
			std::cout << "새 파일 이름 > ";
			std::cin >> reload_file_name;
			std::cin.ignore();
			load_file_name = reload_file_name;
			continue;
		}
		Status::set_is_person_loaded(true);
		std::cout << this->person->get_site_count() << " 개의 사이트 정보가 적재되었습니다." << std::endl;
		std::cout << "도움말 : help" << std::endl;
		break;
	}
}
Order_Interpreter::~Order_Interpreter()
{
	delete this->person;
}
std::string Order_Interpreter::do_order(std::string order)
{
	this->order = Order_Token_Refiner(new Order_token).refining(order); //Order_Token_Refiner 임시객체 개념 사용
	if (compile::debug::order_tokenizer_debug) { //확인 결과 정상동작
		General_Function::show_order(this->order);
	}
	//매개변수로 받은 string 의 order를 잘라 Order_token 구조체를 초기화한다.
	try //매개변수 인자가 유효한지?
	{
		assert(this->order->token_count >= 0);
		if (this->order->token_count == arg::no_arg)
			throw err_exp::msg_no_order_input;
		else if (this->order->token_count == arg::too_much_args)
			throw err_exp::msg_too_much_args;
		else;
	}
	catch (std::string error_message)
	{
		if (error_message != err_exp::msg_no_order_input)
			std::cout << error_message << std::endl;
		delete this->order;
		this->order = nullptr; //예외처리로 끝나긴하지만 할당해준건 해제해주자.
		return err_exp::msg_no_special_thing;
	}

	arg::order_type op = operation_translate(this->order->content[arg::operation_position]);
	if (op == arg::order_type::add_)
		add(this->order);
	else if (op == arg::order_type::del_)
		del(this->order);
	else if (op == arg::order_type::update_)
		update(this->order);

	else if (
		op == arg::order_type::show_site_list_ ||
		op == arg::order_type::show_all_site_information_ ||
		op == arg::order_type::show_one_site_information_with_site_name_ ||
		op == arg::order_type::show_one_site_information_with_number_)
		show(op);

	else if (op == arg::order_type::save_) {
		Exporter exp(this->person);
		exp.save();
	}

	else if (/*추후 추가 order를 분석해서 Person 내의 모든 객체에 포함된 문자열을 찾아낸다.*/0) {}///

	else if (op == arg::order_type::help_)
		General_Function::help();

	else if (op == arg::order_type::exit_) {
		delete this->order;
		this->order = nullptr;
		return std::string("exit");
	}
	else
		std::cout << err_exp::msg_not_defined_operation << std::endl;

	delete this->order;
	this->order = nullptr;
	using namespace err_exp;
	return msg_no_special_thing; //에러는 아니지만.
}

void Order_Interpreter::add(Order_token* order)
{
	using namespace argument::instruction::add;
	if (order->type == add_form_use)
	{	//order가 완전하지 않을 시엔 Form 입력받기 필요
		if (Order_Form_Filler(this->person).add_form_filler(order) == false)
			return;
	}
	this->person->add(order);
}

void Order_Interpreter::del(Order_token* order)
{
	using namespace argument::instruction::del;
	if (order->type == delete_form_use)
	{	//order가 완전하지 않을 시엔 Form 입력받기 필요
		if (Order_Form_Filler(this->person).del_form_filler(order) == false)
			return;
	}
	this->person->del(order);
}

void Order_Interpreter::update(Order_token* order)
{
	using namespace argument::instruction::update;
	if (order->type == modify_form_use)
	{	//order가 완전하지 않을 시엔 Form 입력받기 필요
		if (Order_Form_Filler(this->person).update_form_filler(order) == false)
			return;
	}
	this->person->update(order);
}
void Order_Interpreter::show(int what_type_of_showing)
{	//각 if~else if 문의 순서를 변경할 때는 의미가 달라질 수 있으므로 주의.
	if (this->person->get_site_count() == 0)
		std::cout << err_exp::msg_person_hasnt_site << std::endl;

	switch (what_type_of_showing)
	{
	case arg::order_type::show_site_list_:// "ls"
		this->person->show_site_name_list();
		break;
	case arg::order_type::show_all_site_information_:// "ll"
		this->person->show_all_sites_information();
		break;
	case arg::order_type::show_one_site_information_with_site_name_:// "google"
		show_site_in_site_name(this->order);
		break;
	case arg::order_type::show_one_site_information_with_number_: // "12"
		show_site_in_number(this->order);
		break;
	default:
		std::cout << err_exp::msg_unsupport_order_form << std::endl;
		assert(0);
	}
}
void Order_Interpreter::show_site_in_number(Order_token* order)//숫자로 사이트 찾아주기
{	//"12" 처럼 사이트 번호만으로 정보를 찾는다.
	try { //token 수가 1개가 아니면 함수 종료.
		if (order->token_count != 1)
			throw err_exp::msg_unsupport_order_form;
	}
	catch (std::string error_message) {
		std::cout << error_message << std::endl;
		return;
	}
	int number = General_Function::string_to_integer(order->tokens[arg::operation_position]);
	//order의 첫번째 토큰을 숫자로 바꾼다. "12" -> 12
	if (number == 0) { //0번 사이트는 없으나, 사이트 목록을 출력하는 것으로 대신한다.
		this->person->show_site_name_list();
	}
	else if ((1 <= number) && (number <= this->person->get_site_count()))
	{
		Site * temp_site = this->person->find_site_with_site_number(number);
		this->person->show_one_site_information(temp_site, number);
	}
	else {
		std::cout << err_exp::msg_no_existing_site_number << std::endl;
	}
	return;
}

void Order_Interpreter::show_site_in_site_name(Order_token * order)
{	//"google" 처럼 사이트 이름만으로 정보를 찾는다.
	try { //token 수가 1개가 아니면 함수 종료.
		if (order->token_count != 1)
			throw err_exp::msg_unsupport_order_form;
	}
	catch (std::string error_message) {
		std::cout << error_message << std::endl;
		return;
	}
	Site * temp_site = this->person->find_site_with_site_name(this->order->content[arg::operation_position]);
	try {
		if (temp_site == nullptr)
			throw err_exp::msg_no_existing_site_name;
	}
	catch (std::string error_message) {
		std::cout << error_message << std::endl;
		return;
	}
	int site_number = this->person->get_site_number_with_site_name(temp_site->get_site_name());
	this->person->show_one_site_information(temp_site, site_number);
}

arg::order_type Order_Interpreter::operation_translate(std::string query_op)
{
	arg::order_type interpreted_op;
	if (query_op == "exit"
		|| query_op == "-1")
		interpreted_op = arg::order_type::exit_;

	else if (query_op == "show"
		|| query_op == "ls")
		interpreted_op = arg::order_type::show_site_list_;

	else if (query_op == "all"
		|| query_op == "ll")
		interpreted_op = arg::order_type::show_all_site_information_;

	else if (query_op == "add"
		|| query_op == "+")
		interpreted_op = arg::order_type::add_;

	else if (query_op == "del"
		|| query_op == "delete"
		|| query_op == "remove"
		|| query_op == "rm"
		|| query_op == "-")
		interpreted_op = arg::order_type::del_;

	else if (query_op == "update"
		|| query_op == "new"
		|| query_op == "udt")
		interpreted_op = arg::order_type::update_;

	else if (query_op == "save"
		|| query_op == "sv"
		|| query_op == "store")
		interpreted_op = arg::order_type::save_;

	else if (query_op == "help")
		interpreted_op = arg::order_type::help_;

	else if (this->person->find_site_with_site_name(query_op) != nullptr) //사이트 이름 입력
		interpreted_op = arg::order_type::show_one_site_information_with_site_name_;

	else if (General_Function::is_natural_number(query_op) == true) //사이트 번호 입력
		interpreted_op = arg::order_type::show_one_site_information_with_number_;

	else
		interpreted_op = arg::order_type::no_operation_input_;

	return interpreted_op;
}
