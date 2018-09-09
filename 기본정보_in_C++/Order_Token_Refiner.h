#pragma once
#ifndef _ORDER_TOKEN_REFINER_H_
#define _ORDER_TOKEN_REFINER_H_
#include <string>
#include <cstring>
#include <iostream>
#include <assert.h>

#include"Options.h"
#include"General_Function.h"
#include "Structs.h"
class Order_Token_Refiner { //�� ���ڿ� ������ ����� Order_token����ü ������� ��ūȭ�ϴ� Ŭ����.
	Order_token* order; 	//�� Ŭ�������� �����Ҵ�Ǿ 

	std::string extract_package(std::string order);
	std::string unpackaging(std::string arg);
	std::string left_trim(std::string str);
	void order_tokenizer(std::string left_order);
public:
	Order_Token_Refiner(Order_token * order_token);
	Order_token * refining(std::string order);
	//�����ε� �� ��ġ��
	Order_token * refining(std::string arg1, std::string arg2, std::string arg3="", std::string arg4="", std::string arg5="");
	Order_token * get_order_token() const;
};
#endif