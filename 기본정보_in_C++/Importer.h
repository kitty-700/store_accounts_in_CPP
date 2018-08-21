#pragma once
#ifndef _IMPORTER_H_
#define _IMPORTER_H_ 
#include <fstream>
#include <iostream>
#include <string>

#include "Options.h"
#include "Information_Organizing_Class.h"
#include "Status.h"
class Importer { //순전히 file 을 가지고 person을 만들기 위한 클래스. 파일 이름을 입력받아 동작한다.
	std::string load_file_name;

	std::ifstream fp;
	Person * temp_person;
	Site * temp_site;
	Account * temp_account;
	std::string temp_str;

	int state_was;

	char * data;
	int data_size;
	int di; //data index

	bool is_file_exist;

private:
	void get_data_size();
	void show_now_data();
	void load_raw_data();
	void decrypt();
	void boot_load(bool * load_start, bool * op_active);
	bool assembly(bool * op_active, bool * is_successful);
	bool is_proper_transition(const int before_state, const int now_state);
	bool change_state(bool * is_successful);
	bool fill_proper_place(const int state_was);
	bool is_person_initialized_well_with_raw_data();
	void make_a_person();
public:
	Importer(std::string load_file_name); //Order_interpreter의 생성자와는 달리 기본 파일명 같은건 없다.
	~Importer(); //person을 초기화하고 남은 data를 삭제한다.
	Person * return_person();
};
#endif