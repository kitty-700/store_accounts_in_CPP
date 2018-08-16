#include "Natural_language.h"
namespace err_exp = option::error_expression;
std::string Natural_language::site_attribute_translate(std::string str)
{	//site attribute (��� �ϳ����� �Ӽ�)
	const std::string site_name_similary[] = \
	{ "site_name", "Site_name", "Site_Name", "SITE_NAME", "sitename", "SITENAME", "SN" };
	for (int i = 0; i < sizeof(site_name_similary) / sizeof(std::string); i++)
		if (str == site_name_similary[i])
			return "site_name";
	return err_exp::translation_error;
}

std::string Natural_language::account_attribute_translate(std::string str)
{	//account_attribute. (�ٸ� UD�� ���Ƿ� �ٲ� �� �����Ƿ� ���⼭ �����Ѵ�.)
	const std::string ID_similary[] = \
	{ "ID", "id", "Id", "Identifier","���̵�","�Ƶ�"};
	const std::string PW_similary[] = \
	{ "PW", "PASSWORD", "PASSWD", "pw", "password", "passwd" ,"��й�ȣ","���"};
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
