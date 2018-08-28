#pragma once
#ifndef _BUFFER_H_
#define _BUFFER_H_
namespace option {
	namespace parameters {
		namespace buffer { //���α׷� ������ �̷�� ���� �Ű��������̹Ƿ� ���濡 ���� ������ ���� �� �ִ�.
			//���� ũ�� - �������ִ� ������ �ٸ� �÷��������� ���α׷���� ȣȯ���� ���߱� ���ؼ��� ���� ū ����
			enum { common_length = 200 }; //�� ���� ������ �̰� �����ϵ����Ѵ�. ������ byte
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
				operation_length = common_length, //add del ���� ���� ��ɾ� ����
				order_length = 	//add naver idsample pwpwpw333 ���� Ǯ ��� ���� (���� 5���� ��츦 ����)
				operation_length + site_name_length + id_length + password_length + memo_length
			};
		} // namespace buffer
	} // namespace parameters
}//namespace option
#endif