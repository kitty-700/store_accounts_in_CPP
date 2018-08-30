#include "Order_Form_Filler.h"
namespace err_exp = option::expression::error;
namespace color = option::parameters::console_color;
Order_Form_Filler::Order_Form_Filler(Person * person)
	: person(person) { }
/* �Է� ���

	//ù��° ������ ()
	{
		//�޴����
		{

		}
		//�޴� �߿��� ���� or �Է�
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
			menu_print(false, "������ �߰��ϰ��� �ϴ� ����Ʈ�� ��ȣ�� �������ּ���.");
			zero_selection_explain("����Ʈ �߰�");
			this->person->show_site_name_list();
		}
		//�޴� �߿��� ����
		{
			input_number(&this->selection_1, "����");
		}
		//���ÿ� ���� ����ó��
		{
			exception_no_input(this->selection_1);
			exception_range_out(this->selection_1, this->person->get_site_count());
		}
		//��������
		{
			if (this->selection_1 == argument::zero_selection)
				add_new_site();
			else {
				Site * temp_site = this->person->find_Site(this->selection_1);
				add_new_account(temp_site);
			}
		}
	}//ADD-1 ������ (����Ʈ ����)
	return;
}

void Order_Form_Filler::add_new_site()
{
	std::string new_site_name;
	//ADD-2-NewSite ������ (����Ʈ �̸� �Է�)
	{
		//�޴����
		{
			menu_print(true, "");
			this->person->show_site_name_list();
		}
		//�Է�
		{
			input_string(false, new_site_name, "�� ����Ʈ �̸�");
		}
		//���ÿ� ���� ����ó��
		{		}
		//��������
		{
			using namespace argument::instruction::add;
			Order::set_content(new_site_name_position, new_site_name);
			Order::set_token_count(add_site_only);
		}
	}
}

void Order_Form_Filler::add_new_account(Site * site)
{
	std::string ID_input;
	std::string PW_input;
	std::string memo_input;
	//ADD-2-NewAccount ������ (���� ���� �Է�)
	{
		//�޴� ���
		{
			menu_print(true, "");
			site->show_account_information();
		}
		//�Է�
		{
			input_string(false, ID_input, "�� ������ ID");
			input_string(false, PW_input, "�� ������ PW");
			input_string(false, memo_input, "�� ������ ���� �޸�");
		}
		//���ÿ� ���� ����ó��
		{		}
		//��������
		{
			using namespace argument::instruction::add;
			Order::set_content(new_site_name_position, site->get_site_name());
			Order::set_content(new_id_position, ID_input);
			Order::set_content(new_pw_position, PW_input);
			Order::set_content(new_memo_position, memo_input);
			Order::set_token_count(add_account_with_memo);
		}
	}
	return;
}

void Order_Form_Filler::del_form_filler()
{	//"del" ��ɿ� ���� ����� �޴´�.
	exception_no_sites(this->person->get_site_count());

	Site * temp_site;
	//DEL-1-SiteSelect ������ (����Ʈ ����)
	{
		//�޴� ���
		{
			menu_print(false, "����Ʈ ��ü Ȥ�� ������ �����ϰ��� �ϴ� ����Ʈ�� ��ȣ�� �������ּ���.");
			zero_selection_explain("���� ���");
			this->person->show_site_name_list();
		}
		//�޴� �߿��� ����
		{
			input_number(&this->selection_1, "����");
		}
		//���ÿ� ���� ����ó��
		{
			exception_no_input(this->selection_1);
			exception_zero_to_quit(this->selection_1);
			exception_range_out(this->selection_1, this->person->get_site_count());
		}
		//��������
		{
			temp_site = this->person->find_Site(this->selection_1);
		}
	}//DEL-1-SiteSelect ������ (����Ʈ ����)

	//DEL-2-AccountSelect ������ (����Ʈ ��ü(0) Ȥ�� ���� ����)
	{
		//�޴� ���
		{
			menu_print(true, "������ ������ ��ȣ�� �������ּ���.");
			zero_selection_explain("����Ʈ ����", temp_site);
			temp_site->show_account_information();
		}
		//�޴� �߿��� ����
		{
			input_number(&this->selection_2, "����");
		}
		//���ÿ� ���� ����ó��
		{
			exception_no_input(this->selection_2);
			exception_range_out(this->selection_2, temp_site->get_account_count());
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
	Order::set_content(site_name_position, site->get_site_name());
	Order::set_token_count(delete_site);
	return;
}

void Order_Form_Filler::del_account(Site * site)
{
	using namespace argument::instruction::del;
	Account * temp_account = site->find_account_with_account_number(this->selection_2);
	Order::set_content(site_name_position, site->get_site_name());
	Order::set_content(id_position, temp_account->get_attribute("ID"));
	Order::set_token_count(delete_account);
	return;
}

void Order_Form_Filler::update_form_filler()
{	//"update" ��ɿ� ���� ����� �޴´�.
	exception_no_sites(this->person->get_site_count());

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
			input_number(&this->selection_1, "����");
		}
		//���ÿ� ���� ����ó��
		{
			exception_no_input(this->selection_1);
			exception_zero_to_quit(this->selection_1);
			exception_range_out(this->selection_1, this->person->get_site_count());
		}
		//��������
		{
			temp_site = this->person->find_Site(this->selection_1);
		}
	}//UPDATE-1 ������ (����Ʈ ����)

	//UPDATE-2 ������ (����Ʈ ��ü(0) Ȥ�� ���� ����)
	{
		//�޴� ���
		{
			General_Function::print_thin_line();
			std::cout << "����Ʈ �̸��� ������ ��� 0���� �����ϰ�, \n����Ʈ �� ������ �Ӽ��� ������ ��� ������ ��ȣ�� �������ּ���." << std::endl;
			zero_selection_explain("����Ʈ �̸� ����", temp_site);
			temp_site->show_account_information();
		}
		//�޴� �߿��� ����
		{
			input_number(&this->selection_2, "����");
		}
		//���ÿ� ���� ����ó��
		{
			exception_no_input(this->selection_2);
			exception_range_out(this->selection_2, temp_site->get_account_count());
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

	std::string new_site_name;
	//UPDATE-3-UpdateSiteName ������ (����Ʈ ��ü(0) Ȥ�� ���� ����)
	{
		//�޴����
		{
			menu_print(true, "������ ����Ʈ �̸� �Է�");
		}
		//�Է�
		{
			print_colored_site_name(site);
			input_string(true, new_site_name);
		}
		//���ÿ� ���� ����ó��
		{
			exception_no_input(new_site_name);
		}
		//��������
		{
			Order::set_content(update::site_name_position, site->get_site_name());
			Order::set_content(update::new_site_name_position, new_site_name);
			Order::set_token_count(update::modify_site_name);
		}
	}//UPDATE-3-UpdateSiteName ������ (����Ʈ ��ü(0) Ȥ�� ���� ����)
	return;
}

void Order_Form_Filler::update_account_attribute(Site * site)
{
	Account * account = site->find_account_with_account_number(this->selection_2);
	namespace update = argument::instruction::update;

	//UPDATE-3-AccountAttributeSelect ������ (���� �Ӽ� ���� ID/PW/Memo)
	{
		//�޴����
		{
			menu_print(true, "������ �Ӽ��� �������ּ���.");
			zero_selection_explain("���� ���");
			print_colored_account_attributes(account);
		}
		//�޴� �߿��� ����
		{
			input_number(&this->selection_3, "����");
		}
		//���ÿ� ���� ����ó��
		{
			exception_no_input(this->selection_3);
			exception_range_out(this->selection_3, 3);
			exception_zero_to_quit(this->selection_3);
		}
		//��������
		{
			Order::set_content(update::site_name_position, site->get_site_name());
			Order::set_content(update::id_position, account->get_attribute("ID"));

			switch (this->selection_3)
			{
			case 1:
				Order::set_content(update::attribute_select_position, "ID");
				break;
			case 2:
				Order::set_content(update::attribute_select_position, "PW");
				break;
			case 3:
				Order::set_content(update::attribute_select_position, "memo");
				break;
			}
		}
	}//UPDATE-3-AccountAttributeSelect ������ (���� �Ӽ� ���� ID/PW/Memo)

	std::string new_attribute_value;
	//UPDATE-4-AttributeValueInput ������ (���õ� �Ӽ��� ������ �� �� �Է�)
	{
		//�޴����
		{
			menu_print(true, "������ �Ӽ��� ������ �Է����ּ���.");
		}
		//�Է�
		{
			std::string attribute____ = Order::get_content(update::attribute_select_position);
			std::cout << attribute____ << ") ";
			print_colored_account_attribute(account, attribute____);
			input_string(true, new_attribute_value);
		}
		//���ÿ� ���� ����ó��
		{
			if (Order::get_content(update::attribute_select_position) != "memo")
				exception_no_input(new_attribute_value);
		}
		//��������
		{
			Order::set_content(update::new_attribute_value_position, new_attribute_value);
			Order::set_token_count(update::modify_account_attribute);
		}
	}//UPDATE-4-AttributeValueInput ������ (���õ� �Ӽ��� ������ �� �� �Է�)

	return;
}

void Order_Form_Filler::load_form_filler()
{	// "load" ��ɿ� ���� ����� �޴´�.
	std::string file_name;
	//LOAD-1 ������ (���� �̸� �Է�)
	{
		//�޴� ���
		{
			menu_print(true, "���� �ε��ϰ��� �ϴ� ������ �̸��� �Է����ּ���.");
		}
		//�Է�
		{
			input_string(false, file_name, "���� �̸�");
		}
		//���ÿ� ���� ����ó��
		{
			exception_no_input(file_name);
		}
		//��������
		{
			using namespace argument::instruction::load;
			Order::set_content(file_name_position, file_name);
		}
	}//LOAD-1 ������ (���� �̸� �Է�)
	return;
}

void Order_Form_Filler::exception_no_sites(int site_count)
{	//site�� ������ ������ �ǹ̰� ���� DEL, UPDATE �� ���� ��ɿ� ���δ�.
		if (site_count == 0)	//����Ʈ�� ������ del�� �ǹ̰� ����.
			throw err_exp::msg_person_hasnt_site;
}

void Order_Form_Filler::exception_no_input(int selection)
{
	if (selection == err_exp::string_to_be_int_wasnt_entered)
		throw Form_Filling_Exception(err_exp::msg_no_input_form_filling_cancel);
}

void Order_Form_Filler::exception_no_input(std::string selection)
{
	if (selection == "")
		throw Form_Filling_Exception(err_exp::msg_no_input_form_filling_cancel);
}

void Order_Form_Filler::exception_zero_to_quit(int selection)
{
	if (selection == argument::zero_selection)
		throw Form_Filling_Exception(err_exp::msg_form_filling_cancel_on_purpose);
}

void Order_Form_Filler::exception_range_out(int select, int count)
{
	if (is_within_count_range(select, count) == false)
		throw Form_Filling_Exception(err_exp::msg_ineffective_select);
}

void Order_Form_Filler::zero_selection_explain(std::string sentence)
{
	SET_CONSOLE_COLOR(color::zero_selection);
	this->person->print_site_number(0);
	std::cout << sentence << std::endl;
	SET_CONSOLE_COLOR_DEFAULT;
}

void Order_Form_Filler::zero_selection_explain(std::string sentence, Site * site)
{	//����Ʈ �̸��� �߰��� ���
	SET_CONSOLE_COLOR(color::zero_selection);
	this->person->print_site_number(0);
	print_colored_site_name(site);
	SET_CONSOLE_COLOR(color::zero_selection);
	std::cout << sentence << std::endl;
	SET_CONSOLE_COLOR_DEFAULT;
}

void Order_Form_Filler::print_colored_site_name(Site * site)
{	
	SET_CONSOLE_COLOR(color::site_name_color);
	std::cout << site->get_site_name();
	SET_CONSOLE_COLOR_DEFAULT;
}

void Order_Form_Filler::print_colored_account_attributes(Account * account)
{
	SET_CONSOLE_COLOR(color::account_attribute_color);
	std::cout << "[1] ID : " << account->get_attribute("ID") << std::endl;
	std::cout << "[2] PW : " << account->get_attribute("PW") << std::endl;
	std::cout << "[3] memo : " << account->get_attribute("Memo") << std::endl;
	SET_CONSOLE_COLOR_DEFAULT;
}

void Order_Form_Filler::print_colored_account_attribute(Account * account, std::string attribute)
{
	SET_CONSOLE_COLOR(color::account_attribute_color);
	if (attribute == "ID")
		std::cout << account->get_attribute("ID");
	else if (attribute == "PW")
		std::cout << account->get_attribute("PW");
	else if (attribute == "memo")
		std::cout << account->get_attribute("Memo");
	else
		assert(0);
	SET_CONSOLE_COLOR_DEFAULT;
}

bool Order_Form_Filler::is_within_count_range(int select, int count)
{	//0�� ������������ ������ַ� ���
	return (0 <= select && select <= count) ? true : false;
}


void Order_Form_Filler::menu_print(const bool line_devide, std::string sign)
{
	if (line_devide == true)
		General_Function::print_thin_line();
	if (sign != "")
		std::cout << sign << std::endl;
}
void Order_Form_Filler::input_string(const bool change, std::string & str, const std::string message)
{
	if(change==true) std::cout << " ��> "; //�� ��� �տ� �ٲ�� ���� ���� �������� ����س����Ѵ�.
	else {
		std::cout << message << " > ";
	}
	General_Function::order_color_input(str);
}

void Order_Form_Filler::input_number(int * number, const std::string message)
{
	std::cout << message << " > ";
	General_Function::order_color_input(this->selection);
	*number = General_Function::string_to_integer(this->selection);
}

