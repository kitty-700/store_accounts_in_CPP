#pragma once
#ifndef _UPDATE_H_
#define _UPDATE_H_
namespace option {
	namespace argument {
		namespace instruction {
			namespace update {
				/*
				(인자 3) update naver Naver : "naver라는 사이트 이름을 Naver로 바꾼다."
				(인자 5) update Naver tempID PW pasw123123 :
				"Naver라는 사이트에 tempID라는 ID를 가진 계정의 패스워드를 pasw123123으로 변경한다."
				*/
				enum control { //Order_token 구조체의 token_count 를 통해 무슨 함수를 실행할지 제어한다.
					modify_form_use = 1,
					modify_site_name = 3,
					modify_account_attribute = 5
				};
				enum argument_position {
					site_name_position = 1,	//이름을 바꿀 사이트의 인덱스
					new_site_name_position = 2,	//바꿀 사이트 이름의 인덱스 
					id_position = 2,						//속성 값을 바꿀 계정의 인덱스 
					attribute_select_position = 3,	//바꾸려는 속성 종류 선택 인덱스
					new_attribute_value_position = 4	//바꾸려는 속성의 새 값 인덱스
				};
			}//namespace update
		}//namespace instruction
	}//namespace argument
}//namespace option
#endif // !_UPDATE_H_
