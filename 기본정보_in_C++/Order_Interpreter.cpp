#include "Order_Interpreter.h"

namespace arg = option::argument;
namespace err_exp = option::error_expression;
bool Order_Interpreter::init_person(std::string file_name, const bool using_in_first_time)
{
	Importer importer(file_name);
	Person * imported_person = importer.return_person();
	bool is_success = change_person(imported_person, using_in_first_time);
	if (is_success == true)
		init_person_success_action(file_name);
	return is_success;
}
void Order_Interpreter::init_person_success_action(std::string loaded_file_name)
{
	General_Function::print_thin_line();
	Status::set_is_person_loaded(true);
	this->now_loaded_file_name = loaded_file_name;
	std::cout << this->person->get_site_count() << " ���� ����Ʈ ������ ����Ǿ����ϴ�." << std::endl;
	std::cout << "���� : help" << std::endl;
}
Order_Interpreter::Order_Interpreter()
{	//�翬�� �Ҹ�����, �� ó���� ������ �о�;� ���α׷��� ������ �� �ִ�.
	std::string load_file_name = compile::default_load_file_name; //���� ó���� �⺻���� ������ ���� �̸����� ���縦 �õ��Ѵ�.
	while (1)
	{
		if (init_person(load_file_name, true) == false)
		{
			std::string reload_file_name;
			std::cout << "�� ���� �̸��� �Է����ֽðڽ��ϱ�? ";
			std::cout << "( ���� �ҷ������� ���� �̸� : " << load_file_name << " )" << std::endl;
			std::cout << "�� ���� �̸� > ";
			std::cin >> reload_file_name;
			std::cin.ignore();
			load_file_name = reload_file_name;
			continue;
		}
		break;
	}
}
Order_Interpreter::~Order_Interpreter()
{
	delete this->person;
}
std::string Order_Interpreter::excute_order(std::string order)
{
	this->order = Order_Token_Refiner(new Order_token).refining(order); //Order_Token_Refiner �ӽð�ü ���� ���
	if (compile::debug::order_tokenizer_debug) { //Ȯ�� ��� ������
		General_Function::show_order(this->order);
	}
	//�Ű������� ���� string �� order�� �߶� Order_token ����ü�� �ʱ�ȭ�Ѵ�.
	try //�Ű����� ���ڰ� ��ȿ����?
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
		this->order = nullptr; //����ó���� ������������ �Ҵ����ذ� ����������.
		return err_exp::msg_no_special_thing;
	}

	arg::order_type op = operation_translate(this->order->content[arg::operation_position]);
	if (op == arg::order_type::clear_screen_)
		system("cls");
	else if (op == arg::order_type::add_)
		add(this->order);
	else if (op == arg::order_type::del_)
		del(this->order);
	else if (op == arg::order_type::update_)
		update(this->order);
	else if (op == arg::order_type::load_)
		load(this->order);
	else if (op == arg::order_type::reload_)
		init_person(this->now_loaded_file_name, false);

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

	else if (op == arg::order_type::help_)
		General_Function::help();

	else if (op == arg::order_type::exit_) {
		delete this->order;
		this->order = nullptr;
		return std::string("exit");
	}
	else if (/*���� �߰� order�� �м��ؼ� Person ���� ��� ��ü�� ���Ե� ���ڿ��� ã�Ƴ���.*/0) {}///

	else
		std::cout << err_exp::msg_not_defined_operation << std::endl;

	delete this->order;
	this->order = nullptr;
	using namespace err_exp;
	return msg_no_special_thing; //������ �ƴ�����.
}

void Order_Interpreter::add(Order_token* order)
{
	Status::set_is_form_filling_successful(true);
	using namespace arg::instruction::add;
	if (order->type == add_form_use)
	{	//order�� �������� ���� �ÿ� Form �Է¹ޱ� �ʿ�
		Order_Form_Filler(this->person, order).add_form_filler();
	}
	if (Status::get_is_form_filling_successful() == true)
		this->person->add(order);
}

void Order_Interpreter::load(Order_token * site_name)
{
	Status::set_is_form_filling_successful(true);
	using namespace arg::instruction::load;
	if (order->type == load_in_default_file_name)
	{	//order�� �������� ���� �ÿ� Form �Է¹ޱ� �ʿ�
		//
	}
	if (Status::get_is_form_filling_successful() == true)
		this->person->add(order);
}

void Order_Interpreter::del(Order_token* order)
{
	Status::set_is_form_filling_successful(true);
	using namespace argument::instruction::del;
	if (order->type == delete_form_use)
	{	//order�� �������� ���� �ÿ� Form �Է¹ޱ� �ʿ�
		Order_Form_Filler(this->person, order).del_form_filler();
	}
	if (Status::get_is_form_filling_successful() == true)
		this->person->del(order);
}

void Order_Interpreter::update(Order_token* order)
{
	Status::set_is_form_filling_successful(true);
	using namespace argument::instruction::update;
	if (order->type == modify_form_use)
	{	//order�� �������� ���� �ÿ� Form �Է¹ޱ� �ʿ�
		Order_Form_Filler(this->person, order).update_form_filler();
	}
	if (Status::get_is_form_filling_successful() == true)
		this->person->update(order);
}
void Order_Interpreter::show(int what_type_of_showing)
{	//�� if~else if ���� ������ ������ ���� �ǹ̰� �޶��� �� �����Ƿ� ����.
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
void Order_Interpreter::show_site_in_number(Order_token* order)//���ڷ� ����Ʈ ã���ֱ�
{	//"12" ó�� ����Ʈ ��ȣ������ ������ ã�´�.
	try { //token ���� 1���� �ƴϸ� �Լ� ����.
		if (order->token_count != 1)
			throw err_exp::msg_unsupport_order_form;
	}
	catch (std::string error_message) {
		std::cout << error_message << std::endl;
		return;
	}
	int number = General_Function::string_to_integer(order->tokens[arg::operation_position]);
	//order�� ù��° ��ū�� ���ڷ� �ٲ۴�. "12" -> 12
	if (number == 0) { //0�� ����Ʈ�� ������, ����Ʈ ����� ����ϴ� ������ ����Ѵ�.
		this->person->show_site_name_list();
	}
	else if ((1 <= number) && (number <= this->person->get_site_count()))
	{
		Site * temp_site = this->person->site_number_to_Site(number);
		this->person->show_one_site_information(temp_site, number);
	}
	else {
		std::cout << err_exp::msg_no_existing_site_number << std::endl;
	}
	return;
}

void Order_Interpreter::show_site_in_site_name(Order_token * order)
{	//"google" ó�� ����Ʈ �̸������� ������ ã�´�.
	try { //token ���� 1���� �ƴϸ� �Լ� ����.
		if (order->token_count != 1)
			throw err_exp::msg_unsupport_order_form;
	}
	catch (std::string error_message) {
		std::cout << error_message << std::endl;
		return;
	}
	Site * temp_site = this->person->site_name_to_Site(this->order->content[arg::operation_position]);
	try {
		if (temp_site == nullptr)
			throw err_exp::msg_no_existing_site_name;
	}
	catch (std::string error_message) {
		std::cout << error_message << std::endl;
		return;
	}
	int site_number = this->person->site_name_to_site_number(temp_site->get_site_name());
	this->person->show_one_site_information(temp_site, site_number);
}

bool Order_Interpreter::change_person(Person * person_to_change, const bool using_in_first_time)
{
	if (person_to_change->get_is_alive() == false)
	{
		delete person_to_change;
		return false;
	}
	else
	{
		if (using_in_first_time == false)
		{	//�� ó�� ����Ǵ°� �ƴ϶�� �۾� ���� ����Ǵ°��� �ǹ��ϹǷ� Ȯ�� ������ ��ģ��.
			if (General_Function::ask_do_or_not(error_expression::msg_job_reset_warning + " �����Ͻðڽ��ϱ�?") == true)
			{
				this->person = person_to_change;
				return true;
			}
			else
			{
				std::cout << "��ҵǾ����ϴ�." << std::endl;
				return false;
			}
		}
		else {
			this->person = person_to_change;
			return true;
		}
	}
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
		|| query_op == "ADD"
		|| query_op == "+")
		interpreted_op = arg::order_type::add_;

	else if (query_op == "del"
		|| query_op == "DELETE"
		|| query_op == "delete"
		|| query_op == "remove"
		|| query_op == "rm"
		|| query_op == "-")
		interpreted_op = arg::order_type::del_;

	else if (query_op == "cls"
		|| query_op == "clear")
		interpreted_op = arg::order_type::clear_screen_;

	else if (query_op == "update"
		|| query_op == "UPDATE"
		|| query_op == "Update"
		|| query_op == "udt")
		interpreted_op = arg::order_type::update_;

	else if (query_op == "save"
		|| query_op == "SAVE"
		|| query_op == "Save"
		|| query_op == "store")
		interpreted_op = arg::order_type::save_;
	
	else if (query_op == "load"
		|| query_op == "Load"
		|| query_op == "LOAD")
		interpreted_op = arg::order_type::load_;

	else if (query_op == "reload"
		|| query_op == "Reload")
		interpreted_op = arg::order_type::reload_;

	else if (query_op == "help")
		interpreted_op = arg::order_type::help_;

	else if (this->person->site_name_to_Site(query_op) != nullptr) //����Ʈ �̸� �Է�
		interpreted_op = arg::order_type::show_one_site_information_with_site_name_;

	else if (General_Function::is_natural_number(query_op) == true) //����Ʈ ��ȣ �Է�
		interpreted_op = arg::order_type::show_one_site_information_with_number_;

	else
		interpreted_op = arg::order_type::no_operation_input_;

	return interpreted_op;
}
