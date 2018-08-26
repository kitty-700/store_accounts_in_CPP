#pragma once
#ifndef _TRANSLATION_H_
#define _TRANSLATION_H_
#include <string>
#include"Options.h"
namespace expression {
		class Translation
		{
		public:
			static std::string site_attribute_translate(std::string str);
			static std::string account_attribute_translate(std::string str);
			static option::argument::order_type operation_translate(std::string query_op);
		};
}//namespace expression 

#endif