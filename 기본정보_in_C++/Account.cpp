#include "Account.h"
using namespace std;
namespace err_exp = error_expression;

bool Account::is_proper_string(std::string what_attribute, std::string str) const
{	// what_attribute 문자열은 translate_natural_language() 를 거침.
	try {
		if (what_attribute == "ID") {
			if (str.size() > buffer::id_length)
				throw err_exp::msg_too_long_account_ID;
			if (str == "")
				throw err_exp::msg_ID_must_be_filled;
		}
		else if (what_attribute == "PW") {
			if (str.size() > buffer::password_length)
				throw err_exp::msg_too_long_account_PW;
			if (str == "")
				throw err_exp::msg_PW_must_be_filled;
		}
		else if (what_attribute == "memo") {
			if (str.size() > buffer::memo_length)
				throw err_exp::msg_too_long_accout_memo; //메모는 공백이어도 된다.
		}
		else
			throw err_exp::msg_undefined_account_attribute;
		namespace arg = option::argument;
		for (int i = 0; i < sizeof(arg::forbidden_chars) / sizeof(char); i++)
			if (str.find(arg::forbidden_chars[i]) != string::npos)
				throw  "계정의 " + what_attribute + "에 " + err_exp::msg_forbidden_character;
	}
	catch (std::string error_message) {
		std::cout << error_message << std::endl;
		return false;
	}
	return true;
}
void Account::replace_account_update_time(char now_time[buffer::update_time_length])
{
	time_t timer = time(NULL);
	struct tm t;
	localtime_s(&t, &timer);
	sprintf_s(now_time, buffer::update_time_length, "%4d-%02d-%02d %02d:%02d:%02d",
		t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
}
void Account::show_account_information() const
{
	cout << "     ID : " << this->ID << endl;
	cout << "     PW : " << this->PW << endl;
	cout << "     UD : " << this->update_time << endl;
	cout << "     MM : ";
	if (!strcmp(this->memo, "") == true)
		cout << compile::msg_null << endl;
	else
		cout << this->memo << endl;
}
void Account::update_attribute(string what_attribute, string new_value)
{
	what_attribute = Natural_language::account_attribute_translate(what_attribute);
	if (what_attribute == "ID") {
		if (is_proper_string(what_attribute, new_value) == true)
		{
			strcpy_s(this->ID, buffer::id_length, new_value.c_str());
		}
		else
			strcpy_s(this->ID, buffer::id_length, error_expression::abnormal_Account_ID.c_str());
	}
	else if (what_attribute == "PW") {
		if (is_proper_string(what_attribute, new_value) == true)
			strcpy_s(this->PW, buffer::password_length, new_value.c_str());
		else
			strcpy_s(this->ID, buffer::id_length, error_expression::abnormal_Account_ID.c_str());
	}
	else if (what_attribute == "memo") {
		if (is_proper_string(what_attribute, new_value) == true)
			strcpy_s(this->memo, buffer::memo_length, new_value.c_str());
		else
			strcpy_s(this->ID, buffer::id_length, error_expression::abnormal_Account_ID.c_str());
	}
	else {  /*    return error_expression::translation_error;    */
		cout << err_exp::msg_undefined_account_attribute << endl;
		return;
	}
	if (Status::get_is_person_loaded() == true)
		replace_account_update_time(this->update_time);
}
string Account::get_attribute(std::string what_info) const
{
	what_info = Natural_language::account_attribute_translate(what_info);
	if (what_info == "ID")
		return string(this->ID);
	else if (what_info == "PW")
		return string(this->PW);
	else if (what_info == "memo")
		return string(this->memo);
	else { /*translation_error*/
		cout << err_exp::msg_undefined_account_attribute << endl;
		return nullptr;
	}
}