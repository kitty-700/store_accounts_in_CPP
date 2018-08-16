#pragma once
#ifndef _ADD_H_
#define _ADD_H_
namespace option {
	namespace argument {
		namespace instruction {
			namespace add {
				/*
				(인자 2) add naver : "naver라는 사이트를 추가한다."
				(인자 4) add naver tempID pasw123123 :
				"naver라는 사이트에 ID가 tempID이고 PW가 pasw123123인 계정을 추가한다."
				(인자 5) add naver tempID pasw123123 no_memo :
				"naver라는 사이트에 ID가 tempID이고 PW가 pasw123123이고 메모가 no_memo 인 계정을 추가한다."
				*/
				enum control { //Order_token 구조체의 token_count 를 통해 무슨 함수를 실행할지 제어한다.
					add_form_use = 1,
					add_site_only = 2,
					add_account_without_memo = 4,
					add_account_with_memo = 5
				};
				enum argument_position {
					new_site_name_position = 1,	//추가할 사이트 이름의 인덱스
					new_id_position = 2,				//추가할 ID 의 인덱스
					new_pw_position = 3,				//추가할 패스워드의 인덱스
					new_memo_position = 4			//추가할 메모의 인덱스 
				};
			}//namespace add
		}//namespace instruction
	}//namespace argument
}//namespace option
#endif // !_ADD_H_
