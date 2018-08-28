#pragma once
#ifndef _COMPILE_H_
#define _COMPILE_H_
#include <string>

namespace option {
	namespace parameters {
		namespace compile	//������ �ø��� �ٲ㺼�� ������ŭ ���濡 ���� ����ũ�� ����.
		{
			//��� �׽�Ʈ
			static const bool do_module_test = false;
			//���ϸ�
			static const std::string default_load_file_name = "AQ.alz";
			static const std::string default_save_file_name = "AQ.alz";
			//��ȣȭ ����
			static const bool active_encryption = true; //at Export
			static const bool active_decryption = true; //at Import
			//JUNK byte ���̱�.  �ѹ� ���� ������ min~max ��ŭ�� ����Ʈ �� �� ���� ������ ���δ�.
			static const bool generate_junk_bytes = true;
			static const int max_junk_bytes = 500000;
			static const int min_junk_bytes = 250000; //max���� ũ�� �ʾƾ� �Ѵ�.
			//�α���
			static const bool pass_char_ipnut = false;	//�� ���α׷��� �� �� �ƴ����� ���� �͸� �ľ�
			static const char pass_char = 'a';

			static const bool require_additional_password = false;	 //�� �ܿ� �߰��� ��й�ȣ �Է�
			static const std::string then_password = "bc";
			enum login_status { login_success = 0, login_fail = 1 };
			//��ȣȭ ����
			static const char xor_factor = '#';
			//���α׷� ��ó ǥ�� ����
			static const bool is_show_the_source = true;
			static const std::string source_message = "KNU";
			//�����ɼ�
			namespace debug
			{
				static const bool order_tokenizer = false;
				static const bool load_raw_data = false;
			}// namespace debug
		} // namespace compile
	}// namespace parameters
}// namespace option
#endif