#pragma once
#ifndef _SHOW_H_
#define _SHOW_H_
namespace option {
	namespace argument {
		namespace instruction {
			namespace show {
				/*
				(���� 1) 2 : �ι�° ����Ʈ�� ���� ������ ����Ѵ�.
				(���� 1) "naver" : ����Ʈ �̸��� "naver"�� ����Ʈ�� ���� ������ ����Ѵ�.
				*/
				enum control { //Order_token ����ü�� token_count �� ���� ���� �Լ��� �������� �����Ѵ�.
					no_additional_arguments = 1
				};
				enum argument_position {

				};
			}//namespace show
		}//namespace instruction
	}//namespace argument
}//namespace option
#endif // !_SHOW_H_
