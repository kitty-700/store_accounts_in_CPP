#include "Order_Form_Filler.h"
namespace err_exp = error_expression;
Order_Form_Filler::Order_Form_Filler(Person * person) : person(person) { }

//XXXX_form_filler() ���� false�� ��ȯ�� ���, ����� �� order ����� ������ �������� �ǹ��ϸ�, ���� �̿� ���� ����� �������� �ʴ´�.

bool Order_Form_Filler::add_form_filler(Order_token * order)
{	//"add" ��ɿ� ���� ����� �޴´�. 
	std::cout << "������ �߰��ϰ��� �ϴ� ����Ʈ�� ��ȣ�� �������ּ���." << std::endl;
	SET_CONSOLE_COLOR(console_color::zero_selection);
	this->person->print_site_number(0);
	std::cout << "����Ʈ �߰�" << std::endl;
	SET_CONSOLE_COLOR_DEFAULT;
	this->person->show_site_name_list();

	std::cout << "���� > ";
	std::getline(std::cin, this->selection, '\n');
	this->selection_1 = General_Function::string_to_integer(this->selection);

	try {
		if (this->selection_1 == argument::zero_selection)
			add_new_site(order);
		else if (this->selection_1 == error_expression::string_to_be_int_wasnt_entered) {
			throw error_expression::msg_form_filling_cancel;
		}
		else {
			if (add_new_account(order) == false)
				return false;
		}
	}
	catch (std::string error_message) { //������ catch��
		std::cout << error_message << std::endl;
		return false;
	}
	return true;
}

void Order_Form_Filler::add_new_site(Order_token * order)
{
	using namespace std;
	std::string new_site_name;
	std::cout << "�� ����Ʈ �̸� > ";
	std::getline(std::cin, new_site_name, '\n');

	using namespace argument::instruction::add;
	order->tokens[new_site_name_position] = new_site_name;
	order->type = add_site_only;
}

bool Order_Form_Filler::add_new_account(Order_token * order)
{
	Site * temp_site = this->person->find_site_with_site_number(this->selection_1);
	try {
		if (temp_site == nullptr)
			throw err_exp::msg_no_existing_site_number;
	}
	catch (std::string error_message) {
		std::cout << error_message << std::endl;
		return false;
	}
	temp_site->show_account_information();

	std::string str;

	using namespace argument::instruction::add;
	order->tokens[new_site_name_position] = temp_site->get_site_name();
	std::cout << "�� ������ ID > ";
	std::getline(std::cin, str, '\n');
	order->tokens[new_id_position] = str;
	std::cout << "�� ������ PW > ";
	std::getline(std::cin, str, '\n');
	order->tokens[new_pw_position] = str;
	std::cout << "�� ������ ���� �޸� > ";
	std::getline(std::cin, str, '\n');
	order->tokens[new_memo_position] = str;
	order->token_count = add_account_with_memo;
	return true;
}

bool Order_Form_Filler::del_form_filler(Order_token * order)
{	//"del" ��ɿ� ���� ����� �޴´�.
	std::cout << "����Ʈ ��ü Ȥ�� ������ �����ϰ��� �ϴ� ����Ʈ�� ��ȣ�� �������ּ���." << std::endl;
	this->person->show_site_name_list();
	std::cout << "����Ʈ ���� > ";
	SET_CONSOLE_COLOR(console_color::order_color);
	std::getline(std::cin, this->selection, '\n');
	this->selection_1 = General_Function::string_to_integer(this->selection);
	SET_CONSOLE_COLOR_DEFAULT;
	Site * temp_site;
	try {
		if (this->selection_1 <= 0)
			throw err_exp::msg_no_existing_site_number;
		temp_site = this->person->find_site_with_site_number(this->selection_1);
		if (temp_site == nullptr)
			throw err_exp::msg_no_existing_site_number;
	}
	catch (std::string error_message) { //������ catch��
		std::cout << error_message << std::endl;
		return false;
	}

	std::cout << "����Ʈ ��ü�� ������ ��� 0���� �����ϰ�, \n����Ʈ ���� ������ ������ ��� ������ ��ȣ�� �������ּ���." << std::endl;
	SET_CONSOLE_COLOR(console_color::zero_selection);
	this->person->print_site_number(0);
	SET_CONSOLE_COLOR(console_color::site_name_color);
	std::cout << temp_site->get_site_name();
	SET_CONSOLE_COLOR(console_color::zero_selection);
	std::cout << " ����Ʈ ����" << std::endl;
	SET_CONSOLE_COLOR_DEFAULT;
	temp_site->show_account_information();	
	std::cout << "���� > ";
	SET_CONSOLE_COLOR(console_color::order_color);	
	std::getline(std::cin, this->selection, '\n');
	this->selection_2 = General_Function::string_to_integer(this->selection);
	SET_CONSOLE_COLOR_DEFAULT;

	if (this->selection_2 == argument::zero_selection) {
		del_site(order);
	}
	else {
		del_account(order);
	}
	return true;
}

bool Order_Form_Filler::del_site(Order_token * order)
{
	using namespace argument::instruction::del;
	Site * temp_site = this->person->find_site_with_site_number(this->selection_1);
	order->tokens[site_name_position] = temp_site->get_site_name();
	order->type = delete_site;
	return true;
}

bool Order_Form_Filler::del_account(Order_token * order)
{
	using namespace argument::instruction::del;
	Site * temp_site = this->person->find_site_with_site_number(this->selection_1);
	order->tokens[site_name_position] = temp_site->get_site_name();
	Account * temp_account = temp_site->find_account_with_account_number(this->selection_2);
	order->tokens[id_position] = temp_account->get_attribute("ID");
	order->type = delete_account;
	return true;
}

bool Order_Form_Filler::update_form_filler(Order_token * order)
{	//"update" ��ɿ� ���� ����� �޴´�.
	std::cout << "����Ʈ �̸� Ȥ�� ���� �Ӽ��� �����ϰ��� �ϴ� ����Ʈ�� ��ȣ�� �������ּ���." << std::endl;
	this->person->show_site_name_list();
	std::cout << "����Ʈ ���� > ";
	SET_CONSOLE_COLOR(console_color::order_color);	
	std::getline(std::cin, this->selection, '\n');
	this->selection_1 = General_Function::string_to_integer(this->selection);
	SET_CONSOLE_COLOR_DEFAULT;

	Site * temp_site;
	try {
		if (this->selection_1 <= 0)
			throw err_exp::msg_no_existing_site_number;
		temp_site = this->person->find_site_with_site_number(this->selection_1);
		if (temp_site == nullptr)
			throw err_exp::msg_no_existing_site_number;
	}
	catch (std::string error_message) {
		std::cout << error_message << std::endl;
		return false;
	}

	std::cout << "����Ʈ �̸��� ������ ��� 0���� �����ϰ�, \n����Ʈ �� ������ �Ӽ��� ������ ��� ������ ��ȣ�� �������ּ���." << std::endl;
	SET_CONSOLE_COLOR(console_color::zero_selection);
	this->person->print_site_number(0);
	SET_CONSOLE_COLOR(console_color::site_name_color);
	std::cout << temp_site->get_site_name();
	SET_CONSOLE_COLOR(console_color::zero_selection);
	std::cout << " ����Ʈ �̸� ����" << std::endl;
	SET_CONSOLE_COLOR_DEFAULT;
	temp_site->show_account_information();
	std::cout << "���� ���� > ";
	SET_CONSOLE_COLOR(console_color::order_color);	
	std::getline(std::cin, this->selection, '\n');
	this->selection_2 = General_Function::string_to_integer(this->selection);
	SET_CONSOLE_COLOR_DEFAULT;

	if (this->selection_2 == argument::zero_selection) {
		return update_site_name(order);
	}
	else {
		return update_account_attribute(order);
	}
}

bool Order_Form_Filler::update_site_name(Order_token * order)
{
	Site * temp_site = this->person->find_site_with_site_number(this->selection_1);

	namespace update = argument::instruction::update;
	order->tokens[update::site_name_position] = temp_site->get_site_name();
	std::string new_site_name;
	std::cout << "������ ����Ʈ �̸� ( ";
	SET_CONSOLE_COLOR(console_color::site_name_color);
	std::cout << temp_site->get_site_name();
	SET_CONSOLE_COLOR_DEFAULT; 
	std::cout << " ->  ? )" << std::endl;
	std::cout << "�� > ";
	SET_CONSOLE_COLOR(console_color::order_color);
	std::getline(std::cin, new_site_name, '\n');
	SET_CONSOLE_COLOR_DEFAULT;
	order->tokens[update::new_site_name_position] = new_site_name;
	order->type = update::modify_site_name;
	return true;
}

bool Order_Form_Filler::update_account_attribute(Order_token * order)
{
	Site * temp_site = this->person->find_site_with_site_number(this->selection_1);
	Account * temp_account = temp_site->find_account_with_account_number(this->selection_2);

	SET_CONSOLE_COLOR(console_color::account_attribute_color);
	std::cout << "[1] ID : " << temp_account->get_attribute("ID") << std::endl;
	std::cout << "[2] PW : " << temp_account->get_attribute("PW") << std::endl;
	std::cout << "[3] memo : " << temp_account->get_attribute("Memo") << std::endl;
	SET_CONSOLE_COLOR_DEFAULT;
	std::cout << "�Ӽ� ���� > ";
	SET_CONSOLE_COLOR(console_color::order_color);	
	std::getline(std::cin, this->selection, '\n');
	this->selection_3 = General_Function::string_to_integer(this->selection);
	SET_CONSOLE_COLOR_DEFAULT;

	try {
		if (this->selection_3 < 1 || 3 < this->selection_3)
			throw err_exp::msg_undefined_account_attribute;
	}
	catch (std::string error_message) { //������ catch��
		std::cout << error_message << std::endl;;
		return false;
	}
	namespace update = argument::instruction::update;
	order->tokens[update::site_name_position] = temp_site->get_site_name();
	order->tokens[update::id_position] = temp_account->get_attribute("ID");
	switch (this->selection_3)
	{
	case 1:
		order->tokens[update::attribute_select_position] = "ID";
		break;
	case 2:
		order->tokens[update::attribute_select_position] = "PW";
		break;
	case 3:
		order->tokens[update::attribute_select_position] = "memo";
		break;

	}
	std::string new_attribute_value;
	std::cout << "������ ���� > ";
	std::getline(std::cin, new_attribute_value, '\n');
	order->tokens[update::new_attribute_value_position] = new_attribute_value;
	order->type = update::modify_account_attribute;
	return true;
}
