#include "Account.h"
namespace err_exp = option::expression::error;
namespace buff = option::parameters::buffer;

bool Account::is_proper_string(std::string what_attribute, std::string str) const
{
	try {
		if (what_attribute == "ID") {
			if (str.size() > buff::id_length)
				throw err_exp::msg_too_long_account_ID;
			if (str == "")
				throw err_exp::msg_ID_must_be_filled;
		}
		else if (what_attribute == "PW") {
			if (str.size() > buff::password_length)
				throw err_exp::msg_too_long_account_PW;
			if (str == "")
				throw err_exp::msg_PW_must_be_filled;
		}
		else if (what_attribute == "memo") {
			if (str.size() > buff::memo_length)
				throw err_exp::msg_too_long_account_memo; //메모는 공백이어도 된다.
		}
		else if (what_attribute == "update_time") {
			if (str.size() > buff::update_time_length)
				throw err_exp::msg_too_long_account_update_time; //메모는 공백이어도 된다.
		}
		else
			throw err_exp::msg_undefined_account_attribute;
		namespace arg = option::argument;
		for (int i = 0; i < sizeof(arg::forbidden_chars) / sizeof(char); i++)
			if (str.find(arg::forbidden_chars[i]) != std::string::npos)
				throw  "계정의 " + what_attribute + "에 " + err_exp::msg_forbidden_character;
	}
	catch (std::string error_message) {
		std::cout << error_message << std::endl;
		return false;
	}
	return true;
}
void Account::replace_account_update_time(char now_time[buff::update_time_length])
{
	time_t timer = time(NULL);
	struct tm t;
	localtime_s(&t, &timer);
	sprintf_s(now_time, buff::update_time_length, "%4d-%02d-%02d %02d:%02d:%02d",
		t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
}
void Account::show_accounts() const
{
	std::cout << "     ID : " << this->ID << std::endl;
	std::cout << "     PW : " << this->PW << std::endl;
	std::cout << "     UD : " << this->update_time << std::endl;
	std::cout << "     MM : ";
	if (!strcmp(this->memo, "") == true)
		std::cout << option::expression::normal::msg_null << std::endl;
	else
		std::cout << this->memo << std::endl;
}
void Account::update_attribute(std::string what_attribute, std::string new_value)
{
	what_attribute = option::expression::Translation::account_attribute_translate(what_attribute);
	if (is_proper_string(what_attribute, new_value) == true)
	{
		if (Main_Order::get_opcode() == argument::update_)
			Log_Recorder::pre_recording_procedure();
		if (what_attribute == "ID") {
			std::string before_ID = this->ID;
			strcpy_s(this->ID, buff::id_length, new_value.c_str());
		}
		else if (what_attribute == "PW") {
			std::string before_PW = this->PW;
			strcpy_s(this->PW, buff::password_length, new_value.c_str());
		}
		else if (what_attribute == "memo") {
			std::string before_memo = this->memo;
			strcpy_s(this->memo, buff::memo_length, new_value.c_str());
		}
		else if (what_attribute == "update_time") { //form filling 에서는 의도적으로 update_time 을 수정하는 것을 숨겼다.
			std::string before_update_time = this->update_time;
			strcpy_s(this->update_time, buff::update_time_length, new_value.c_str());
		}
		else {  /*    return error_expression::translation_error;    */
			std::cout << err_exp::msg_undefined_account_attribute << std::endl;
			return;
		}
	}
	else
		strcpy_s(this->ID, buff::id_length, err_exp::abnormal_Account_ID.c_str());
	if (Status::get_is_person_loaded() == true && what_attribute !="update_time")
		replace_account_update_time(this->update_time);
}
std::string Account::get_attribute(std::string what_info) const
{
	what_info = option::expression::Translation::account_attribute_translate(what_info);
	if (what_info == "ID")
		return std::string(this->ID);
	else if (what_info == "PW")
		return std::string(this->PW);
	else if (what_info == "memo")
		return std::string(this->memo);
	else if (what_info == "update_time")
		return std::string(this->update_time);
	else { /*translation_error*/
		std::cout << err_exp::msg_undefined_account_attribute << std::endl;
		return nullptr;
	}
}

std::ostream & operator<<(std::ostream & os, const Account & account)
{
	account.show_accounts();
	return os;
}
