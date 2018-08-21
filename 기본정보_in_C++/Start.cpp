#include <iostream>
#include <string>
#include <windows.h>
#include "Options.h"
#include "Compile.h"
#include "General_Function.h"
#include "Order_Interpreter.h"
#include "Status.h"
void init(bool * do_more, Order_Interpreter ** p_slave, const int argc);
int main(int argc, char ** argv)
{
	if (compile::module_test == true)
	{	//단순한 모듈테스트. compile_option에서 토글 가능
		General_Function::function_test();
		exit(0);
	}
	Order_Interpreter * slave;
	std::string order;
	std::string answer;
	bool do_more;
	init(&do_more, &slave, argc);
	do
	{
		std::cout << thick_line << std::endl;
		std::cout << "> ";
		if (Status::get_is_argument_input() == false) {//보통의 경우엔 콘솔에서 명령어 입력을 받고 명령을 실행한다.
			General_Function::order_color_input(order);
		}
		else {//프로그램에 인자가 전달됐다면 단 한 번 전달된 명령을 실행한다.
			order = General_Function::sum_of_argv(argc, argv);
			Status::set_is_argument_input(false);
		}
		if (order == "reload") { //Order_interpreter랑 파일 적재의 분리가 제대로 안 이루어져있어서 아직은 main()에 유지한다. 
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

void init(bool * do_more, Order_Interpreter ** p_slave, const int argc)
{

	if (General_Function::login() == compile::login_fail)
		exit(compile::login_fail);

	srand((unsigned)time(NULL));
	*p_slave = new Order_Interpreter();//만일 불러오기에 적절한 파일을 찾지 못 했다면 여기서 무한루프를 돈다.
	*do_more = true;
	if (argc >= 2)
		Status::set_is_argument_input(true);
}