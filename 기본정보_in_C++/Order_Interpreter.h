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
	friend class Export;
	Person * person;
	Order_token * order;
private:
	int init_person(std::string file_name); //�����ڷκ��� ȣ���
	void add(Order_token* site_name);
	void del(Order_token* site_name);
	void update(Order_token* site_name);
	void show(int what_type_of_showing);
	option::argument::order_type operation_translate(std::string op);
	void show_site_in_number(Order_token* order);
	void show_site_in_site_name(Order_token* order);
public:
	Order_Interpreter();//�����ڿ��� ���� �⺻���� �ҷ����� �����̸��� init_person()�� �����ش�.
	~Order_Interpreter();//�����Ҵ�� person�� �����ϱ� ���� person kill()
	std::string do_order(std::string order);//����ڰ� ���� ����� ������ �� �Լ����� ó���ȴ�.
	//do_order()�� Person ��ü�� �� ��Ȯ�� ����� �������ν� �����ȴ�.
};
#endif