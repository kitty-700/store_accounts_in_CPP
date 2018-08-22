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
	bool init_person(std::string file_name); //생성자로부터 호출됨
	void init_person_success_action(std::string loaded_file_name); //생성자로부터 호출됨
	void add(Order_token* order);
	void del(Order_token* order);
	void update(Order_token* order);
	void load(Order_token* order);
	void show(int what_type_of_showing);
	option::argument::order_type operation_translate(std::string op);
	void show_site_in_number(Order_token* order);
	void show_site_in_site_name(Order_token* order);
	bool change_person(Person * person_to_change);
public:
	Order_Interpreter();//생성자에선 단지 기본으로 불러들일 파일이름만 init_person()에 던져준다.
	~Order_Interpreter();//동적할당된 person을 제거하기 위해 person kill()
	std::string excute_order(std::string order);//사용자가 내린 명령은 실제로 이 함수에서 처리된다.
	//do_order()는 Person 객체에 더 정확한 명령을 내림으로써 구현된다.
};
#endif