#pragma once
#ifndef _LOAD_H_
#define _LOAD_H_
namespace option {
	namespace argument {
		namespace instruction {
			namespace load {
				/*
				(���� 1) reload : �⺻ ���� �̸����� ���縦 �õ��Ѵ�.
				(���� 2) reload file_B : file_B ��� ���Ϸ� ���縦 �õ��Ѵ�.
				*/
				enum control { //Order_token ����ü�� token_count �� ���� ���� �Լ��� �������� �����Ѵ�.
					load_in_default_file_name = 1,
					load_in_specific_file_name = 2
				};
				enum argument_position {
					file_name_position = 1,	//���� �����ϰ��� �ϴ� ���� �̸��� �ε���
				};
			}//namespace load
		}//namespace instruction
	}//namespace argument
}//namespace option
#endif // !_LOAD_H_
