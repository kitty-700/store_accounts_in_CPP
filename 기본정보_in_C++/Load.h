#pragma once
#ifndef _LOAD_H_
#define _LOAD_H_
namespace option {
	namespace argument {
		namespace instruction {
			namespace load {
				/*
				(인자 1) reload : 기본 파일 이름으로 적재를 시도한다.
				(인자 2) reload file_B : file_B 라는 파일로 적재를 시도한다.
				*/
				enum control { //Order_token 구조체의 token_count 를 통해 무슨 함수를 실행할지 제어한다.
					load_in_default_file_name = 1,
					load_in_specific_file_name = 2
				};
				enum argument_position {
					file_name_position = 1,	//새로 적재하고자 하는 파일 이름의 인덱스
				};
			}//namespace load
		}//namespace instruction
	}//namespace argument
}//namespace option
#endif // !_LOAD_H_
