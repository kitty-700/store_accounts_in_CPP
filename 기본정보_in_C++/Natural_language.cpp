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
