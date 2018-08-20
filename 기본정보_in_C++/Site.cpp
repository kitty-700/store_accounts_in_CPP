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
{	//Site 가 지닌, 동적할당한 모든 대상에 대해서 할당 해제한다.
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
{	// what_attribute 문자열은 translate_natural_language() 를 거침.
	try { //1.변경하려는 속성이 site_name이 맞는지, 2.길이가 적절한지, 3. 공백은 아닌지 4.특수문자가 포함되어있지는 않은지
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
				throw "site 이름에 " + err_exp::msg_forbidden_character;
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
		std::cout << count << "]↘" << std::endl;
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
	try { //사이트 내의 ID 중복 체크
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
	//파일로부터 적재 시에 update_time 이 변경되지 않게 함수 내에서 조절한다.
	//이전에 저장된 정보들이 옳다는 가정 하에 바르게 동작한다. (Account::update_attribute () 내에서 경고는 띄워준다.)
	if (temp_account->get_attribute("ID") == error_expression::abnormal_Account_ID)
	{
		delete temp_account;
		return nullptr;
	}
	else {
		*(this) += temp_account;
		return temp_account;
	}
}


void Site::del_account(std::string ID)
{
	for (std::list<Account*>::iterator each = this->accounts.begin(); each != this->accounts.end(); each++)
	{
		if ((*each)->get_attribute("ID") == ID)
		{
			delete (*each);
			this->accounts.erase(each);
			this->account_count--;
			return;
		}
	}
	try { //삭제하려는 ID를 못 찾았을 경우
		throw err_exp::msg_no_existing_ID;
	}
	catch (std::string error_message) {
		std::cout << error_message << std::endl;
		return;
	}
}
void Site::update_site_name(string what_attribute, string new_site_name)
{	//사실 여기에 attribute 하나밖에 필요없는데, Account 클래스랑 모양 비슷하게 맞춘것 뿐임.
	what_attribute = Natural_language::site_attribute_translate(what_attribute);
	if (what_attribute == "site_name") //ID 업데이트
	{
		if (is_proper_string(what_attribute, new_site_name) == true)
			strcpy_s(this->site_name, option::buffer::site_name_length, new_site_name.c_str());
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
		if (Natural_language::account_attribute_translate(what_attribute) == "ID")
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