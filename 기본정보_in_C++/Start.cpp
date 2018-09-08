#include <iostream>
#include <string>
#include <windows.h>
#include "Options.h"
#include "Order_Interpreter.h"
#include "Module_Tester.h"
#include "Status.h"
void init_program();
void argument_excute(int argc, char ** argv);
void exit_program();
namespace compile = option::parameters::compile;
int main(int argc, char ** argv)
{
	if (compile::do_module_test == true)
	{	//�ܼ��� ����׽�Ʈ. compile_option���� ��� ����
		Module_tester::module_test();
		exit(0);
	}
	bool is_exit = false;
	init_program();
	argument_excute(argc, argv);
	do
	{
		std::string order_string;
		//1. ����� string ���� �Է¹޴´�.
		{
			General_Function::print_thick_line();
			std::cout << Order_Interpreter::get_loaded_file_name() << " > ";
			General_Function::order_color_input(order_string);
		}
		//2. �Է¹޴� string�� �߶� Order_token ����ü�� �ʱ�ȭ�Ѵ�. �������ϰ� �ʱ�ȭ�Ǹ� ���.
		{
			Order_token * order = Order_Token_Refiner(new Order_token).refining(order_string);
			if (order == nullptr) continue;
			Main_Order::set(order);
		}
		//3. Order_Interpreter �� �ʱ�ȭ�� Order_toekn ����ü�� �ѱ��. 
		{
			is_exit = Order_Interpreter::interprete_order(Main_Order::get());
		}
	} while (is_exit == option::expression::normal::no_exit);
	exit_program();
	return 0;
}

void init_program()
{
	if (General_Function::login() == compile::login_fail)
		exit(compile::login_fail);
	Module_tester::init();
	Order_Interpreter::init();
	//system("mode con:cols=80 lines=50");
	SetConsoleTitle(L"info edit");
	srand((unsigned)time(NULL));
}

void argument_excute(int argc, char ** argv)
{
	if (argc == 1) return;
	std::string string_order = General_Function::sum_of_argv(argc, argv);
	Main_Order::set(Order_Token_Refiner(new Order_token).refining(string_order));
	if (Main_Order::get() == nullptr) assert(0);
	Order_Interpreter::interprete_order(Main_Order::get());
}

void exit_program()
{
	Module_tester::exit();
}
