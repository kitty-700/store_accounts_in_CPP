#pragma once
#ifndef _STATUS_H_ 
#define _STATUS_H_ 
#include"Options.h"
class Status {	//protect해서 상속시키는건 어떨까?
	static bool is_person_loaded;
	static bool is_argument_input;
	//static 변수를 추가시킬 때는 cpp 파일에서 초기화해준다.
public:
	static bool get_is_person_loaded();
	static void set_is_person_loaded(bool is_person_loaded);
	static bool get_is_argument_input();
	static void set_is_argument_input(bool is_argument_input);
};
#endif