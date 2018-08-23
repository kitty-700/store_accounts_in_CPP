#pragma once
#ifndef _ORDER_FORM_FILLER_H_
#define _ORDER_FORM_FILLER_H_
#include<iostream>
#include<string>

#include"Options.h"
#include"Information_Organizing_Class.h"
#include"Structs.h"
class Order_Form_Filler {
	Person * person;
	Order_token * order;

	std::string selection;
	int selection_1;
	int selection_2;
	int selection_3;

public:
	Order_Form_Filler(Person * person, Order_token * order);

	void add_form_filler();
	void del_form_filler();
	void update_form_filler();
	void load_form_filler();

private:
	void add_new_site();
	void add_new_account(Site * site);

	void del_site(Site * site);
	void del_account(Site * site);

	void update_site_name(Site * site);
	void update_account_attribute(Site * site);

	//////////////////////////////////////뒷받침되는 함수들
	bool exception_no_sites(int site_count);
	void exception_no_input(int selection);
	void exception_no_input(std::string selection);
	void exception_zero_to_quit(int selection);
	void exception_range_out(int select, int count);

	void zero_selection_explain(std::string sentence);
	void zero_selection_explain(std::string sentence, Site * site);
	void print_colored_site_name(Site *site);
	void print_colored_account_attributes(Account *account);
	void print_colored_account_attribute(Account *account, std::string attribute);
	bool is_count_range(int select, int count);
};
#endif