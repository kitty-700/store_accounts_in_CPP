#include "Module_Tester.h"
#include "Order_Token_Refiner.h"
#include "Order_Interpreter.h"

void Module_tester::module_test()
{
	std::cout << ">> MODULE TESTING <<" << std::endl;
	Order_Interpreter::interprete_order(Order_Token_Refiner(new Order_token).refining("add","ODDOODODOD"));
	Order_Interpreter::interprete_order(Order_Token_Refiner(new Order_token).refining("add"));
}
