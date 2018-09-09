#pragma once
#ifndef _LOG_RECORDER_H_ 
#define _LOG_RECORDER_H_ 
#include <stack>
#include <vector>
#include <assert.h>
#include "Options.h"
#include "Structs.h"
#include "Status.h"
#include "Log_Set.h"
#include "General_Function.h"
class Site;
class Log_Recorder {
	static int log_count;
	static std::stack <Log*> undo_stack;
	static std::stack <Log*> redo_stack;
public:
	~Log_Recorder();
	static void clear_itself();

	static Log* pre_recording_procedure();
	static void after_recording_procedure(Log * log);

	static void record_add_site(std::string site_name);
	static void record_add_account(std::string site_name, std::string account_ID);

	static void record_del_site(Site * site);
	static void record_del_account(std::string site_name, std::string account_ID);

	static void record_update_site_name(std::string site_name, std::string account_ID, std::string original);
	static void record_update_account_attribute(std::string site_name, std::string account_ID, std::string attribute, std::string original);

	static void print_log();
	static bool has_log();
	static bool continue_although_unsaved();
};
#endif 