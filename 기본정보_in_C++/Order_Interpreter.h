#pragma once
#ifndef _ORDER_INTERPRETER_H_
#define _ORDER_INTERPRETER_H_
#include <string>
#include <cstring>
#include <windows.h>

#include "Options.h"
#include "Order.h"
#include "Order_Token_Refiner.h"
#include "Order_Form_Filler_Exception.h"
#include "Order_Form_Filler.h"
#include "File_IO_Class.h"
#include "Module_Tester.h"
#include "Status.h"
#include "Structs.h"
#include "General_Function.h"

class Person;
class Order_Interpreter {
	Person * person;
	std::string now_loaded_file_name;
private:
	bool init_person(std::string file_name); //�����ڷκ��� ȣ���
	void init_person_success_action(std::string loaded_file_name); //�����ڷκ��� ȣ���
	void add(Order_token * order);
	void del(Order_token * order);
	void update(Order_token * order);
	void load(Order_token * order);
	void sort(bool is_ascending);
	void show(int what_type_of_showing);
	void show_site_in_number();
	void show_site_in_site_name();
	bool change_person(Person * person_to_change);
	void order_forwarding(Order_token * order, argument::order_type op, bool * is_exit);
	void wanna_filling_sometimse(Order_token * order, argument::order_type op);
	void exit_precess(bool * is_exit);
	option::argument::order_type operation_translate(std::string query_op);
public:
	Order_Interpreter();//�����ڿ��� ���� �⺻���� �ҷ����� �����̸��� init_person()�� �����ش�.
	~Order_Interpreter();//�����Ҵ�� person�� �����ϱ� ���� person kill()
	bool interprete_order(Order_token * order);//�ڡڡڡڻ���ڰ� ���� ����� ������ �� �Լ����� ó���ȴ�.
	std::string get_loaded_file_name();
	//do_order()�� Person ��ü�� �� ��Ȯ�� ����� �������ν� �����ȴ�.
};
#endif