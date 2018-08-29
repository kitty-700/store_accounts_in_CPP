#pragma once
#ifndef _ORDER_FORM_FILLER_EXCEPTION_H_
#define _ORDER_FORM_FILLER_EXCEPTION_H_
#include<iostream>
#include"Status.h"
class Form_Filling_Exception {
	std::string error_message;
public:
	Form_Filling_Exception(std::string error_message) : error_message(error_message) {	}
	void error_reporting() {
		Status::set_is_form_filling_successful(false);
		std::cout << this->error_message << std::endl;
	}
};
#endif