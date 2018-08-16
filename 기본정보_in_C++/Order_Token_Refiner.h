#pragma once
#ifndef _ORDER_TOKEN_REFINER_H_
#define _ORDER_TOKEN_REFINER_H_
#include <string>
#include <cstring>
#include <iostream>

#include"Options.h"
#include "Structs.h"
class Order_Token_Refiner { //통 문자열 형태의 명령을 Order_token구조체 양식으로 토큰화하는 클래스.
	Order_token* order_token; 	//본 클래스에서 동적할당되어서 

	std::string extract_package(std::string order);
	std::string unpackaging(std::string arg);
	std::string left_trim(std::string str);
	void order_tokenizer(std::string left_order);
public:
	Order_Token_Refiner(Order_token * order_token);
	Order_token * refining(std::string order);
	Order_token * get_order_token() const;
};
#endif