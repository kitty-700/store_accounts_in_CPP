#pragma once
#ifndef _COMPILE_H_
#define _COMPILE_H_
#include <string>

namespace option {
	namespace parameters {
		namespace compile	//컴파일 시마다 바꿔볼수 있을만큼 변경에 따른 리스크는 없다.
		{
			//모듈 테스트
			static const bool do_module_test = false;
			//파일명
			static const std::string default_load_file_name = "AQ.alz";
			static const std::string default_save_file_name = "AQ.alz";
			//암호화 여부
			static const bool active_encryption = true; //at Export
			static const bool active_decryption = true; //at Import
			//JUNK byte 붙이기.  한번 붙일 때마다 min~max 만큼의 바이트 수 중 랜덤 갯수로 붙인다.
			static const bool generate_junk_bytes = true;
			static const int max_junk_bytes = 500000;
			static const int min_junk_bytes = 250000; //max보다 크지 않아야 한다.
			//로그인
			static const bool pass_char_ipnut = false;	//이 프로그램을 쓸 줄 아는지에 대한 것만 파악
			static const char pass_char = 'a';

			static const bool require_additional_password = false;	 //그 외에 추가로 비밀번호 입력
			static const std::string then_password = "bc";
			enum login_status { login_success = 0, login_fail = 1 };
			//암호화 관련
			static const char xor_factor = '#';
			//프로그램 출처 표시 관련
			static const bool is_show_the_source = true;
			static const std::string source_message = "KNU";
			//디버깅옵션
			namespace debug
			{
				static const bool order_tokenizer = false;
				static const bool load_raw_data = false;
			}// namespace debug
		} // namespace compile
	}// namespace parameters
}// namespace option
#endif