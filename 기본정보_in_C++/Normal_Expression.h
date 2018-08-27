#pragma once
#ifndef _NORMAL_EXPRESSION_H_
#define _NORMAL_EXPRESSION_H_
#include <string>
namespace option {
	namespace expression
	{
		namespace normal
		{
			static const std::string thick_line = "==============================";
			static const std::string thin_line = "------------------------------";
			static int index_fix = 1;
			static int null_fix = 1;
			static char char_to_int_fix = '0';
			static const std::string msg_null = "(null)";
			static const std::string msg_no_special_thing = "";
			static const bool no_exit = false;
		}// namespace normal_expression
	}
}//namespace option
#endif
