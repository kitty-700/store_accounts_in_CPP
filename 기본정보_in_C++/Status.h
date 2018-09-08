#pragma once
#ifndef _STATUS_H_ 
#define _STATUS_H_ 
#include"Options.h"
#include"Structs.h"
#include"Log_Recorder.h"
class Status {	//protect해서 상속시키는건 어떨까?
	static bool is_person_loaded;
	static bool is_form_filling_successful;
	//static 변수를 추가시킬 때는 cpp 파일에서 초기화해준다.
public:
	static bool get_is_person_loaded();
	static void set_is_person_loaded(bool is_person_loaded);
	static bool get_is_form_filling_successful();
	static void set_is_form_filling_successful(bool is_form_filling_successful);
};
#endif