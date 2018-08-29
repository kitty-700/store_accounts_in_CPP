#include "Module_Tester.h"
Person* Module_tester::person;
void Module_tester::module_test()
{
	std::cout << ">> MODULE TESTING <<" << std::endl;
	Site * site = Module_tester::person->find_Site(1);
	Account * account = site->find_account_with_account_number(1);
	std::cout << *account;
}

void Module_tester::init()
{
	Module_tester::init_person();
}

void Module_tester::exit()
{
	delete Module_tester::person;
}

void Module_tester::add_account(Site * site, std::string ID, std::string PW, std::string memo)
{
	Account * temp_acc = new Account();
	strcpy_s(temp_acc->ID, ID.c_str());
	strcpy_s(temp_acc->PW, PW.c_str());
	strcpy_s(temp_acc->memo, memo.c_str());
	*site += temp_acc;
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
	temp_site = make_site("naver");
	{
		add_account(temp_site, "dummy_id1", "dummypw_1", "dummy_memo1");
		add_account(temp_site, "dummy_id2", "dummypw_2", "dummy_memo2");
		add_account(temp_site, "dummy_id3", "dummypw_3", "dummy_memo3");
		add_account(temp_site, "dummy_id4", "dummypw_4", "dummy_memo4");
		*Module_tester::person += temp_site;
	}
	temp_site = make_site("daum");
	{
		add_account(temp_site, "dummy_id1", "dummypw_1", "dummy_memo1");
		add_account(temp_site, "dummy_id2", "dummypw_2", "dummy_memo2");
		add_account(temp_site, "dummy_id3", "dummypw_3", "dummy_memo3");
		add_account(temp_site, "dummy_id4", "dummypw_4", "dummy_memo4");
		*Module_tester::person += temp_site;
	}
	temp_site = make_site("nexon");
	{
		add_account(temp_site, "dummy_id1", "dummypw_1", "dummy_memo1");
		add_account(temp_site, "dummy_id2", "dummypw_2", "dummy_memo2");
		*Module_tester::person += temp_site;
	}
}