#pragma once
#ifndef _GENERAL_FUNCTION_H_
#define _GENERAL_FUNCTION_H_
#include <iostream>
#include <assert.h>
#include <conio.h>
#include <string>
#include <cstring>
#include <ctime>
#include <random>

#include"Options.h"
#include "Structs.h"
#include "Console_Color.h"
#include "Log_Recorder.h"
#include "Status.h"
class General_Function {
public:
	static void function_test();
	static bool is_natural_number(std::string str);
	static int string_to_integer(std::string str);
	static int get_cipher(int number);
	static int get_random(int min, int max);
	static bool ask_do_or_not(std::string ask);
	static void order_color_input(std::string &order);
	static std::string sum_of_argv(int argc, char ** argv);
	static void get_string_without_overflow(char *string, const int string_length);
	static int login();
	static void show_order(Order_token * order);
	static void print_thick_line();
	static void print_thin_line();
	static void help();
};
#endif