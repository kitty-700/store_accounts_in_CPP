#pragma once
#ifndef _ERROR_EXPRESSION_H_
#define _ERROR_EXPRESSION_H_
#include <string>
#include "Buffer.h"
namespace option {
	namespace error_expression
	{	//std::string error_answer / error_message
		/*//������ catch��
		catch (std::string error_message) { 
		std::cout << error_message << std::endl;
		return;
		}
		*/
		//arg
		static const std::string msg_too_much_args = "���ڰ� �ʹ� �����ϴ�.";
		static const std::string msg_not_defined_operation = "�׷� ��ɾ�� �����ϴ�.";
		static const std::string msg_unsupport_order_form = "��ɾ�� ����������, �������� �ʴ� ��� ����Դϴ�..";
		static const std::string msg_forbidden_character = "������ Ư�� ���� �Է¸� �Է��ϼ̽��ϴ�.";
		//Person
		static const std::string msg_person_hasnt_site = "�ƹ� ����Ʈ�� ��ϵǾ����� �ʽ��ϴ�.";
		//Site
		static const std::string abnormal_Site_site_name= "#$SN";
		static const std::string msg_site_name_must_be_filled = "����Ʈ �̸��� �����̾�� �� �˴ϴ�.";
		static const std::string msg_undefined_site_attribute = "Site �� �׷� �Ӽ��� �����ϴ�..";
		static const std::string msg_cant_make_site = "Site �� ���� �� �����ϴ�.";
		static const std::string msg_already_existing_site_name = "��(/��) �̹� �����ϴ� ����Ʈ �̸��Դϴ�.";
		static const std::string msg_no_existing_site_number = "�׷� ��ȣ�� ���� ����Ʈ�� �����ϴ�.";
		static const std::string msg_no_existing_site_name = "�׷� �̸��� ���� ����Ʈ�� �����ϴ�.";
		static const std::string msg_site_hasnt_account = "����Ʈ�� �ƹ��� ������ �����ϴ�.";
		static const std::string msg_too_long_site_name =
			"�Է��� ����Ʈ �̸��� ���̰� �ʹ� ��ϴ�.  ( " + std::to_string(buffer::site_name_length) + " �� ���Ϸ�..)";
		//Account
		static const std::string abnormal_Account_ID = "#$ID";
		static const std::string msg_undefined_account_attribute = "Account �� �׷� �Ӽ��� �����ϴ�..";
		static const std::string msg_no_existing_ID = "�׷� ID�� �����ϴ�.";
		static const std::string msg_ID_must_be_filled = "ID �� �����̾�� �� �˴ϴ�.";
		static const std::string msg_PW_must_be_filled = "PW �� �����̾�� �� �˴ϴ�.";
		static const std::string msg_already_existing_ID = "��(/��) �̹� �����ϴ� ID�Դϴ�.";
		static const std::string msg_no_existing_account_number = "�׷� ��ȣ�� ���� ������ �����ϴ�.";
		static const std::string msg_too_long_account_ID =
			"�Է��� ������ ID�� ���̰� �ʹ� ��ϴ�.  ( " + std::to_string(buffer::id_length) + " �� ���Ϸ�..)";
		static const std::string msg_too_long_account_PW =
			"�Է��� ������ Password�� ���̰� �ʹ� ��ϴ�.  ( " + std::to_string(buffer::password_length) + " �� ���Ϸ�..)";
		static const std::string msg_too_long_accout_memo =
			"�Է��� ������ memo �� ���̰� �ʹ� ��ϴ�.  ( " + std::to_string(buffer::memo_length) + " �� ���Ϸ�..)";
		//translation
		static const std::string translation_error = "TRANSLATION FAIL";
		//file_io
		static const std::string msg_file_doesnt_exist = "�׷� ���� �����ϴ�.";
		static const std::string msg_wrong_file_detected = "������ ���������� ������ �߸��Ǿ� �ҷ����� ���߽��ϴ�.";
		static const std::string msg_string_in_file_was_too_long = "���� �������� ���ڿ����� ���̰� �ʹ� ��ϴ�.";
		static const std::string msg_job_reset_warning = "������ �ٽ� �����ϱ� ���� ��������� ������ �������� ������ �۾��ϴ� �͵��� ������ϴ�.";
		//answer
		static const std::string msg_no_special_thing = "";
		static const std::string msg_no_order_input = "";
		//form fill
		static const std::string msg_no_input_form_filling_cancel = "�ƹ� �Էµ� �����Ƿ� ������ ����մϴ�.";
		static const std::string msg_form_filling_cancel = "������ ����մϴ�.";
		static const std::string msg_ineffective_select = "�������� �����ϴ�.";
		//string to int
		enum convert_error{
			string_to_be_int_wasnt_entered = -999
		};
	}// namespace error_expression
}//namespace option
#endif
