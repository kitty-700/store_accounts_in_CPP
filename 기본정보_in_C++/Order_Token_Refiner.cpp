#include "Order_Token_Refiner.h"
namespace normal_exp = option::expression::normal;
Order_Token_Refiner::Order_Token_Refiner(Order_token * order_token)
{
	this->order_token = order_token;
	this->order_token->token_count = 0;
}

Order_token * Order_Token_Refiner::refining(std::string order)
{
	order_tokenizer(order);
	return this->order_token;
}

void Order_Token_Refiner::order_tokenizer(std::string left_order)
{	//명령을 각 토큰으로 자른다. "~~~" 등의 패키징된 문자열도 고려해야한다.
	namespace arg = option::argument;
	namespace pack = arg::package;
	bool is_include_package = (extract_package(left_order) != pack::no_package_detected);
	int space_location;
	while (left_order.empty() != true)
	{
		left_order = left_trim(left_order);
		if (left_order.empty() == true)
			return;
		std::string order_argument;

		space_location = (int)left_order.find(" ");
		if (is_include_package == false)
		{
			if (space_location != std::string::npos) //공백이 있으면 공백을 기준으로 자른다.
			{
				order_argument = left_order.substr(0, space_location); //0번째문자부터 space_location만큼
				left_order = left_order.substr(space_location + 1);
			}
			else //공백이 없으면 끝
			{
				order_argument = left_order;
				left_order.clear(); //반복문의 조건이 left_order가 빌때까지니까 이게 break;이나 마찬가지
			}
		}
		else //패키지가 확실히 존재한다.
		{
			if (space_location == std::string::npos) //그런데 그 패키지가 공백도 없이 붙어있으면 그냥 하나로 묶는다.
			{
				order_argument = left_order;
				order_argument = unpackaging(order_argument);
				left_order.clear();
			}
			else	//패키지도 이에 더해 공백 역시 있다. 인자는 적어도 두 개란 소리. 
			{		//근데 패키지가 어느 위치인지에 따라 좀 다르게 처리한다.
				order_argument = extract_package(left_order);
				int then_package_position = (int)left_order.find(order_argument);
				if (then_package_position == pack::target_argument) //패키지가 첫번째 인자인 경우엔?
				{	//-> 언패키징한 문자열을 취한다.
					left_order = left_order.substr(order_argument.size());
					order_argument = unpackaging(order_argument);
					is_include_package = (extract_package(left_order) != pack::no_package_detected);
					//패키지 하나 빠졌으니까 패키지가 더 있는지 다시 검사한다.
				}
				else	//패키지가 첫번째 인자가 아닌 경우엔  ( add {site name unknown} 처럼 )
				{		//-> 앞에것만 취한다.
					order_argument = left_order.substr(0, space_location);
					left_order = left_order.substr(space_location + 1);
				}
			}
		}
		if (this->order_token->token_count >= arg::argument_limit)
		{
			this->order_token->token_count = arg::too_much_args;
			return;
		}
		this->order_token->content[this->order_token->each_argument] = order_argument;
		//각 토큰화된 문자열의 길이가 적절한지는 토큰들을 받아서 직접 처리하는 쪽에서 맡는다.
		this->order_token->each_argument++;
	}
}

std::string Order_Token_Refiner::extract_package(std::string order__string)
{	//문자열 내에 포함된 가장 빠른 순서의 패키지를 찾아낸다.
	//패키지가 없으면 no_pagage_detected 로 정의된 "" 을 반환한다.
	namespace package_macro = option::argument::package;
	using namespace package_macro;
	int order_size = (int)order__string.size();
	char * order__char = new char[order_size + normal_exp::index_fix];
	strcpy_s(order__char, order_size + normal_exp::index_fix, order__string.c_str());
	bool possible_to_include_package = false;
	int then_standard_index;

	int each_char = 0;
	for (; each_char < order_size; each_char++)
	{	 //패키징을 알리는 문자가 있는지 확인하고 없으면 종료한다.
		for (int what_standard = 0; what_standard < kinds_of_tip; what_standard++)
		{
			if (order__char[each_char] == package_standard[left_tip][what_standard])
			{
				possible_to_include_package = true;
				then_standard_index = what_standard;
				goto MAYBE_IT_CONTAINS_PACKAGE;
			}
		}
	}
	delete order__char;
	return package_macro::no_package_detected;
MAYBE_IT_CONTAINS_PACKAGE:
	const int package_start = each_char;
	for (; each_char < order_size; each_char++)
	{	//패키징을 끝내는 문자가 있는지 확인하고 있으면 패키징째로 반환.
		if ((order__char[each_char] == package_standard[right_tip][then_standard_index])
			&& (each_char != package_start) /* ' 과 " 처럼 여는 문자와 닫는 문자가 같은 경우를 위해서.*/)
		{
			const int package_end = each_char;
			int return_order_size = package_end - package_start + normal_exp::index_fix;
			char * new_order__char = new char[return_order_size + normal_exp::null_fix];
			for (int i = 0; i < return_order_size; i++)
				new_order__char[i] = order__char[i + package_start];
			new_order__char[return_order_size] = NULL;
			std::string new_order__string(new_order__char);

			delete new_order__char;
			delete order__char;
			return new_order__string; //임시객체반환
		}
	}
	delete order__char;
	return package_macro::no_package_detected;
}

std::string Order_Token_Refiner::unpackaging(std::string arg)
{	//add "the site my best required" 처럼 패키징된 인자를 풀어준다.
	using namespace option::argument::package;
	if (arg.empty() == true)
		return arg;
	if (arg.length() >= 3)
	// "" 이런건 그냥 그대로 넘기고,, "a" 이런거부터 패키징이 유의미하니까  a만 넘긴다.
	{
		for (int i = 0; i < kinds_of_tip; i++)
		{
			if (arg[0] == package_standard[left_tip][i] && \
				arg[arg.length() - normal_exp::index_fix] == package_standard[right_tip][i])
				return arg.substr(1, arg.length() - normal_exp::index_fix - 1);
		}
	}
	return arg;
}

std::string Order_Token_Refiner::left_trim(std::string str)
{
	do
	{
		int space_position = (int)str.find(" ");
		if (space_position == 0) // " *"
			str.erase(0, 1);
		else
			break;
		//(space_position == std::string::npos) 인 경우 -> "*"
		// 혹은  "* *" 인 경우
	} while (str.empty() != true);
	return str;
}

Order_token * Order_Token_Refiner::get_order_token() const
{
	return this->order_token;
}
