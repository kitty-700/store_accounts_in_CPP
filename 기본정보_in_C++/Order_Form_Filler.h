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

	std::string selection;
	int selection_1;
	int selection_2;
	int selection_3;

public:
	Order_Form_Filler(Person * person);

	//XXXX_form_filler() ���� false�� ��ȯ�� ���, ����� �� order ����� ������ �������� �ǹ��ϸ�, ���� �̿� ���� ����� �������� �ʴ´�.
	bool add_form_filler(Order_token * order);///
	bool del_form_filler(Order_token * order);///
	bool update_form_filler(Order_token * order);///

private:
	void add_new_site(Order_token * order);
	bool add_new_account(Order_token * order);

	bool del_site(Order_token * order);
	bool del_account(Order_token * order);

	bool update_site_name(Order_token * order);
	bool update_account_attribute(Order_token * order);

};
#endif