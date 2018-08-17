#pragma once
#ifndef _EXPORTER_H_
#define _EXPORTER_H_ 
#include<iostream>
#include <fstream>
#include <list>
#include <random>

#include "Options.h"
#include "Information_Organizing_Class.h"
#include "General_Function.h"

class Exporter {
	Person * person_to_export;

	std::ofstream fp;
	std::string temp_string;
	void junk_byte_input();
	void person_byte_input();
	void site_byte_input(Site * temp_site);
	void encrypt(std::string& data);
	void encrypt(char* data);
	void put_on_file(char data);
	void account_byte_input(Account * temp_account);
public:
	Exporter(Person * person);
	void save();
};
#endif