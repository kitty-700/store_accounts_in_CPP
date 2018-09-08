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
	static Person * person;
	static std::string now_loaded_file_name;
private:
	static bool init_person(std::string file_name); //�����ڷκ��� ȣ���
	static void init_person_success_action(std::string loaded_file_name); //�����ڷκ��� ȣ���
	static void add(Order_token * order);
	static void del(Order_token * order);
	static void update(Order_token * order);
	static void load(Order_token * order);
	static void sort(bool is_ascending);
	static void show(int what_type_of_showing);
	static void show_site_in_number();
	static void show_site_in_site_name();
	static bool change_person(Person * person_to_change);
	static void order_forwarding(Order_token * order, argument::order_type op, bool * is_exit);
	static void wanna_filling_sometimse(Order_token * order, argument::order_type op);
	static void exit_precess(bool * is_exit);
	static option::argument::order_type operation_translate(std::string query_op);
public:
	static void init();
	~Order_Interpreter();
	static bool interprete_order(Order_token * order);//�ڡڡڡڻ���ڰ� ���� ����� ������ �� �Լ����� ó���ȴ�.
	static std::string get_loaded_file_name();
	//do_order()�� Person ��ü�� �� ��Ȯ�� ����� �������ν� �����ȴ�.
};
#endif