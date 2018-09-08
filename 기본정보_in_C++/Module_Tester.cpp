#include "Module_Tester.h"
#include "Order_Token_Refiner.h"
#include "Order_Interpreter.h"
Person* Module_tester::person;
void Module_tester::module_test()
{
	std::cout << ">> MODULE TESTING <<" << std::endl;
	Order_Interpreter::interprete_order(Order_Token_Refiner(new Order_token).refining("add fuck a b c"));
	Order_Interpreter::interprete_order(Order_Token_Refiner(new Order_token).refining("add fuck b c d"));
	Order_Interpreter::interprete_order(Order_Token_Refiner(new Order_token).refining("update fuck FUCKKK"));
}
