#pragma once
#ifndef _STATUS_H_ 
#define _STATUS_H_ 
#include"Options.h"
class Status {	//protect�ؼ� ��ӽ�Ű�°� ���?
	static bool is_person_loaded;
	static bool is_argument_input;
	//static ������ �߰���ų ���� cpp ���Ͽ��� �ʱ�ȭ���ش�.
public:
	static bool get_is_person_loaded();
	static void set_is_person_loaded(bool is_person_loaded);
	static bool get_is_argument_input();
	static void set_is_argument_input(bool is_argument_input);
};
#endif