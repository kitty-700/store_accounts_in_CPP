#include <iostream>
#include <string>
#include <windows.h>
#include "Options.h"
#include "Compile.h"
#include "General_Function.h"
#include "Order_Interpreter.h"
#include "Status.h"

int main(int argc, char ** argv)
{
	if (compile::do_you_test_the_module)
	{	//단순한 모듈테스트. compile_option에서 토글 가능
		General_Function::function_test();
		return 0;
	}

	if (General_Function::login() == compile::login_fail)
		exit(compile::login_fail);

	Order_Interpreter * slave = new Order_Interpreter();
	//만일 불러오기에 적절한 파일을 찾지 못 했다면 여기서 무한루프를 돈다.

	std::string order;
	std::string answer;
	bool do_more = true;
	if (argc >= 2)
		Status::set_is_argument_input(true);

	do
	{
		std::cout << "==============================\n> ";
		if (Status::get_is_argument_input() == true) { //프로그램에 인자가 전달됐다면 단 한 번 전달된 명령을 실행한다.
			order = General_Function::sum_of_argv(argc, argv);
			Status::set_is_argument_input(false);
		}

		else {
			SET_CONSOLE_COLOR(console_color::order_color);
			std::getline(std::cin, order, '\n');
			//Sleep(2000);
			SET_CONSOLE_COLOR_DEFAULT;
		}
		if (order == "reload") {
			system("cls");
			delete slave;
			slave = new Order_Interpreter();
			continue;
		}
		do_more = slave->do_order(order) != "exit";
	} while (do_more);
	delete slave;
	return 0;
}