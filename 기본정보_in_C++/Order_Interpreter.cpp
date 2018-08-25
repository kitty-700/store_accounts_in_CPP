#include "Order_Interpreter.h"

namespace arg = option::argument;
namespace err_exp = option::error_expression;
bool Order_Interpreter::init_person(std::string file_name)
{
	Importer importer(file_name);
	Person * imported_person = importer.return_person();
	bool is_success = change_person(imported_person);
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
Order_Interpreter::Order_Interpreter() : person(nullptr)
{	//�翬�� �Ҹ�����, �� ó���� ������ �о�;� ���α׷��� ������ �� �ִ�.
	std::string load_file_name = compile::default_load_file_name; //���� ó���� �⺻���� ������ ���� �̸����� ���縦 �õ��Ѵ�.
	while (1)
	{
		if (init_person(load_file_name) == false)
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
std::string Order_Interpreter::excute_order(std::string order)///�ڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡ�
{
	Order::set( Order_Token_Refiner(new Order_token).refining(order)); //Order_Token_Refiner �ӽð�ü ���� ���
	if (compile::debug::order_tokenizer_debug) { //Ȯ�� ��� ������
		General_Function::show_order(Order::get());
	}
	//�Ű������� ���� string �� order�� �߶� Order_token ����ü�� �ʱ�ȭ�Ѵ�.
	try //�Ű����� ���ڰ� ��ȿ����?
	{
		assert(Order::get_token_count() >= 0);
		if (Order::get_token_count() == arg::no_arg)
			throw err_exp::msg_no_order_input;
		else if (Order::get_token_count() == arg::too_much_args)
			throw err_exp::msg_too_much_args;
		else;
	}
	catch (std::string error_message)
	{
		if (error_message != err_exp::msg_no_order_input)
			std::cout << error_message << std::endl;
		Order::clear();
		return err_exp::msg_no_special_thing;
	}

	arg::order_type op = operation_translate(Order::get()->content[arg::operation_position]);
	if (op == arg::order_type::clear_screen_)
		system("cls");
	else if (op == arg::order_type::add_)
		add();
	else if (op == arg::order_type::del_)
		del();
	else if (op == arg::order_type::update_)
		update();
	else if (op == arg::order_type::load_)
		load();
	else if (op == arg::order_type::reload_)
		init_person(this->now_loaded_file_name);

	else if (
		op == arg::order_type::show_site_list_ ||
		op == arg::order_type::show_all_site_information_ ||
		op == arg::order_type::show_one_site_information_with_site_name_ ||
		op == arg::order_type::show_one_site_information_with_number_)
		show(op);

	else if (op == arg::order_type::save_) {
		Exporter exp(this->person, this->now_loaded_file_name);
		exp.save();
	}

	else if (op == arg::order_type::help_)
		General_Function::help();

	else if (op == arg::order_type::exit_) {
		Order::clear();
		return std::string("exit");
	}
	else if (/*���� �߰� order�� �м��ؼ� Person ���� ��� ��ü�� ���Ե� ���ڿ��� ã�Ƴ���.*/0) {}///

	else
		std::cout << err_exp::msg_not_defined_operation << std::endl;
	Order::clear();
	using namespace err_exp;
	return msg_no_special_thing; //������ �ƴ����� error_expression�� �־��. ���߿� expression�̶�� namespace ������ �и��� ��.
}

void Order_Interpreter::add()
{
	Status::set_is_form_filling_successful(true);
	using namespace arg::instruction::add;
	if (Order::get_type() == add_form_use)
	{	//order�� �������� ���� �ÿ� Form �Է¹ޱ� �ʿ�
		Order_Form_Filler(this->person).add_form_filler();
	}
	if (Status::get_is_form_filling_successful() == true)
		this->person->add(Order::get());
}

void Order_Interpreter::load()
{
	Status::set_is_form_filling_successful(true);
	using namespace arg::instruction::load;
	if (Order::get_type() == load_in_default_file_name)
	{	//order�� �������� ���� �ÿ� Form �Է¹ޱ� �ʿ�
		Order_Form_Filler(this->person).load_form_filler();
	}
	if (Status::get_is_form_filling_successful() == true)
	{
		init_person(Order::get_content(file_name_position));
	}
}

void Order_Interpreter::del()
{
	Status::set_is_form_filling_successful(true);
	using namespace argument::instruction::del;
	if (Order::get_type() == delete_form_use)
	{	//order�� �������� ���� �ÿ� Form �Է¹ޱ� �ʿ�
		Order_Form_Filler(this->person).del_form_filler();
	}
	if (Status::get_is_form_filling_successful() == true)
		this->person->del(Order::get());
}

void Order_Interpreter::update()
{
	Status::set_is_form_filling_successful(true);
	using namespace argument::instruction::update;
	if (Order::get_type() == modify_form_use)
	{	//order�� �������� ���� �ÿ� Form �Է¹ޱ� �ʿ�
		Order_Form_Filler(this->person).update_form_filler();
	}
	if (Status::get_is_form_filling_successful() == true)
		this->person->update(Order::get());
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

void Order_Interpreter::show_site_in_number()//���ڷ� ����Ʈ ã���ֱ�
{	//"12" ó�� ����Ʈ ��ȣ������ ������ ã�´�.
	try { //token ���� 1���� �ƴϸ� �Լ� ����.
		if (Order::get_type() != argument::instruction::show::no_additional_arguments)
			throw err_exp::msg_unsupport_order_form;
	}
	catch (std::string error_message) {
		std::cout << error_message << std::endl;
		return;
	}
	int number = General_Function::string_to_integer(Order::get_content(arg::operation_position));
	//order�� ù��° ��ū�� ���ڷ� �ٲ۴�. "12" -> 12
	if (number == 0) { //0�� ����Ʈ�� ������, ����Ʈ ����� ����ϴ� ������ ����Ѵ�.
		this->person->show_site_name_list();
	}
	else if ((1 <= number) && (number <= this->person->get_site_count()))
	{
		Site * temp_site = this->person->find_Site(number);
		this->person->show_one_site_information(temp_site, number);
	}
	else {
		std::cout << err_exp::msg_no_existing_site_number << std::endl;
	}
	return;
}

void Order_Interpreter::show_site_in_site_name()
{	//"google" ó�� ����Ʈ �̸������� ������ ã�´�.
	try { //token ���� 1���� �ƴϸ� �Լ� ����.
		if (Order::get_type() != argument::instruction::show::no_additional_arguments)
			throw err_exp::msg_unsupport_order_form;
	}
	catch (std::string error_message) {
		std::cout << error_message << std::endl;
		return;
	}
	Site * temp_site = this->person->find_Site(Order::get_content(arg::operation_position));
	try {
		if (temp_site == nullptr)
			throw err_exp::msg_no_existing_site_name;
	}
	catch (std::string error_message) {
		std::cout << error_message << std::endl;
		return;
	}
	int site_number = this->person->find_Site_number(temp_site->get_site_name());
	this->person->show_one_site_information(temp_site, site_number);
}

bool Order_Interpreter::change_person(Person * person_to_change)
{
	if (person_to_change->get_is_alive() == false)
	{
		delete person_to_change;
		return false;
	}
	else
	{
		if (this->person != nullptr)
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
	arg::order_type interpreted_op = Natural_language::operation_translate(query_op);
	if (interpreted_op == arg::order_type::not_translate_but_should_calculated_)
	{
		if (this->person->find_Site(query_op) != nullptr) //����Ʈ �̸� �Է�
			interpreted_op = arg::order_type::show_one_site_information_with_site_name_;

		else if (General_Function::is_natural_number(query_op) == true) //����Ʈ ��ȣ �Է�
			interpreted_op = arg::order_type::show_one_site_information_with_number_;

		else
			interpreted_op = arg::order_type::no_operation_input_;
	}
	return interpreted_op;
}
