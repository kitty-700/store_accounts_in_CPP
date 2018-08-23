#pragma once
#ifndef _FILE_IO_H_
#define _FILE_IO_H_
#include <string>
namespace option {
	namespace file_io_parameter
	{
		/*
		#0

		#1naver$
		-	#2my main ID$
			#3main's PW$
			#42018-08-06 01:07:03$
			#5asjodpasjpo$ -> site�� account�� ����

		-	#2mysecondID$
			#3secPW$
			#42018-08-06 01:07:11$
			#5%
		#6 -> person�� site�� ����

		#1secondSite$
		#6 -> �� ���, ����Ʈ�� person�� ���δ�.

		#9
		*/
		static const char op_start_char = '#';
		static const char arg_input_finished_char = '$';
		static const char non_arg_char = '%';
		enum {
			op_start = 100, //#
			file_doesnt_exist = -1,
			wrong_file_detected = -2
		};
		enum load_state {
			not_in_process = -1, //���� �ε忡 ���� ��� ���۵� ���������ʾ���.
			load_started = 0, //#0
			site_assemblying_started = 1, //#1 $�ʼ�
			account_id_assemblying = 2, //#2 $�ʼ�
			account_pw_assemblying = 3, //#3 $�ʼ�
			account_ud_assemblying = 4, //#4 $�ʼ�
			account_memo_assemblying = 5, //#5 $ Ȥ�� % �ʼ�
			site_assemblying_finished = 6, //#6
			load_finished = 9 //#9
		};
		static bool transition_graph[10][10]; //�ػ����� ���� �ø��� ������ ���⵵ �����ؾ��Ѵ�.
											  //#0���� �ٷ� #5�� �� �� ���� ��ó��, ���� ���̿��� ��Ģ�� �ִ�. ��Ģ�� ����� �߸��� ������ load�ϴ� ���̹Ƿ� ����.
		static int transition_graph_init()
		{	//�ٷ� ���� ���ǵ� ������ load_state �� �����ؼ� ���� �׷����� �ʱ�ȭ�Ѵ�.
			for (int i = 0; i < 10; i++)
				for (int j = 0; j < 10; j++)
					transition_graph[i][j] = false;
			transition_graph[load_started][site_assemblying_started] = true;
			transition_graph[site_assemblying_started][account_id_assemblying] = true;
			transition_graph[site_assemblying_started][site_assemblying_finished] = true;
			transition_graph[account_id_assemblying][account_pw_assemblying] = true;
			transition_graph[account_pw_assemblying][account_ud_assemblying] = true;
			transition_graph[account_ud_assemblying][account_memo_assemblying] = true;
			transition_graph[account_memo_assemblying][account_id_assemblying] = true;
			transition_graph[account_memo_assemblying][site_assemblying_finished] = true;
			transition_graph[site_assemblying_finished][site_assemblying_started] = true;
			transition_graph[site_assemblying_finished][load_finished] = true;
			return 0;
		}
	}// namespace file_io
}//namespace option
#endif