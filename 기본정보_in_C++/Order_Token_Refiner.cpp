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
{	//����� �� ��ū���� �ڸ���. "~~~" ���� ��Ű¡�� ���ڿ��� ����ؾ��Ѵ�.
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
			if (space_location != std::string::npos) //������ ������ ������ �������� �ڸ���.
			{
				order_argument = left_order.substr(0, space_location); //0��°���ں��� space_location��ŭ
				left_order = left_order.substr(space_location + 1);
			}
			else //������ ������ ��
			{
				order_argument = left_order;
				left_order.clear(); //�ݺ����� ������ left_order�� ���������ϱ� �̰� break;�̳� ��������
			}
		}
		else //��Ű���� Ȯ���� �����Ѵ�.
		{
			if (space_location == std::string::npos) //�׷��� �� ��Ű���� ���鵵 ���� �پ������� �׳� �ϳ��� ���´�.
			{
				order_argument = left_order;
				order_argument = unpackaging(order_argument);
				left_order.clear();
			}
			else	//��Ű���� �̿� ���� ���� ���� �ִ�. ���ڴ� ��� �� ���� �Ҹ�. 
			{		//�ٵ� ��Ű���� ��� ��ġ������ ���� �� �ٸ��� ó���Ѵ�.
				order_argument = extract_package(left_order);
				int then_package_position = (int)left_order.find(order_argument);
				if (then_package_position == pack::target_argument) //��Ű���� ù��° ������ ��쿣?
				{	//-> ����Ű¡�� ���ڿ��� ���Ѵ�.
					left_order = left_order.substr(order_argument.size());
					order_argument = unpackaging(order_argument);
					is_include_package = (extract_package(left_order) != pack::no_package_detected);
					//��Ű�� �ϳ� �������ϱ� ��Ű���� �� �ִ��� �ٽ� �˻��Ѵ�.
				}
				else	//��Ű���� ù��° ���ڰ� �ƴ� ��쿣  ( add {site name unknown} ó�� )
				{		//-> �տ��͸� ���Ѵ�.
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
		//�� ��ūȭ�� ���ڿ��� ���̰� ���������� ��ū���� �޾Ƽ� ���� ó���ϴ� �ʿ��� �ô´�.
		this->order_token->each_argument++;
	}
}

std::string Order_Token_Refiner::extract_package(std::string order__string)
{	//���ڿ� ���� ���Ե� ���� ���� ������ ��Ű���� ã�Ƴ���.
	//��Ű���� ������ no_pagage_detected �� ���ǵ� "" �� ��ȯ�Ѵ�.
	namespace package_macro = option::argument::package;
	using namespace package_macro;
	int order_size = (int)order__string.size();
	char * order__char = new char[order_size + normal_exp::index_fix];
	strcpy_s(order__char, order_size + normal_exp::index_fix, order__string.c_str());
	bool possible_to_include_package = false;
	int then_standard_index;

	int each_char = 0;
	for (; each_char < order_size; each_char++)
	{	 //��Ű¡�� �˸��� ���ڰ� �ִ��� Ȯ���ϰ� ������ �����Ѵ�.
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
	{	//��Ű¡�� ������ ���ڰ� �ִ��� Ȯ���ϰ� ������ ��Ű¡°�� ��ȯ.
		if ((order__char[each_char] == package_standard[right_tip][then_standard_index])
			&& (each_char != package_start) /* ' �� " ó�� ���� ���ڿ� �ݴ� ���ڰ� ���� ��츦 ���ؼ�.*/)
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
			return new_order__string; //�ӽð�ü��ȯ
		}
	}
	delete order__char;
	return package_macro::no_package_detected;
}

std::string Order_Token_Refiner::unpackaging(std::string arg)
{	//add "the site my best required" ó�� ��Ű¡�� ���ڸ� Ǯ���ش�.
	using namespace option::argument::package;
	if (arg.empty() == true)
		return arg;
	if (arg.length() >= 3)
	// "" �̷��� �׳� �״�� �ѱ��,, "a" �̷��ź��� ��Ű¡�� ���ǹ��ϴϱ�  a�� �ѱ��.
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
		//(space_position == std::string::npos) �� ��� -> "*"
		// Ȥ��  "* *" �� ���
	} while (str.empty() != true);
	return str;
}

Order_token * Order_Token_Refiner::get_order_token() const
{
	return this->order_token;
}
