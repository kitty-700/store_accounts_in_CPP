#include "Natural_language.h"
namespace err_exp = option::error_expression;
std::string Natural_language::site_attribute_translate(std::string str)
{	//site attribute (사실 하나뿐인 속성)
	const std::string site_name_similary[] = \
	{ "site_name", "Site_name", "Site_Name", "SITE_NAME", "sitename", "SITENAME", "SN" };
	for (int i = 0; i < sizeof(site_name_similary) / sizeof(std::string); i++)
		if (str == site_name_similary[i])
			return "site_name";
	return err_exp::translation_error;
}

std::string Natural_language::account_attribute_translate(std::string str)
{	//account_attribute. (다만 UD는 임의로 바꿀 수 없으므로 여기서 제외한다.)
	const std::string ID_similary[] = \
	{ "ID", "id", "Id", "Identifier","아이디","아디"};
	const std::string PW_similary[] = \
	{ "PW", "PASSWORD", "PASSWD", "pw", "password", "passwd" ,"비밀번호","비번"};
	const std::string Memo_similary[] = \
	{ "Memo", "MEMO", "memo" };
	for (int i = 0; i < sizeof(ID_similary) / sizeof(std::string); i++)
		if (str == ID_similary[i])
			return "ID";
	for (int i = 0; i < sizeof(PW_similary) / sizeof(std::string); i++)
		if (str == PW_similary[i])
			return "PW";
	for (int i = 0; i < sizeof(Memo_similary) / sizeof(std::string); i++)
		if (str == Memo_similary[i])
			return "memo";
	return err_exp::translation_error;
}

argument::order_type Natural_language::operation_translate(std::string query_op)
{
	namespace arg = argument;
	arg::order_type interpreted_op;
	if (query_op == "exit"
		|| query_op == "-1")
		interpreted_op = arg::order_type::exit_;

	else if (query_op == "show"
		|| query_op == "ls")
		interpreted_op = arg::order_type::show_site_list_;

	else if (query_op == "all"
		|| query_op == "ll")
		interpreted_op = arg::order_type::show_all_site_information_;

	else if (query_op == "add"
		|| query_op == "ADD"
		|| query_op == "+")
		interpreted_op = arg::order_type::add_;

	else if (query_op == "del"
		|| query_op == "DELETE"
		|| query_op == "delete"
		|| query_op == "remove"
		|| query_op == "rm"
		|| query_op == "-")
		interpreted_op = arg::order_type::del_;

	else if (query_op == "cls"
		|| query_op == "clear")
		interpreted_op = arg::order_type::clear_screen_;

	else if (query_op == "update"
		|| query_op == "UPDATE"
		|| query_op == "Update"
		|| query_op == "udt")
		interpreted_op = arg::order_type::update_;

	else if (query_op == "save"
		|| query_op == "SAVE"
		|| query_op == "Save"
		|| query_op == "store")
		interpreted_op = arg::order_type::save_;

	else if (query_op == "load"
		|| query_op == "Load"
		|| query_op == "LOAD")
		interpreted_op = arg::order_type::load_;

	else if (query_op == "reload"
		|| query_op == "Reload")
		interpreted_op = arg::order_type::reload_;

	else if (query_op == "help")
		interpreted_op = arg::order_type::help_;

	else
		interpreted_op = arg::order_type::not_translate_but_should_calculated_;

	return interpreted_op;
}