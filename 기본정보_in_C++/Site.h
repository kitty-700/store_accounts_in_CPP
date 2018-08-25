#pragma once
#ifndef _SITE_H_ 
#define _SITE_H_ 
#include <list>
#include <string>
#include <cstring>
#include <windows.h>
#include "Options.h"
#include "Account.h"
#include "Log_Recorder.h"
#include "Order.h"
#include "Natural_language.h"

class Site {
	friend class Importer;
	friend class Exporter;
	int account_count;
	std::list<Account*> accounts;
	char site_name[buffer::site_name_length];
private:
	bool is_proper_string(std::string what_attribute, std::string str) const;

	bool is_redundancy_ID(std::string ID);
public:
	Site();
	~Site();
	void operator+=(Account * account);
	std::string get_site_name();
	int get_account_count() const;
	void show_account_information();
	Account * find_account_with_ID(std::string ID);
	Account * find_account_with_account_number(int account_number);
	Account* add_account(std::string ID, std::string PW, std::string memo);
	void del_account(std::string ID);
	void update_account_attribute(std::string ID, std::string what_attribute, std::string new_value);
	void update_site_name(std::string what_attribute, std::string new_site_name);
	void clean_itself();
};
#endif