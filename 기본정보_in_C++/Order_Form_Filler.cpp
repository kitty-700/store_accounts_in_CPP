#include "Order_Form_Filler.h"
namespace err_exp = error_expression;
Order_Form_Filler::Order_Form_Filler(Person * person) : person(person) { }

//XXXX_form_filler() 에서 false가 반환될 경우, 제대로 된 order 양식을 만들지 못했음을 의미하며, 따라서 이에 대해 명령을 수행하지 않는다.

bool Order_Form_Filler::add_form_filler(Order_token * order)
{	//"add" 명령에 대한 양식을 받는다. 
	std::cout << "계정을 추가하고자 하는 사이트의 번호를 선택해주세요." << std::endl;
	SET_CONSOLE_COLOR(console_color::zero_selection);
	this->person->print_site_number(0);
	std::cout << "사이트 추가" << std::endl;
	SET_CONSOLE_COLOR_DEFAULT;
	this->person->show_site_name_list();

	std::cout << "선택 > ";
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
	catch (std::string error_message) { //보통의 catch문
		std::cout << error_message << std::endl;
		return false;
	}
	return true;
}

void Order_Form_Filler::add_new_site(Order_token * order)
{
	using namespace std;
	std::string new_site_name;
	std::cout << "새 사이트 이름 > ";
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
	std::cout << "새 계정의 ID > ";
	std::getline(std::cin, str, '\n');
	order->tokens[new_id_position] = str;
	std::cout << "새 계정의 PW > ";
	std::getline(std::cin, str, '\n');
	order->tokens[new_pw_position] = str;
	std::cout << "새 계정에 대한 메모 > ";
	std::getline(std::cin, str, '\n');
	order->tokens[new_memo_position] = str;
	order->token_count = add_account_with_memo;
	return true;
}

bool Order_Form_Filler::del_form_filler(Order_token * order)
{	//"del" 명령에 대한 양식을 받는다.
	std::cout << "사이트 자체 혹은 계정을 삭제하고자 하는 사이트의 번호를 선택해주세요." << std::endl;
	this->person->show_site_name_list();
	std::cout << "사이트 선택 > ";
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
	catch (std::string error_message) { //보통의 catch문
		std::cout << error_message << std::endl;
		return false;
	}

	std::cout << "사이트 자체를 삭제할 경우 0번을 선택하고, \n사이트 내의 계정을 삭제할 경우 계정의 번호를 선택해주세요." << std::endl;
	SET_CONSOLE_COLOR(console_color::zero_selection);
	this->person->print_site_number(0);
	SET_CONSOLE_COLOR(console_color::site_name_color);
	std::cout << temp_site->get_site_name();
	SET_CONSOLE_COLOR(console_color::zero_selection);
	std::cout << " 사이트 삭제" << std::endl;
	SET_CONSOLE_COLOR_DEFAULT;
	temp_site->show_account_information();	
	std::cout << "선택 > ";
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
{	//"update" 명령에 대한 양식을 받는다.
	std::cout << "사이트 이름 혹은 계정 속성을 변경하고자 하는 사이트의 번호를 선택해주세요." << std::endl;
	this->person->show_site_name_list();
	std::cout << "사이트 선택 > ";
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

	std::cout << "사이트 이름을 변경할 경우 0번을 선택하고, \n사이트 내 계정의 속성을 변경할 경우 계정의 번호를 선택해주세요." << std::endl;
	SET_CONSOLE_COLOR(console_color::zero_selection);
	this->person->print_site_number(0);
	SET_CONSOLE_COLOR(console_color::site_name_color);
	std::cout << temp_site->get_site_name();
	SET_CONSOLE_COLOR(console_color::zero_selection);
	std::cout << " 사이트 이름 변경" << std::endl;
	SET_CONSOLE_COLOR_DEFAULT;
	temp_site->show_account_information();
	std::cout << "계정 선택 > ";
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
	std::cout << "변경할 사이트 이름 ( ";
	SET_CONSOLE_COLOR(console_color::site_name_color);
	std::cout << temp_site->get_site_name();
	SET_CONSOLE_COLOR_DEFAULT; 
	std::cout << " ->  ? )" << std::endl;
	std::cout << "└ > ";
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
	std::cout << "속성 선택 > ";
	SET_CONSOLE_COLOR(console_color::order_color);	
	std::getline(std::cin, this->selection, '\n');
	this->selection_3 = General_Function::string_to_integer(this->selection);
	SET_CONSOLE_COLOR_DEFAULT;

	try {
		if (this->selection_3 < 1 || 3 < this->selection_3)
			throw err_exp::msg_undefined_account_attribute;
	}
	catch (std::string error_message) { //보통의 catch문
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
	std::cout << "변경할 내용 > ";
	std::getline(std::cin, new_attribute_value, '\n');
	order->tokens[update::new_attribute_value_position] = new_attribute_value;
	order->type = update::modify_account_attribute;
	return true;
}
