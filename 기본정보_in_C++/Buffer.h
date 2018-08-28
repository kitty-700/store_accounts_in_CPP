#pragma once
#ifndef _BUFFER_H_
#define _BUFFER_H_
namespace option {
	namespace parameters {
		namespace buffer { //프로그램 구조를 이루는 여러 매개변수들이므로 변경에 따른 위험이 있을 수 있다.
			//버퍼 크기 - 지정해주는 이유는 다른 플랫폼에서의 프로그램들과 호환성을 맞추기 위해서가 가장 큰 이유
			enum { common_length = 200 }; //별 이유 없으면 이걸 참조하도록한다. 단위는 byte
			enum account_define {
				id_length = common_length,
				password_length = common_length,
				update_time_length = common_length,
				memo_length = common_length
			};
			enum site_define {
				site_name_length = common_length
			};
			enum order_define {
				operation_length = common_length, //add del 등의 단일 명령어 길이
				order_length = 	//add naver idsample pwpwpw333 등의 풀 명령 길이 (인자 5개인 경우를 가정)
				operation_length + site_name_length + id_length + password_length + memo_length
			};
		} // namespace buffer
	} // namespace parameters
}//namespace option
#endif