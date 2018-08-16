#pragma once
#ifndef _ORDER_TOKEN_H_
#define _ORDER_TOKEN_H_
#include <string>

#include"Options.h"
typedef struct Order_token{
	int token_count = 0;
	std::string tokens[argument::argument_limit]; 
}Order_token;
#endif