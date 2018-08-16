#pragma once
#ifndef _ORDER_TOKEN_REFINER_H_
#define _ORDER_TOKEN_REFINER_H_
#include <string>
#include <cstring>
#include <iostream>

#include"Options.h"
#include "Structs.h"
class Order_Token_Refiner { //�� ���ڿ� ������ ����� Order_token����ü ������� ��ūȭ�ϴ� Ŭ����.
	Order_token* order_token; 	//�� Ŭ�������� �����Ҵ�Ǿ 

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