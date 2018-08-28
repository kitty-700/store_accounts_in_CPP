#pragma once
#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_ 
#include <iostream>
#include <string>
#include <ctime>
#include "Options.h"
#include "Status.h"
#include "Order.h"
#include "General_Function.h"

class Account {
	friend class Importer; //�̷���, ��ó���� �ٸ� Ŭ���������� ������ �ʱ�ȭ�� �ʿ䰡 ���� �� friend�� �����ѵ� 
	friend class Exporter;
	char ID[option::parameters::buffer::id_length];
	char PW[option::parameters::buffer::password_length];
	char update_time[option::parameters::buffer::update_time_length];	//������ ������Ʈ ����
	char memo[option::parameters::buffer::memo_length];
private:
	bool is_proper_string(std::string what_attribute, std::string str) const;
	void replace_account_update_time(char now_time[option::parameters::buffer::update_time_length]);
public:
	void show_account_information() const;
	std::string get_attribute(std::string what_attribute) const;
	void update_attribute(std::string what_attribute, std::string new_value);//�ٸ� �������� ID�� �ߺ��˻�� Site Ŭ�������� ������...
};
#endif