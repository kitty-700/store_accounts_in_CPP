#pragma once
#ifndef _LOG_RECORDER_H_ 
#define _LOG_RECORDER_H_ 
#include <stack>
#include <vector>
#include <assert.h>
#include "Options.h"
#include "Structs.h"
#include "Status.h"
#include "Log.h"
#include "General_Function.h"
class Log_Recorder {
	static int log_count;
	static std::stack <Log*> logstack;
public:
	~Log_Recorder();
	static void clear_itself();
	static void add_log(const Order_token * order,std::string original_value="");//add
	static void print_log();
	static bool has_log();
	static void order_copy(Order_token * destination_order, const Order_token * source_order);
	static bool continue_although_unsaved();
};
#endif 