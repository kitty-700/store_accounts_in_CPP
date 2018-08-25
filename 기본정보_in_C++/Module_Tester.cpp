#include "Module_Tester.h"

#include"Log_Recorder.h"
#include"Structs.h"
#include"Order_Token_Refiner.h"
void module_test()
{
	Log_Recorder lg;
	std::string order = "del f c d a";
	Order_token * order_refined = Order_Token_Refiner(new Order_token).refining(order);
	lg.add_log(order_refined, "ORIG_1");
	lg.add_log(order_refined, "ORIG_2");
	lg.add_log(order_refined, "ORIG_3");
	lg.add_log(order_refined, "ORIG_4");
	lg.print_log();
}
