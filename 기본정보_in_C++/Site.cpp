#include "Site.h"
using namespace std;
namespace err_exp = option::error_expression;
Site::Site() : account_count(0) {}
Site::~Site()
{
	clean_itself();
}
void Site::operator+=(Account * account)
{
	this->accounts.push_back(account);
	this->account_count++;
}
void Site::clean_itself()
{	//Site �� ����, �����Ҵ��� ��� ��� ���ؼ� �Ҵ� �����Ѵ�.
	for (std::list<Account*>::iterator position = this->accounts.begin(); position != this->accounts.end(); )
	{
		del_account((*position)->get_attribute("ID"));
		position = this->accounts.begin();
	}
}
string Site::get_site_name()
{
	return string(this->site_name);
}
int Site::get_account_count() const
{
	return this->account_count;
}
bool Site::is_proper_string(string what_attribute, string str) const
{
	try { //1.�����Ϸ��� �Ӽ��� site_name�� �´���, 2.���̰� ��������, 3. ������ �ƴ��� 4.Ư�����ڰ� ���ԵǾ������� ������
		if (what_attribute != "site_name")
			throw err_exp::msg_undefined_site_attribute;
		else {
			if (str.size() > option::buffer::site_name_length)
				throw err_exp::msg_too_long_site_name;
			if (str == "")
				throw err_exp::msg_site_name_must_be_filled;
		}
		namespace arg = option::argument;
		for (int i = 0; i < sizeof(arg::forbidden_chars) / sizeof(char); i++)
			if (str.find(arg::forbidden_chars[i]) != string::npos)
				throw "site �̸��� " + err_exp::msg_forbidden_character;
	}
	catch (std::string error_message) {
		std::cout << error_message << std::endl;
		return false;
	}
	return true;
}
Account * Site::find_account_with_ID(std::string ID)
{
	for (std::list<Account*>::iterator each = this->accounts.begin(); each != this->accounts.end(); each++)
		if ((*each)->get_attribute("ID") == ID)
			return (*each);
	return nullptr;
}
Account * Site::find_account_with_account_number(int account_number)
{
	int count = 1;
	for (
		std::list<Account*>::iterator each = this->accounts.begin();
		each != this->accounts.end();
		each++, count++) 
	{
		if (count == account_number)
			return *(each);
	}
	return nullptr;
}

bool Site::is_redundancy_ID(std::string ID)
{
	if (find_account_with_ID(ID) == nullptr)
		return false;
	return true;
}
void Site::show_account_information()
{
	int count = 1;
	SET_CONSOLE_COLOR(option::console_color::account_attribute_color);
	for (list<Account*>::iterator each = this->accounts.begin(); each != this->accounts.end(); each++)
	{
		std::cout << "[";
		std::cout.fill('0');
		std::cout.width(General_Function::get_cipher(this->account_count));
		std::cout << count << "]��" << std::endl;
		(*each)->show_account_information();
		count++;
	}
	SET_CONSOLE_COLOR_DEFAULT;
	try {
		if (this->account_count == 0)
			throw err_exp::msg_site_hasnt_account;
	}
	catch (std::string error_message) {
		std::cout << error_message << std::endl;
		return;
	}
}
Account * Site::add_account(string ID, string PW, string memo)
{
	try { //����Ʈ ���� ID �ߺ� üũ
		if (is_redundancy_ID(ID) == true)
			throw ID + err_exp::msg_already_existing_ID;
	}
	catch (std::string error_message) {
		std::cout << error_message << std::endl;
		return nullptr;
	}
	Account * temp_account = new Account();
	temp_account->update_attribute("ID", ID);
	temp_account->update_attribute("PW", PW);
	temp_account->update_attribute("memo", memo);
	//���Ϸκ��� ���� �ÿ� update_time �� ������� �ʰ� �Լ� ������ �����Ѵ�.
	//������ ����� �������� �Ǵٴ� ���� �Ͽ� �ٸ��� �����Ѵ�. (Account::update_attribute () ������ ���� ����ش�.)
	if (temp_account->get_attribute("ID") == error_expression::abnormal_Account_ID)
	{
		std::cout << "Account �� ���� �� �����ϴ�." << std::endl;
		delete temp_account;
		return nullptr;
	}
	else {
		*(this) += temp_account;
		Log_Recorder::add_log(Order::get(),"���� �߰�," + ID);
		return temp_account;
	}
}


void Site::del_account(std::string ID)
{
	for (std::list<Account*>::iterator each = this->accounts.begin(); each != this->accounts.end(); each++)
	{
		if ((*each)->get_attribute("ID") == ID)
		{
			std::string to_record =
				"������ ������ ID : " + (*each)->get_attribute("ID");
			delete (*each);
			this->accounts.erase(each);
			this->account_count--;
			Log_Recorder::add_log(Order::get(), to_record);
			return;
		}
	}
	try { //�����Ϸ��� ID�� �� ã���� ���
		throw err_exp::msg_no_existing_ID;
	}
	catch (std::string error_message) {
		std::cout << error_message << std::endl;
		return;
	}
}
void Site::update_site_name(string what_attribute, string new_site_name)
{	//��� ���⿡ attribute �ϳ��ۿ� �ʿ���µ�, Account Ŭ������ ��� ����ϰ� ����� ����.
	what_attribute = expression::Translation::site_attribute_translate(what_attribute);
	argument::order_type op = expression::Translation::operation_translate(Order::get_content(argument::operation_position));
	if (what_attribute == "site_name") //ID ������Ʈ
	{
		if (is_proper_string(what_attribute, new_site_name) == true)
		{
			std::string before_site_name = this->site_name;
			strcpy_s(this->site_name, option::buffer::site_name_length, new_site_name.c_str());
			if (op == argument::update_)
				Log_Recorder::add_log(Order::get(), "�ٲٱ� ���� ����Ʈ �̸� : " + before_site_name);
		}
		else
			strcpy_s(this->site_name, option::buffer::site_name_length, error_expression::abnormal_Site_site_name.c_str());
	}
	else { /*    return error_expression::translation_error;    */
		cout << what_attribute << err_exp::msg_undefined_site_attribute << endl;
	}
}
void Site::update_account_attribute(std::string ID, std::string what_attribute, std::string new_value)
{
	Account * temp_account = find_account_with_ID(ID);
	try {
		if (temp_account == nullptr)
			throw err_exp::msg_no_existing_ID;
		if (expression::Translation::account_attribute_translate(what_attribute) == "ID")
		{
			if (is_redundancy_ID(new_value) == true)
				throw new_value + err_exp::msg_already_existing_ID;
		}
	}
	catch (std::string error_message) {
		std::cout << error_message << std::endl;
		return;
	}
	temp_account->update_attribute(what_attribute, new_value);
}