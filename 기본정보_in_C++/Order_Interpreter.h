#pragma once
#ifndef _ORDER_INTERPRETER_H_
#define _ORDER_INTERPRETER_H_
#include <string>
#include <cstring>
#include <windows.h>

#include"Options.h"
#include "File_IO_Class.h"
#include "Status.h"
#include "Structs.h"
#include "General_Function.h"
#include "Order_Token_Refiner.h"
#include "Order_Form_Filler.h"

class Person;
class Order_Interpreter {
	Person * person;
	Order_token * order;
	std::string now_loaded_file_name;
private:
	bool init_person(std::string file_name); //�����ڷκ��� ȣ���
	void init_person_success_action(std::string loaded_file_name); //�����ڷκ��� ȣ���
	void add(Order_token* order);
	void del(Order_token* order);
	void update(Order_token* order);
	void load(Order_token* order);
	void show(int what_type_of_showing);
	void show_site_in_number(Order_token* order);
	void show_site_in_site_name(Order_token* order);
	bool change_person(Person * person_to_change);
public:
	Order_Interpreter();//�����ڿ��� ���� �⺻���� �ҷ����� �����̸��� init_person()�� �����ش�.
	~Order_Interpreter();//�����Ҵ�� person�� �����ϱ� ���� person kill()
	std::string excute_order(std::string order);//����ڰ� ���� ����� ������ �� �Լ����� ó���ȴ�.
	option::argument::order_type operation_translate(std::string query_op);
	//do_order()�� Person ��ü�� �� ��Ȯ�� ����� �������ν� �����ȴ�.
};
#endif