#pragma once
#ifndef _UPDATE_H_
#define _UPDATE_H_
namespace option {
	namespace argument {
		namespace instruction {
			namespace update {
				/*
				(���� 3) update naver Naver : "naver��� ����Ʈ �̸��� Naver�� �ٲ۴�."
				(���� 5) update Naver tempID PW pasw123123 :
				"Naver��� ����Ʈ�� tempID��� ID�� ���� ������ �н����带 pasw123123���� �����Ѵ�."
				*/
				enum control { //Order_token ����ü�� token_count �� ���� ���� �Լ��� �������� �����Ѵ�.
					modify_form_use = 1,
					modify_site_name = 3,
					modify_account_attribute = 5
				};
				enum argument_position {
					site_name_position = 1,	//�̸��� �ٲ� ����Ʈ�� �ε���
					new_site_name_position = 2,	//�ٲ� ����Ʈ �̸��� �ε��� 
					id_position = 2,						//�Ӽ� ���� �ٲ� ������ �ε��� 
					attribute_select_position = 3,	//�ٲٷ��� �Ӽ� ���� ���� �ε���
					new_attribute_value_position = 4	//�ٲٷ��� �Ӽ��� �� �� �ε���
				};
			}//namespace update
		}//namespace instruction
	}//namespace argument
}//namespace option
#endif // !_UPDATE_H_
