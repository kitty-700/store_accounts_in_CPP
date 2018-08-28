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
	friend class Importer; //이렇게, 맨처음에 다른 클래스에의해 강제로 초기화될 필요가 있을 때 friend는 유용한듯 
	friend class Exporter;
	char ID[option::parameters::buffer::id_length];
	char PW[option::parameters::buffer::password_length];
	char update_time[option::parameters::buffer::update_time_length];	//마지막 업데이트 일자
	char memo[option::parameters::buffer::memo_length];
private:
	bool is_proper_string(std::string what_attribute, std::string str) const;
	void replace_account_update_time(char now_time[option::parameters::buffer::update_time_length]);
public:
	void show_account_information() const;
	std::string get_attribute(std::string what_attribute) const;
	void update_attribute(std::string what_attribute, std::string new_value);//다만 고유값인 ID의 중복검사는 Site 클래스에서 해주자...
};
#endif