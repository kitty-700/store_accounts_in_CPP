#pragma once
#ifndef _ORDER_INTERPRETER_H_
#define _ORDER_INTERPRETER_H_
#include <string>
#include <cstring>
#include <windows.h>

#include"Options.h"
#include"Order.h"
#include "File_IO_Class.h"
#include "Status.h"
#include "Structs.h"
#include "General_Function.h"
#include "Order_Token_Refiner.h"
#include "Order_Form_Filler.h"

class Person;
class Order_Interpreter {
	Person * person;
	std::string now_loaded_file_name;
private:
	bool init_person(std::string file_name); //생성자로부터 호출됨
	void init_person_success_action(std::string loaded_file_name); //생성자로부터 호출됨
	void add();
	void del();
	void update();
	void load();
	void show(int what_type_of_showing);
	void show_site_in_number();
	void show_site_in_site_name();
	bool change_person(Person * person_to_change);
public:
	Order_Interpreter();//생성자에선 단지 기본으로 불러들일 파일이름만 init_person()에 던져준다.
	~Order_Interpreter();//동적할당된 person을 제거하기 위해 person kill()
	std::string excute_order(std::string order);//사용자가 내린 명령은 실제로 이 함수에서 처리된다.
	option::argument::order_type operation_translate(std::string query_op);
	//do_order()는 Person 객체에 더 정확한 명령을 내림으로써 구현된다.
};
#endif