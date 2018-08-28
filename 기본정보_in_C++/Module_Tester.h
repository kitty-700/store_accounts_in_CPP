#pragma once
#ifndef _MODULE_TESTER_H_
#define _MODULE_TESTER_H_
#include <iostream>
#include <string>
#include <list>
#include <stack>
#include "Options.h"
#include "Information_Organizing_Class.h"

class Module_tester {
	static Person  * person;

	static Account * make_account(std::string ID, std::string PW, std::string memo);
	static Site* make_site(std::string site_name);
	static void init_person();
public:
	static void init();
	static void exit();
	static void module_test();
};
#endif