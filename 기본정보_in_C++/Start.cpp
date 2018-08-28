#include <iostream>
#include <string>
#include <windows.h>
#include "Options.h"
#include "Order_Interpreter.h"
#include "Module_Tester.h"
#include "Status.h"

void init_program(const int argc);
void exit_program();
namespace compile = option::parameters::compile;
int main(int argc, char ** argv)
{
	if (compile::do_module_test == true)
	{	//단순한 모듈테스트. compile_option에서 토글 가능
		Module_tester::module_test();
		exit(0);
	}
	Order_Interpreter slave;
	std::string order;
	std::string answer;
	bool is_exit = false;
	init_program(argc);
	do
	{
		General_Function::print_thick_line();
		std::cout << slave.get_loaded_file_name() << " > ";
		if (Status::get_is_argument_input() == false) {//보통의 경우엔 콘솔에서 명령어 입력을 받고 명령을 실행한다.
			General_Function::order_color_input(order);
		}
		else {//프로그램에 인자가 전달됐다면 단 한 번 전달된 명령을 실행한다.
			order = General_Function::sum_of_argv(argc, argv);
			Status::set_is_argument_input(false);
		}
		is_exit = slave.interprete_order(order);
	} while (!is_exit);
	exit_program();
	return 0;
}

void init_program(const int argc)
{
	if (General_Function::login() == compile::login_fail)
		exit(compile::login_fail);
	Module_tester::init();
	system("mode con:cols=80 lines=50");
	SetConsoleTitle(L"info edit");
	srand((unsigned)time(NULL));
	if (argc >= 2)
		Status::set_is_argument_input(true);
}

void exit_program()
{
	Module_tester::exit();
}
