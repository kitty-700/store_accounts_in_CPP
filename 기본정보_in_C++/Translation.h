#pragma once
#ifndef _TRANSLATION_H_
#define _TRANSLATION_H_
#include <string>
#include "Expression.h"
#include "Argument.h"
//여기서 Option을 include 해버리면 순환호출이 되어버림.
namespace option {
	namespace expression {
		class Translation
		{
		public:
			static std::string site_attribute_translate(std::string str);
			static std::string account_attribute_translate(std::string str);
			static argument::order_type operation_translate(std::string query_op);
		};
	}//namespace expression 
}//namespace option 

#endif