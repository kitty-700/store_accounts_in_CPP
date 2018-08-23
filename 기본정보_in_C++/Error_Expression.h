#pragma once
#ifndef _ERROR_EXPRESSION_H_
#define _ERROR_EXPRESSION_H_
#include <string>
#include "Buffer.h"
namespace option {
	namespace error_expression
	{	//std::string error_answer / error_message
		/*//보통의 catch문
		catch (std::string error_message) { 
		std::cout << error_message << std::endl;
		return;
		}
		*/
		//arg
		static const std::string msg_too_much_args = "인자가 너무 많습니다.";
		static const std::string msg_not_defined_operation = "그런 명령어는 없습니다.";
		static const std::string msg_unsupport_order_form = "명령어는 존재하지만, 지원하지 않는 명령 양식입니다..";
		static const std::string msg_forbidden_character = "금지된 특수 문자 입력를 입력하셨습니다.";
		//Person
		static const std::string msg_person_hasnt_site = "아무 사이트도 등록되어있지 않습니다.";
		//Site
		static const std::string abnormal_Site_site_name= "#$SN";
		static const std::string msg_site_name_must_be_filled = "사이트 이름은 공백이어서는 안 됩니다.";
		static const std::string msg_undefined_site_attribute = "Site 에 그런 속성은 없습니다..";
		static const std::string msg_cant_make_site = "Site 를 만들 수 없습니다.";
		static const std::string msg_already_existing_site_name = "은(/는) 이미 존재하는 사이트 이름입니다.";
		static const std::string msg_no_existing_site_number = "그런 번호를 가진 사이트는 없습니다.";
		static const std::string msg_no_existing_site_name = "그런 이름를 가진 사이트는 없습니다.";
		static const std::string msg_site_hasnt_account = "사이트에 아무런 계정도 없습니다.";
		static const std::string msg_too_long_site_name =
			"입력한 사이트 이름의 길이가 너무 깁니다.  ( " + std::to_string(buffer::site_name_length) + " 자 이하로..)";
		//Account
		static const std::string abnormal_Account_ID = "#$ID";
		static const std::string msg_undefined_account_attribute = "Account 에 그런 속성은 없습니다..";
		static const std::string msg_no_existing_ID = "그런 ID는 없습니다.";
		static const std::string msg_ID_must_be_filled = "ID 는 공백이어서는 안 됩니다.";
		static const std::string msg_PW_must_be_filled = "PW 는 공백이어서는 안 됩니다.";
		static const std::string msg_already_existing_ID = "은(/는) 이미 존재하는 ID입니다.";
		static const std::string msg_no_existing_account_number = "그런 번호를 가진 계정은 없습니다.";
		static const std::string msg_too_long_account_ID =
			"입력한 계정의 ID의 길이가 너무 깁니다.  ( " + std::to_string(buffer::id_length) + " 자 이하로..)";
		static const std::string msg_too_long_account_PW =
			"입력한 계정의 Password의 길이가 너무 깁니다.  ( " + std::to_string(buffer::password_length) + " 자 이하로..)";
		static const std::string msg_too_long_accout_memo =
			"입력한 계정의 memo 의 길이가 너무 깁니다.  ( " + std::to_string(buffer::memo_length) + " 자 이하로..)";
		//translation
		static const std::string translation_error = "TRANSLATION FAIL";
		//file_io
		static const std::string msg_file_doesnt_exist = "그런 파일 없습니다.";
		static const std::string msg_wrong_file_detected = "파일은 존재하지만 내용이 잘못되어 불러오지 못했습니다.";
		static const std::string msg_string_in_file_was_too_long = "파일 내에서의 문자열들의 길이가 너무 깁니다.";
		static const std::string msg_job_reset_warning = "파일을 다시 적재하기 전에 현재까지의 내용을 저장하지 않으면 작업하던 것들이 사라집니다.";
		//answer
		static const std::string msg_no_special_thing = "";
		static const std::string msg_no_order_input = "";
		//form fill
		static const std::string msg_no_input_form_filling_cancel = "아무 입력도 없으므로 동작을 취소합니다.";
		static const std::string msg_form_filling_cancel = "동작을 취소합니다.";
		static const std::string msg_ineffective_select = "선택지에 없습니다.";
		//string to int
		enum convert_error{
			string_to_be_int_wasnt_entered = -999
		};
	}// namespace error_expression
}//namespace option
#endif
