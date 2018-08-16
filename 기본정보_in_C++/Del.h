#pragma once
#ifndef _DELETE_H_
#define _DELETE_H_
namespace option {
	namespace argument {
		namespace instruction {
			namespace del {
				/*
				(���� 2) del naver : "naver��� ����Ʈ�� �� ���� ���� ���θ� �����Ѵ�."
				(���� 3) del naver tempID : "naver��� ����Ʈ ���� tempID��� ID�� ���� ������ �����Ѵ�."
				*/
				enum control { //Order_token ����ü�� token_count �� ���� ���� �Լ��� �������� �����Ѵ�.
					delete_form_use = 1,
					delete_site = 2,
					delete_account = 3
				};
				enum argument_position {
					site_name_position = 1,	//������ ����Ʈ �̸��� �ε���
					id_position = 2,				//������ ID �� �ε���
				};
			}//namespace del
		}//namespace instruction
	}//namespace argument
}//namespace option
#endif // !_DELETE_H_
