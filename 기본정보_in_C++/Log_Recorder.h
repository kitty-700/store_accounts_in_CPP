#pragma once
#ifndef _LOG_RECORDER_H_ 
#define _LOG_RECORDER_H_ 
#include <stack>
#include <vector>
#include <assert.h>
#include "Structs.h"
#include "General_Function.h"
class Log_Recorder {
	int log_count;
	std::stack <Log*> logstack;
public:
	void add_log(const Order_token * order,std::string original_value);
	void print_log();
};
#endif