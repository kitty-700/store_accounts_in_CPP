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
	{	//�ܼ��� ����׽�Ʈ. compile_option���� ��� ����
		General_Function::function_test();
		return 0;
	}

	if (General_Function::login() == compile::login_fail)
		exit(compile::login_fail);

	Order_Interpreter * slave = new Order_Interpreter();
	//���� �ҷ����⿡ ������ ������ ã�� �� �ߴٸ� ���⼭ ���ѷ����� ����.

	std::string order;
	std::string answer;
	bool do_more = true;
	if (argc >= 2)
		Status::set_is_argument_input(true);

	do
	{
		std::cout << "==============================\n> ";
		if (Status::get_is_argument_input() == true) { //���α׷��� ���ڰ� ���޵ƴٸ� �� �� �� ���޵� ����� �����Ѵ�.
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