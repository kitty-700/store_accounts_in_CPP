#pragma once
#ifndef _ARGUMENT_H_
#define _ARGUMENT_H_
#include <string>
namespace option {
	namespace argument { //Structs.h �� ���ǵ� Order_token ����ü�� �����ϱ� ���� �����ѹ��� ��Ƶξ���.
#define type token_count
#define each_argument token_count
#define content tokens
		static const char forbidden_chars[] = {
			'#','$','%'
		};
		namespace package {
			static const std::string no_package_detected = "";
			enum package_standard_handler { kinds_of_tip = 6, left_tip = 0, right_tip = 1, target_argument = 0 };
			static const char package_standard[2][kinds_of_tip] = {
				{ '\'' , '\"' , '{' , '[' , '(' , '<' },
			{ '\'' , '\"' , '}' , ']' , ')' , '>' }
			};
		}
		enum { //etc
			operation_position = 0, //add, del, update ����  ��ɾ� ������ ��Ÿ���� �ε���
			argument_limit = 5, /*����� ���ڴ� �ִ� 5�� ����*/
			no_arg = 0,
			too_much_args = 999999,
		};
		enum form {
			zero_selection = 0
		};
		enum order_type {
			show_site_list_ = 0,
			add_ = 1,
			del_ = 2,
			update_ = 3,
			help_ = 4,
			show_one_site_information_with_number_ = 5,
			show_one_site_information_with_site_name_ = 6,
			show_all_site_information_ = 7,
			save_ = 8,
			load_ = 9,
			reload_ = 10,
			clear_screen_ = 11,
			log_ = 12,
			exit_ = -1,
			no_operation_input_ = -2,
			not_translate_but_should_calculated_ = -3 //�ܼ��� �ڿ���θ� �����Ǵ°� �ƴ϶� ���Ǿ�� �� �� �ִ� ��ɾ��� ���
		};
	}//namespace argument
}//option
#endif