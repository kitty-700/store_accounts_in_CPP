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
	{	//�ܼ��� ����׽�Ʈ. compile_option���� ��� ����
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
		if (Status::get_is_argument_input() == false) {//������ ��쿣 �ֿܼ��� ��ɾ� �Է��� �ް� ����� �����Ѵ�.
			General_Function::order_color_input(order);
		}
		else {//���α׷��� ���ڰ� ���޵ƴٸ� �� �� �� ���޵� ����� �����Ѵ�.
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