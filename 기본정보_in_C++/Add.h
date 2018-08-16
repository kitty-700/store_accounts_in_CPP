#pragma once
#ifndef _ADD_H_
#define _ADD_H_
namespace option {
	namespace argument {
		namespace instruction {
			namespace add {
				/*
				(���� 2) add naver : "naver��� ����Ʈ�� �߰��Ѵ�."
				(���� 4) add naver tempID pasw123123 :
				"naver��� ����Ʈ�� ID�� tempID�̰� PW�� pasw123123�� ������ �߰��Ѵ�."
				(���� 5) add naver tempID pasw123123 no_memo :
				"naver��� ����Ʈ�� ID�� tempID�̰� PW�� pasw123123�̰� �޸� no_memo �� ������ �߰��Ѵ�."
				*/
				enum control { //Order_token ����ü�� token_count �� ���� ���� �Լ��� �������� �����Ѵ�.
					add_form_use = 1,
					add_site_only = 2,
					add_account_without_memo = 4,
					add_account_with_memo = 5
				};
				enum argument_position {
					new_site_name_position = 1,	//�߰��� ����Ʈ �̸��� �ε���
					new_id_position = 2,				//�߰��� ID �� �ε���
					new_pw_position = 3,				//�߰��� �н������� �ε���
					new_memo_position = 4			//�߰��� �޸��� �ε��� 
				};
			}//namespace add
		}//namespace instruction
	}//namespace argument
}//namespace option
#endif // !_ADD_H_
