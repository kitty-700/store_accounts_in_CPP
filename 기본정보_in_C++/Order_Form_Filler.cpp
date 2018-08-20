#include "Order_Form_Filler.h"
namespace err_exp = error_expression;
Order_Form_Filler::Order_Form_Filler(Person * person, Order_token * order) 
	: person(person) , order(order) { }
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
		//��������
		{

		}
	}

*/

void Order_Form_Filler::add_form_filler()
{	//"add" ��ɿ� ���� ����� �޴´�. 
	//ADD-1 ������ (����Ʈ ����)
	{	
		//�޴� ���
		{
			std::cout << "������ �߰��ϰ��� �ϴ� ����Ʈ�� ��ȣ�� �������ּ���." << std::endl;
			zero_selection_explain("����Ʈ �߰�");
			this->person->show_site_name_list();
		}
		//�޴� �߿��� ����
		{
			std::cout << "���� > ";
			General_Function::order_color_input(this->selection);
			this->selection_1 = General_Function::string_to_integer(this->selection);
		}
		//���ÿ� ���� ����ó��
		{
			try {
				if (this->selection_1 == error_expression::string_to_be_int_wasnt_entered)
					throw error_expression::msg_form_filling_cancel;
				if (is_count_range(this->selection_1, this->person->get_site_count()) == false)
					throw error_expression::msg_no_existing_site_number;
			}
			catch (std::string error_message) { //������ catch��
				Status::set_is_form_filling_successful(false);
				std::cout << error_message << std::endl;
				return;
			}
		}
		//��������
		{
			if (this->selection_1 == argument::zero_selection)
				add_new_site();
			else
				add_new_account();
		}
	}//ù��° ������ (����Ʈ ����)
	return;
}

void Order_Form_Filler::add_new_site()
{
	using namespace std;
	std::string new_site_name;
	//ADD-2-NewSite ������ (����Ʈ �̸� �Է�)
	{
		std::cout << "�� ����Ʈ �̸� > ";
		General_Function::order_color_input(new_site_name);
	}

	using namespace argument::instruction::add;
	this->order->tokens[new_site_name_position] = new_site_name;
	this->order->type = add_site_only;
}

void Order_Form_Filler::add_new_account()
{
	Site * temp_site = this->person->site_number_to_Site(this->selection_1);

	using namespace argument::instruction::add;
	std::string temp_str;
	//ADD-2-NewAccount ������ (���� ���� �Է�)
	{
		//�޴� ���
		{
			temp_site->show_account_information();
		}
		this->order->tokens[new_site_name_position] = temp_site->get_site_name();
		//
		std::cout << "�� ������ ID > ";
		General_Function::order_color_input(temp_str);
		this->order->tokens[new_id_position] = temp_str;
		//
		std::cout << "�� ������ PW > ";
		General_Function::order_color_input(temp_str);
		this->order->tokens[new_pw_position] = temp_str;
		//
		std::cout << "�� ������ ���� �޸� > ";
		General_Function::order_color_input(temp_str);
		this->order->tokens[new_memo_position] = temp_str;

		this->order->token_count = add_account_with_memo;
	}
	return;
}

void Order_Form_Filler::del_form_filler()
{	//"del" ��ɿ� ���� ����� �޴´�.
	if (exception_no_sites() == true)
		return;
	Site * temp_site;
	//DEL-1-SiteSelect ������ (����Ʈ ����)
	{
		//�޴� ���
		{
			std::cout << "����Ʈ ��ü Ȥ�� ������ �����ϰ��� �ϴ� ����Ʈ�� ��ȣ�� �������ּ���." << std::endl;
			zero_selection_explain("���� ���");
			this->person->show_site_name_list();
		}
		//�޴� �߿��� ����
		{
			std::cout << "���� > ";
			General_Function::order_color_input(this->selection);
			this->selection_1 = General_Function::string_to_integer(this->selection);
		}
		//���ÿ� ���� ����ó��
		{
			try {
				if (this->selection_1 == error_expression::string_to_be_int_wasnt_entered)
					throw err_exp::msg_form_filling_cancel;
				if (this->selection_1 == argument::zero_selection)
					throw err_exp::msg_form_filling_cancel;
				if (is_count_range(this->selection_1, this->person->get_site_count()) == false)
					throw err_exp::msg_no_existing_site_number;
			}
			catch (std::string error_message) { //������ catch��
				Status::set_is_form_filling_successful(false);
				std::cout << error_message << std::endl;
				return;
			}
		}
		//��������
		{
			temp_site = this->person->site_number_to_Site(this->selection_1);
		}
	}//DEL-1-SiteSelect ������ (����Ʈ ����)

	//DEL-2-AccountSelect ������ (����Ʈ ��ü(0) Ȥ�� ���� ����)
	{
		//�޴� ���
		{
			std::cout << "������ ������ ��ȣ�� �������ּ���." << std::endl;
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
				if (is_count_range(this->selection_2, temp_site->get_account_count()) == false)
					throw error_expression::msg_no_existing_account_number;
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
				del_site(temp_site);
			else
				del_account(temp_site);
		}
	}//DEL-2-AccountSelect ������ (����Ʈ ��ü(0) Ȥ�� ���� ����)
	return;
}

void Order_Form_Filler::del_site(Site * site)
{
	using namespace argument::instruction::del;
	this->order->tokens[site_name_position] = site->get_site_name();
	this->order->type = delete_site;
	return;
}

void Order_Form_Filler::del_account(Site * site)
{
	using namespace argument::instruction::del;
	this->order->tokens[site_name_position] = site->get_site_name();
	Account * temp_account = site->find_account_with_account_number(this->selection_2);
	this->order->tokens[id_position] = temp_account->get_attribute("ID");
	this->order->type = delete_account;
	return;
}

void Order_Form_Filler::update_form_filler()
{	//"update" ��ɿ� ���� ����� �޴´�.
	if (exception_no_sites() == true)
		return;
	Site * temp_site;
	//UPDATE-1 ������ (����Ʈ ����)
	{	
		//�޴� ���
		{
			std::cout << "����Ʈ �̸� Ȥ�� ���� �Ӽ��� �����ϰ��� �ϴ� ����Ʈ�� ��ȣ�� �������ּ���." << std::endl;
			zero_selection_explain("���� ���");
			this->person->show_site_name_list();
		}
		//�޴� �߿��� ����
		{
			std::cout << "���� > ";
			General_Function::order_color_input(this->selection);
			this->selection_1 = General_Function::string_to_integer(this->selection);
		}
		//���ÿ� ���� ����ó��
		{
			try {
				if (this->selection_1 == error_expression::string_to_be_int_wasnt_entered)
					throw error_expression::msg_form_filling_cancel;
				if (this->selection_1 == argument::zero_selection)
					throw err_exp::msg_form_filling_cancel;
				if (is_count_range(this->selection_1, this->person->get_site_count()) == false)
					throw err_exp::msg_no_existing_site_number;
			}
			catch (std::string error_message) {
				Status::set_is_form_filling_successful(false);
				std::cout << error_message << std::endl;
				return;
			}
		}
		//��������
		{
			temp_site = this->person->site_number_to_Site(this->selection_1);
		}
	}//UPDATE-1 ������ (����Ʈ ����)

	//UPDATE-2 ������ (����Ʈ ��ü(0) Ȥ�� ���� ����)
	{
		//�޴� ���
		{
			std::cout << "����Ʈ �̸��� ������ ��� 0���� �����ϰ�, \n����Ʈ �� ������ �Ӽ��� ������ ��� ������ ��ȣ�� �������ּ���." << std::endl;
			zero_selection_explain("����Ʈ �̸� ����", temp_site);
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
				if (is_count_range(this->selection_2, temp_site->get_account_count()) == false)
					throw error_expression::msg_no_existing_account_number;
			}
			catch (std::string error_message) {
				Status::set_is_form_filling_successful(false);
				std::cout << error_message << std::endl;
				return;
			}
		}
		//��������
		{
			if (this->selection_2 == argument::zero_selection)
				update_site_name(temp_site);
			else
				update_account_attribute(temp_site);
		}
	}//UPDATE-2 ������ (����Ʈ ��ü(0) Ȥ�� ���� ����)
}

void Order_Form_Filler::update_site_name(Site * site)
{
	namespace update = argument::instruction::update;
	this->order->tokens[update::site_name_position] = site->get_site_name();
	std::string new_site_name;
	//UPDATE-3-UpdateSiteName ������ (����Ʈ ��ü(0) Ȥ�� ���� ����)
	{
		//�޴����
		{
			std::cout << "������ ����Ʈ �̸� ( ";
			print_colored_site_name(site);
			std::cout << " ->  ? )" << std::endl;
		}
		//�޴� �߿��� ����
		{
			std::cout << "�� > ";
			General_Function::order_color_input(new_site_name);
		}
		//���ÿ� ���� ����ó��
		{
			try {
				if (new_site_name == "")
					throw error_expression::msg_form_filling_cancel;
			}
			catch (std::string error_message) {
				Status::set_is_form_filling_successful(false);
				std::cout << error_message << std::endl;;
				return;
			}
		}
		//��������
		{
			this->order->tokens[update::new_site_name_position] = new_site_name;
			this->order->type = update::modify_site_name;
		}
	}//UPDATE-3-UpdateSiteName ������ (����Ʈ ��ü(0) Ȥ�� ���� ����)
	return;
}

void Order_Form_Filler::update_account_attribute(Site * site)
{
	namespace update = argument::instruction::update;
	Site * temp_site = this->person->site_number_to_Site(this->selection_1);
	Account * temp_account = temp_site->find_account_with_account_number(this->selection_2);

	//UPDATE-3-UpdateAccountAttribute ������ (���� �Ӽ� ���� ID/PW/Memo)
	{
		//�޴����
		{
			print_colored_account_attributes(temp_account);
			std::cout << "���� > ";
		}
		//�޴� �߿��� ����
		{
			General_Function::order_color_input(this->selection);
			this->selection_3 = General_Function::string_to_integer(this->selection);
		}
		//���ÿ� ���� ����ó��
		{
			try {
				if (this->selection_3 == error_expression::string_to_be_int_wasnt_entered)
					throw error_expression::msg_form_filling_cancel;
				if (this->selection_3 < 1 || 3 < this->selection_3) //�Ӽ��� 1~3��
					throw err_exp::msg_undefined_account_attribute;
			}
			catch (std::string error_message) { //������ catch��
				Status::set_is_form_filling_successful(false);
				std::cout << error_message << std::endl;;
				return;
			}
		}
		//��������
		{
			this->order->tokens[update::site_name_position] = temp_site->get_site_name();
			this->order->tokens[update::id_position] = temp_account->get_attribute("ID");

			switch (this->selection_3)
			{
			case 1:
				this->order->tokens[update::attribute_select_position] = "ID";
				break;
			case 2:
				this->order->tokens[update::attribute_select_position] = "PW";
				break;
			case 3:
				this->order->tokens[update::attribute_select_position] = "memo";
				break;
			}
		}
	}//UPDATE-3-AccountAttributeSelect ������ (���� �Ӽ� ����)

	std::string new_attribute_value;
	//UPDATE-4-AttributeValueInput ������ (���õ� �Ӽ��� ������ �� �� �Է�)
	{
		//�޴����
		{
			std::cout << "������ ";
			std::cout << this->order->tokens[update::attribute_select_position];
			std::cout << "( ";
			print_colored_account_attribute(temp_account, this->order->tokens[update::attribute_select_position]);
			std::cout << " ->  ? )" << std::endl;
		}
		//�޴� �߿��� ����
		{
			std::cout << "������ ���� > ";
			General_Function::order_color_input(new_attribute_value);
		}
		//���ÿ� ���� ����ó��
		{
			try {
				if (new_attribute_value == "")
					throw error_expression::msg_form_filling_cancel;
			}
			catch (std::string error_message) {
				Status::set_is_form_filling_successful(false);
				std::cout << error_message << std::endl;;
				return;
			}
		}
		//��������
		{
			this->order->tokens[update::new_attribute_value_position] = new_attribute_value;
			this->order->type = update::modify_account_attribute;
		}
	}//UPDATE-4-AttributeValueInput ������ (���õ� �Ӽ��� ������ �� �� �Է�)
	
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

void Order_Form_Filler::print_colored_account_attribute(Account * account, std::string attribute)
{
	SET_CONSOLE_COLOR(console_color::account_attribute_color);
	if (attribute == "ID")
		std::cout <<  account->get_attribute("ID");
	else if (attribute == "PW")
		std::cout <<  account->get_attribute("PW");
	else if (attribute == "memo")
		std::cout <<  account->get_attribute("Memo") ;
	else
		assert(0);
	SET_CONSOLE_COLOR_DEFAULT;
}

bool Order_Form_Filler::is_count_range(int select, int count)
{
	return (0 <= select && select <= count) ? true : false;
}
