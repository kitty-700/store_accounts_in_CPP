#pragma once
#ifndef _SHOW_H_
#define _SHOW_H_
namespace option {
	namespace argument {
		namespace instruction {
			namespace show {
				/*
				(인자 1) 2 : 두번째 사이트의 계정 정보를 출력한다.
				(인자 1) "naver" : 사이트 이름이 "naver"인 사이트의 계정 정보를 출력한다.
				*/
				enum control { //Order_token 구조체의 token_count 를 통해 무슨 함수를 실행할지 제어한다.
					no_additional_arguments = 1
				};
				enum argument_position {

				};
			}//namespace show
		}//namespace instruction
	}//namespace argument
}//namespace option
#endif // !_SHOW_H_
