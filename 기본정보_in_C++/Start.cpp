#include <iostream>
#include <string>
#include <windows.h>
#include "Options.h"
#include "Order_Interpreter.h"
#include "Module_Tester.h"
#include "Status.h"
void init_program(const int argc);
void argument_excute(Order_Interpreter * slave, int argc, char ** argv);
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
	std::string order_string;
	std::string answer;
	bool is_exit = false;
	init_program(argc);
	argument_excute(&slave, argc, argv);
	do
	{
		//1. 명령을 string 으로 입력받는다.
		{
			General_Function::print_thick_line();
			std::cout << slave.get_loaded_file_name() << " > ";
			General_Function::order_color_input(order_string);
		}
		//2. 입력받는 string을 잘라 Order_token 구조체를 초기화한다. 부적절하게 초기화되면 폐기.
		{	
			Order_token * order = Order_Token_Refiner(new Order_token).refining(order_string);
			if (order == nullptr) continue;
			Main_Order::set(order);
		}
		//3. Order_Interpreter 에 초기화된 Order_toekn 구조체를 넘긴다. 
		{
			is_exit = slave.interprete_order(Main_Order::get());
		}
	} while (is_exit == option::expression::normal::no_exit);
	exit_program();
	return 0;
}

void init_program(const int argc)
{
	if (General_Function::login() == compile::login_fail)
		exit(compile::login_fail);
	Module_tester::init();
	//system("mode con:cols=80 lines=50");
	SetConsoleTitle(L"info edit");
	srand((unsigned)time(NULL));
}

void argument_excute(Order_Interpreter * slave, int argc, char ** argv)
{
	if (argc == 1) return;
	std::string string_order = General_Function::sum_of_argv(argc, argv);
	Main_Order::set(Order_Token_Refiner(new Order_token).refining(string_order));
	if (Main_Order::get() == nullptr) assert(0);
	slave->interprete_order(Main_Order::get());
}

void exit_program()
{
	Module_tester::exit();
}
