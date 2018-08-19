#include "Order_Form_Filler.h"
namespace err_exp = error_expression;
Order_Form_Filler::Order_Form_Filler(Person * person) : person(person) { }
/* �Է� ���

//ù��° ������ ()
{
	//�޴����
	{
		
	}
	//�޴� �߿��� ����
	{

	}
	//���ÿ� ���� ����ó��
	{

	}
}
*/
void Order_Form_Filler::add_form_filler(Order_token * order)
{	//"add" ��ɿ� ���� ����� �޴´�. 
	//ù��° ������ (����Ʈ ����)
	{	
		//�޴� ���
		{
			std::cout << "������ �߰��ϰ��� �ϴ� ����Ʈ�� ��ȣ�� �������ּ���." << std::endl;
			zero_selection_explain("����Ʈ �߰�");
			this->person->show_site_name_list();
		}
		//�޴� �߿��� ����
		{
			std::cout << "> ";
			General_Function::order_color_input(this->selection);
			this->selection_1 = General_Function::string_to_integer(this->selection);
		}
		//���ÿ� ���� ����ó��
		{
			try {
				if (this->selection_1 == error_expression::string_to_be_int_wasnt_entered)
					throw error_expression::msg_form_filling_cancel;
				else if (this->selection_1 == argument::zero_selection)
					add_new_site(order);
				else
					add_new_account(order);
			}
			catch (std::string error_message) { //������ catch��
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
	std::cout << "�� ����Ʈ �̸� > ";
	General_Function::order_color_input(new_site_name);

	using namespace argument::instruction::add;
	order->tokens[new_site_name_position] = new_site_name;
	order->type = add_site_only;
}

void Order_Form_Filler::add_new_account(Order_token * order)
{	//����Ʈ ��ȣ�� �߸� �Է��ϸ� ����
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
	std::cout << "�� ������ ID > ";
	General_Function::order_color_input(temp_str);
	order->tokens[new_id_position] = temp_str;

	std::cout << "�� ������ PW > ";
	General_Function::order_color_input(temp_str);
	order->tokens[new_pw_position] = temp_str;

	std::cout << "�� ������ ���� �޸� > ";
	General_Function::order_color_input(temp_str);
	order->tokens[new_memo_position] = temp_str;

	order->token_count = add_account_with_memo;
	return;
}

void Order_Form_Filler::del_form_filler(Order_token * order)
{	//"del" ��ɿ� ���� ����� �޴´�.
	if (exception_no_sites() == true)
		return;
	Site * temp_site;
	//ù��° ������ (����Ʈ ����)
	{
		//�޴� ���
		{
			std::cout << "����Ʈ ��ü Ȥ�� ������ �����ϰ��� �ϴ� ����Ʈ�� ��ȣ�� �������ּ���." << std::endl;
			zero_selection_explain("���� ���");
			this->person->show_site_name_list();
		}
		//�޴� �߿��� ����
		{
			std::cout << "����Ʈ ���� > ";
			General_Function::order_color_input(this->selection);
			this->selection_1 = General_Function::string_to_integer(this->selection);
		}
		//���ÿ� ���� ����ó��
		{
			try {
				if (this->selection_1 == error_expression::string_to_be_int_wasnt_entered)
					throw error_expression::msg_form_filling_cancel;
				if (this->selection_1 <= 0) //��ȣ�� 0 ������ ����Ʈ�� �����Ƿ�.
					throw err_exp::msg_no_existing_site_number;
				temp_site = this->person->site_number_to_Site(this->selection_1);
				if (temp_site == nullptr)
					throw err_exp::msg_no_existing_site_number;
			}
			catch (std::string error_message) { //������ catch��
				Status::set_is_form_filling_successful(false);
				std::cout << error_message << std::endl;
				return;
			}
		}
	}
	//�ι�° ������ (����Ʈ ��ü(0) Ȥ�� ���� ����)
	{
		//�޴� ���2
		{
			std::cout << "����Ʈ ��ü�� ������ ��� 0���� �����ϰ�, \n����Ʈ ���� ������ ������ ��� ������ ��ȣ�� �������ּ���." << std::endl;
			zero_selection_explain("����Ʈ ����", temp_site);
			temp_site->show_account_information();
		}
		//�޴� �߿��� ����
		{
			std::cout << "���� > ";
			General_Function::order_color_input(this->selection);
			this->selection_2 = General_Function::string_to_integer(this->selection);
		}
		//���ÿ� ���� ����ó��
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
		//���� ����
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
{	//"update" ��ɿ� ���� ����� �޴´�.
	if (exception_no_sites() == true)
		return;
	Site * temp_site;
	//ù��° ������ (����Ʈ ����)
	{	
		//�޴� ���
		{
			std::cout << "����Ʈ �̸� Ȥ�� ���� �Ӽ��� �����ϰ��� �ϴ� ����Ʈ�� ��ȣ�� �������ּ���." << std::endl;
			zero_selection_explain("���� ���");
			this->person->show_site_name_list();
		}
		//�޴� �߿��� ����
		{
			std::cout << "����Ʈ ���� > ";
			General_Function::order_color_input(this->selection);
			this->selection_1 = General_Function::string_to_integer(this->selection);
		}
		//���ÿ� ���� ����ó��
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

	//�ι�° ������ (����Ʈ ��ü(0) Ȥ�� ���� ����)
	{
		//�޴� ���
		{
			std::cout << "����Ʈ �̸��� ������ ��� 0���� �����ϰ�, \n����Ʈ �� ������ �Ӽ��� ������ ��� ������ ��ȣ�� �������ּ���." << std::endl;
			zero_selection_explain("����Ʈ �̸� ����", temp_site);
			temp_site->show_account_information();
		}
		//�޴� �߿��� ����
		{
			std::cout << "���� ���� > ";
			General_Function::order_color_input(this->selection);
			this->selection_2 = General_Function::string_to_integer(this->selection);
		}
		//���ÿ� ���� ����ó��
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
	//����° ������ ()
	{
		//�޴����
		{
			std::cout << "������ ����Ʈ �̸� ( ";
			print_colored_site_name(temp_site);
			std::cout << " ->  ? )" << std::endl;
			std::cout << "�� > ";
		}
		//�޴� �߿��� ����
		{
			General_Function::order_color_input(new_site_name);
		}
		//���ÿ� ���� ����ó��
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
	//����° ������ (�Ӽ� ����)
	{
		//�޴����
		{
			print_colored_account_attributes(temp_account);
			std::cout << "�Ӽ� ���� > ";
		}
		//�޴� �߿��� ����
		{
			General_Function::order_color_input(this->selection);
			this->selection_3 = General_Function::string_to_integer(this->selection);
		}
		//���ÿ� ���� ����ó��
		{
			try {
				if (this->selection_3 < 1 || 3 < this->selection_3)
					throw err_exp::msg_undefined_account_attribute;
			}
			catch (std::string error_message) { //������ catch��
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
	//�׹�° ������ (���õ� �Ӽ��� ������ �� �� �Է�)
	{
		//�޴����
		{

		}
		//�޴� �߿��� ����
		{
			std::cout << "������ ���� > ";
			General_Function::order_color_input(new_attribute_value);
		}
		//���ÿ� ���� ����ó��
		{
			///���� �� �����ߴµ�, ��� �Է� �� ������ ����ϵ��� ����ó���ؾ��Ѵ�.
		}
	}
	order->tokens[update::new_attribute_value_position] = new_attribute_value;
	order->type = update::modify_account_attribute;
	return;
}

bool Order_Form_Filler::exception_no_sites()
{
	try {
		if (this->person->get_site_count() == 0)	//����Ʈ�� ������ del�� �ǹ̰� ����.
			throw err_exp::msg_person_hasnt_site;
	}
	catch (std::string error_message) { //������ catch��
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
{	//����Ʈ �̸��� �߰��� ���
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
