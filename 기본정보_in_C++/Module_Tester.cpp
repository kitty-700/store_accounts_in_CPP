#include "Module_Tester.h"
Person* Module_tester::person;
void Module_tester::module_test()
{
	system("mode con:cols=100 lines=20");

}

void Module_tester::init()
{
	Module_tester::init_person();
}

void Module_tester::exit()
{
	delete Module_tester::person;
}

Account * Module_tester::make_account(std::string ID, std::string PW, std::string memo)
{
	Account * temp_acc = new Account();
	strcpy_s(temp_acc->ID, ID.c_str());
	strcpy_s(temp_acc->PW, PW.c_str());
	strcpy_s(temp_acc->memo, memo.c_str());
	return temp_acc;
}

Site * Module_tester::make_site(std::string site_name)
{
	Site * temp_site = new Site();
	strcpy_s(temp_site->site_name, site_name.c_str());
	return temp_site;
}

void Module_tester::init_person()
{
	Module_tester::person = new Person();
	Module_tester::person->set_is_alive(true);
	Site * temp_site;
	Account * temp_acc;
	temp_site = make_site("naver");
	{
		temp_acc = make_account("dummy_id1", "dummypw_1", "dummy_memo1");
		*temp_site += temp_acc;
		temp_acc = make_account("dummy_id2", "dummypw_2", "dummy_memo2");
		*temp_site += temp_acc;
		temp_acc = make_account("dummy_id3", "dummypw_3", "dummy_memo3");
		*temp_site += temp_acc;
		temp_acc = make_account("dummy_id4", "dummypw_4", "dummy_memo4");
		*temp_site += temp_acc;
		*Module_tester::person += temp_site;
	}
	temp_site = make_site("daum");
	{
		temp_acc = make_account("dummy_id1", "dummypw_1", "dummy_memo1");
		*temp_site += temp_acc;
		temp_acc = make_account("dummy_id2", "dummypw_2", "dummy_memo2");
		*temp_site += temp_acc;
		temp_acc = make_account("dummy_id3", "dummypw_3", "dummy_memo3");
		*temp_site += temp_acc;
		temp_acc = make_account("dummy_id4", "dummypw_4", "dummy_memo4");
		*temp_site += temp_acc;
		*Module_tester::person += temp_site;
	}
	temp_site = make_site("nexon");
	{
		temp_acc = make_account("dummy_id1", "dummypw_1", "dummy_memo1");
		*temp_site += temp_acc;
		temp_acc = make_account("dummy_id2", "dummypw_2", "dummy_memo2");
		*temp_site += temp_acc;
		*Module_tester::person += temp_site;
	}
}