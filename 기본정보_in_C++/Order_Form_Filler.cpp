#include "Order_Form_Filler.h"
namespace err_exp = error_expression;
Order_Form_Filler::Order_Form_Filler(Person * person) : person(person) { }
/* 입력 양식

//첫번째 페이지 ()
{
	//메뉴출력
	{
		
	}
	//메뉴 중에서 선택
	{

	}
	//선택에 대한 예외처리
	{

	}
}
*/
void Order_Form_Filler::add_form_filler(Order_token * order)
{	//"add" 명령에 대한 양식을 받는다. 
	//첫번째 페이지 (사이트 선택)
	{	
		//메뉴 출력
		{
			std::cout << "계정을 추가하고자 하는 사이트의 번호를 선택해주세요." << std::endl;
			zero_selection_explain("사이트 추가");
			this->person->show_site_name_list();
		}
		//메뉴 중에서 선택
		{
			std::cout << "> ";
			General_Function::order_color_input(this->selection);
			this->selection_1 = General_Function::string_to_integer(this->selection);
		}
		//선택에 대한 예외처리
		{
			try {
				if (this->selection_1 == error_expression::string_to_be_int_wasnt_entered)
					throw error_expression::msg_form_filling_cancel;
				else if (this->selection_1 == argument::zero_selection)
					add_new_site(order);
				else
					add_new_account(order);
			}
			catch (std::string error_message) { //보통의 catch문
				Status::set_is_form_filling_successful(false);
				std::cout << error_message << std::endl;
				return;
			}
		}
	}
	return;
}

void Order_Form_Filler::add_new_site(Order_token * order)
{
	using namespace std;
	std::string new_site_name;
	std::cout << "새 사이트 이름 > ";
	General_Function::order_color_input(new_site_name);

	using namespace argument::instruction::add;
	order->tokens[new_site_name_position] = new_site_name;
	order->type = add_site_only;
}

void Order_Form_Filler::add_new_account(Order_token * order)
{	//사이트 번호를 잘못 입력하면 실패
	Site * temp_site = this->person->site_number_to_Site(this->selection_1);
	try {
		if (temp_site == nullptr)
			throw err_exp::msg_no_existing_site_number;
	}
	catch (std::string error_message) {
		Status::set_is_form_filling_successful(false);
		std::cout << error_message << std::endl;
		return;
	}
	temp_site->show_account_information();

	std::string temp_str;

	using namespace argument::instruction::add;

	order->tokens[new_site_name_position] = temp_site->get_site_name();
	std::cout << "새 계정의 ID > ";
	General_Function::order_color_input(temp_str);
	order->tokens[new_id_position] = temp_str;

	std::cout << "새 계정의 PW > ";
	General_Function::order_color_input(temp_str);
	order->tokens[new_pw_position] = temp_str;

	std::cout << "새 계정에 대한 메모 > ";
	General_Function::order_color_input(temp_str);
	order->tokens[new_memo_position] = temp_str;

	order->token_count = add_account_with_memo;
	return;
}

void Order_Form_Filler::del_form_filler(Order_token * order)
{	//"del" 명령에 대한 양식을 받는다.
	if (exception_no_sites() == true)
		return;
	Site * temp_site;
	//첫번째 페이지 (사이트 선택)
	{
		//메뉴 출력
		{
			std::cout << "사이트 자체 혹은 계정을 삭제하고자 하는 사이트의 번호를 선택해주세요." << std::endl;
			zero_selection_explain("동작 취소");
			this->person->show_site_name_list();
		}
		//메뉴 중에서 선택
		{
			std::cout << "사이트 선택 > ";
			General_Function::order_color_input(this->selection);
			this->selection_1 = General_Function::string_to_integer(this->selection);
		}
		//선택에 대한 예외처리
		{
			try {
				if (this->selection_1 == error_expression::string_to_be_int_wasnt_entered)
					throw error_expression::msg_form_filling_cancel;
				if (this->selection_1 <= 0) //번호가 0 이하인 사이트는 없으므로.
					throw err_exp::msg_no_existing_site_number;
				temp_site = this->person->site_number_to_Site(this->selection_1);
				if (temp_site == nullptr)
					throw err_exp::msg_no_existing_site_number;
			}
			catch (std::string error_message) { //보통의 catch문
				Status::set_is_form_filling_successful(false);
				std::cout << error_message << std::endl;
				return;
			}
		}
	}
	//두번째 페이지 (사이트 자체(0) 혹은 계정 선택)
	{
		//메뉴 출력2
		{
			std::cout << "사이트 자체를 삭제할 경우 0번을 선택하고, \n사이트 내의 계정을 삭제할 경우 계정의 번호를 선택해주세요." << std::endl;
			zero_selection_explain("사이트 삭제", temp_site);
			temp_site->show_account_information();
		}
		//메뉴 중에서 선택
		{
			std::cout << "선택 > ";
			General_Function::order_color_input(this->selection);
			this->selection_2 = General_Function::string_to_integer(this->selection);
		}
		//선택에 대한 예외처리
		{
			try {
				if (this->selection_2 == error_expression::string_to_be_int_wasnt_entered)
					throw error_expression::msg_form_filling_cancel;
				if (this->selection_2 < 0 || temp_site->get_account_count() < this->selection_2)
					throw error_expression::msg_no_existing_site_number;
			}
			catch (std::string error_message) {
				Status::set_is_form_filling_successful(false);
				std::cout << error_message << std::endl;
				return;
			}
		}
		//정상 진행
		{
			if (this->selection_2 == argument::zero_selection)
				del_site(order);
			else if (this->selection_2)
				del_account(order);
		}
	}
	return;
}

void Order_Form_Filler::del_site(Order_token * order)
{
	using namespace argument::instruction::del;
	Site * temp_site = this->person->site_number_to_Site(this->selection_1);
	order->tokens[site_name_position] = temp_site->get_site_name();
	order->type = delete_site;
	return;
}

void Order_Form_Filler::del_account(Order_token * order)
{
	using namespace argument::instruction::del;
	Site * temp_site = this->person->site_number_to_Site(this->selection_1);
	order->tokens[site_name_position] = temp_site->get_site_name();
	Account * temp_account = temp_site->find_account_with_account_number(this->selection_2);
	order->tokens[id_position] = temp_account->get_attribute("ID");
	order->type = delete_account;
	return;
}

void Order_Form_Filler::update_form_filler(Order_token * order)
{	//"update" 명령에 대한 양식을 받는다.
	if (exception_no_sites() == true)
		return;
	Site * temp_site;
	//첫번째 페이지 (사이트 선택)
	{	
		//메뉴 출력
		{
			std::cout << "사이트 이름 혹은 계정 속성을 변경하고자 하는 사이트의 번호를 선택해주세요." << std::endl;
			zero_selection_explain("동작 취소");
			this->person->show_site_name_list();
		}
		//메뉴 중에서 선택
		{
			std::cout << "사이트 선택 > ";
			General_Function::order_color_input(this->selection);
			this->selection_1 = General_Function::string_to_integer(this->selection);
		}
		//선택에 대한 예외처리
		{
			try {
				if (this->selection_1 <= 0)
					throw err_exp::msg_no_existing_site_number;
				temp_site = this->person->site_number_to_Site(this->selection_1);
				if (temp_site == nullptr)
					throw err_exp::msg_no_existing_site_number;
			}
			catch (std::string error_message) {
				Status::set_is_form_filling_successful(false);
				std::cout << error_message << std::endl;
				return;
			}
		}
	}

	//두번째 페이지 (사이트 자체(0) 혹은 계정 선택)
	{
		//메뉴 출력
		{
			std::cout << "사이트 이름을 변경할 경우 0번을 선택하고, \n사이트 내 계정의 속성을 변경할 경우 계정의 번호를 선택해주세요." << std::endl;
			zero_selection_explain("사이트 이름 변경", temp_site);
			temp_site->show_account_information();
		}
		//메뉴 중에서 선택
		{
			std::cout << "계정 선택 > ";
			General_Function::order_color_input(this->selection);
			this->selection_2 = General_Function::string_to_integer(this->selection);
		}
		//선택에 대한 예외처리
		{
			try {
				if (this->selection_2 == argument::zero_selection) {
					return update_site_name(order);
				}
				else {
					return update_account_attribute(order);
				}
			}
			catch (std::string error_message) {
				Status::set_is_form_filling_successful(false);
				std::cout << error_message << std::endl;
				return;
			}
		}
	}
}

void Order_Form_Filler::update_site_name(Order_token * order)
{
	Site * temp_site = this->person->site_number_to_Site(this->selection_1);

	namespace update = argument::instruction::update;
	order->tokens[update::site_name_position] = temp_site->get_site_name();
	std::string new_site_name;
	//세번째 페이지 ()
	{
		//메뉴출력
		{
			std::cout << "변경할 사이트 이름 ( ";
			print_colored_site_name(temp_site);
			std::cout << " ->  ? )" << std::endl;
			std::cout << "└ > ";
		}
		//메뉴 중에서 선택
		{
			General_Function::order_color_input(new_site_name);
		}
		//선택에 대한 예외처리
		{

		}
	}
	order->tokens[update::new_site_name_position] = new_site_name;
	order->type = update::modify_site_name;
	return;
}

void Order_Form_Filler::update_account_attribute(Order_token * order)
{
	Site * temp_site = this->person->site_number_to_Site(this->selection_1);
	Account * temp_account = temp_site->find_account_with_account_number(this->selection_2);
	//세번째 페이지 (속성 선택)
	{
		//메뉴출력
		{
			print_colored_account_attributes(temp_account);
			std::cout << "속성 선택 > ";
		}
		//메뉴 중에서 선택
		{
			General_Function::order_color_input(this->selection);
			this->selection_3 = General_Function::string_to_integer(this->selection);
		}
		//선택에 대한 예외처리
		{
			try {
				if (this->selection_3 < 1 || 3 < this->selection_3)
					throw err_exp::msg_undefined_account_attribute;
			}
			catch (std::string error_message) { //보통의 catch문
				Status::set_is_form_filling_successful(false);
				std::cout << error_message << std::endl;;
				return;
			}
		}
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
	//네번째 페이지 (선택된 속성이 가지게 될 값 입력)
	{
		//메뉴출력
		{

		}
		//메뉴 중에서 선택
		{
			std::cout << "변경할 내용 > ";
			General_Function::order_color_input(new_attribute_value);
		}
		//선택에 대한 예외처리
		{
			///지금 다 생략했는데, 사실 입력 안 받으면 취소하도록 예외처리해야한다.
		}
	}
	order->tokens[update::new_attribute_value_position] = new_attribute_value;
	order->type = update::modify_account_attribute;
	return;
}

bool Order_Form_Filler::exception_no_sites()
{
	try {
		if (this->person->get_site_count() == 0)	//사이트가 없으면 del의 의미가 없다.
			throw err_exp::msg_person_hasnt_site;
	}
	catch (std::string error_message) { //보통의 catch문
		Status::set_is_form_filling_successful(false);
		std::cout << error_message << std::endl;
		return true;
	}
	return false;
}

void Order_Form_Filler::zero_selection_explain(std::string sentence)
{
	SET_CONSOLE_COLOR(console_color::zero_selection);
	this->person->print_site_number(0);
	std::cout << sentence << std::endl;
	SET_CONSOLE_COLOR_DEFAULT;
}

void Order_Form_Filler::zero_selection_explain(std::string sentence, Site * site)
{	//사이트 이름을 추가로 출력
	SET_CONSOLE_COLOR(console_color::zero_selection);
	this->person->print_site_number(0);
	print_colored_site_name(site);
	std::cout << sentence << std::endl;
	SET_CONSOLE_COLOR_DEFAULT;
}

void Order_Form_Filler::print_colored_site_name(Site * site)
{
	SET_CONSOLE_COLOR(console_color::site_name_color);
	std::cout << site->get_site_name();
	SET_CONSOLE_COLOR_DEFAULT;
}

void Order_Form_Filler::print_colored_account_attributes(Account * account)
{
	SET_CONSOLE_COLOR(console_color::account_attribute_color);
	std::cout << "[1] ID : " << account->get_attribute("ID") << std::endl;
	std::cout << "[2] PW : " << account->get_attribute("PW") << std::endl;
	std::cout << "[3] memo : " << account->get_attribute("Memo") << std::endl;
	SET_CONSOLE_COLOR_DEFAULT;
}
