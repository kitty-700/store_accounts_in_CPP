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
			#5asjodpasjpo$ -> site에 account를 붙임

		-	#2mysecondID$
			#3secPW$
			#42018-08-06 01:07:11$
			#5%
		#6 -> person에 site를 붙임

		#1secondSite$
		#6 -> 이 경우, 사이트만 person에 붙인다.

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
			not_in_process = -1, //파일 로드에 대한 어떠한 동작도 수행하지않았음.
			load_started = 0, //#0
			site_assemblying_started = 1, //#1 $필수
			account_id_assemblying = 2, //#2 $필수
			account_pw_assemblying = 3, //#3 $필수
			account_ud_assemblying = 4, //#4 $필수
			account_memo_assemblying = 5, //#5 $ 혹은 % 필수
			site_assemblying_finished = 6, //#6
			load_finished = 9 //#9
		};
		static bool transition_graph[10][10]; //↖상태의 수를 늘리고 싶으면 여기도 수정해야한다.
											  //#0에서 바로 #5로 갈 수 없는 것처럼, 상태 전이에는 규칙이 있다. 규칙을 벗어나면 잘못된 파일을 load하는 것이므로 종료.
		static int transition_graph_init()
		{	//바로 위에 정의된 열거형 load_state 를 참조해서 전이 그래프를 초기화한다.
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