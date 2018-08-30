#pragma once
#ifndef _ORDER_FORM_FILLER_H_
#define _ORDER_FORM_FILLER_H_
#include<iostream>
#include<string>

#include"Options.h"
#include"Order.h"
#include"Information_Organizing_Class.h"
#include"Order_Form_Filler_Exception.h"
#include"Structs.h"
class Form_Filling_Exception;
class Order_Form_Filler {
	Person * person;

	std::string selection;
	int selection_1;
	int selection_2;
	int selection_3;

public:
	Order_Form_Filler(Person * person);

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
	//1.예외처리
	void exception_no_sites(int site_count);
	void exception_no_input(int selection);
	void exception_no_input(std::string selection);
	void exception_zero_to_quit(int selection);
	void exception_range_out(int select, int count);
	//2. 0번 선택에 관한 설명
	void zero_selection_explain(std::string sentence);
	void zero_selection_explain(std::string sentence, Site * site);
	//3. 색깔있는 출력
	void print_colored_site_name(Site *site);
	void print_colored_account_attributes(Account *account);
	void print_colored_account_attribute(Account *account, std::string attribute);
	//4. 메뉴 출력
	void menu_print(const bool line_devide, std::string sign);
	//5. 입력 함수
	void input_string(const bool change, std::string&str, const std::string message = "");
	void input_number(int * number, const std::string message);
	//and so on
	bool is_within_count_range(int select, int count);
	


};
#endif