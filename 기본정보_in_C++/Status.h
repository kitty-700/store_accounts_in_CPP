#pragma once
#ifndef _STATUS_H_ 
#define _STATUS_H_ 
#include"Options.h"
#include"Structs.h"
#include"Log_Recorder.h"
class Status {	//protect�ؼ� ��ӽ�Ű�°� ���?
	static bool is_person_loaded;
	static bool is_form_filling_successful;
	//static ������ �߰���ų ���� cpp ���Ͽ��� �ʱ�ȭ���ش�.
public:
	static bool get_is_person_loaded();
	static void set_is_person_loaded(bool is_person_loaded);
	static bool get_is_form_filling_successful();
	static void set_is_form_filling_successful(bool is_form_filling_successful);
};
#endif