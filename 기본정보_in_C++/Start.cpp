#include <iostream>
#include <string>
#include <windows.h>
#include "Options.h"
#include "Compile.h"
#include "Order_Interpreter.h"
#include "Module_Tester.h"
#include "Status.h"
void init(bool * do_more, Order_Interpreter * p_slave, const int argc);
int main(int argc, char ** argv)
{
	if (compile::module_test == true)
	{	//단순한 모듈테스트. compile_option에서 토글 가능
		module_test();
		exit(0);
	}
	Order_Interpreter slave;
	std::string order;
	std::string answer;
	bool do_more;
	init(&do_more, &slave, argc);
	do
	{
		General_Function::print_thick_line();
		std::cout << "> ";
		if (Status::get_is_argument_input() == false) {//보통의 경우엔 콘솔에서 명령어 입력을 받고 명령을 실행한다.
			General_Function::order_color_input(order);
		}
		else {//프로그램에 인자가 전달됐다면 단 한 번 전달된 명령을 실행한다.
			order = General_Function::sum_of_argv(argc, argv);
			Status::set_is_argument_input(false);
		}
		do_more = slave.excute_order(order) != "exit";
	} while (do_more);
	return 0;
}

void init(bool * do_more, Order_Interpreter * p_slave, const int argc)
{

	if (General_Function::login() == compile::login_fail)
		exit(compile::login_fail);

	srand((unsigned)time(NULL));
	*do_more = true;
	if (argc >= 2)
		Status::set_is_argument_input(true);
}