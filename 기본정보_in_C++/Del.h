#pragma once
#ifndef _DELETE_H_
#define _DELETE_H_
namespace option {
	namespace argument {
		namespace instruction {
			namespace del {
				/*
				(인자 2) del naver : "naver라는 사이트와 그 안의 계정 전부를 삭제한다."
				(인자 3) del naver tempID : "naver라는 사이트 내의 tempID라는 ID를 가진 계정을 삭제한다."
				*/
				enum control { //Order_token 구조체의 token_count 를 통해 무슨 함수를 실행할지 제어한다.
					delete_form_use = 1,
					delete_site = 2,
					delete_account = 3
				};
				enum argument_position {
					site_name_position = 1,	//삭제할 사이트 이름의 인덱스
					id_position = 2,				//삭제할 ID 의 인덱스
				};
			}//namespace del
		}//namespace instruction
	}//namespace argument
}//namespace option
#endif // !_DELETE_H_
