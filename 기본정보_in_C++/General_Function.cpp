#include "General_Function.h"
using namespace std;
void General_Function::function_test()
{
	for (int i = 0; i < 100; i++)
		cout << get_random(200, 200) << endl;
}
bool General_Function::is_natural_number(std::string str)
{
	if (str.size() > 0)
	{
		const char * c_style_string = str.c_str();
		for (int i = 0; i < str.size(); i++)
			if (!('0' <= c_style_string[i] && c_style_string[i] <= '9'))
				return false;
		return true;
	}
	return false;
}
int General_Function::string_to_integer(std::string str)
{
	if (str.size() > 0)
	{
		const char * c_style_string = str.c_str();
		return atoi(c_style_string);
	}
	assert(0);
	return -999;
}
int General_Function::get_cipher(int number)
{
	int result = 1;
	while (number >= 0)
	{
		if (number / 10 == 0)
			return result;
		number /= 10;
		result++;
	}
	assert(0); //�ڸ��� ���ϴµ����� ������ �����������.
	return 0;
}
int General_Function::get_random(int min, int max)
{	
	assert(max >= min);
	// 1�ܰ�, �õ� ����
	std::random_device random;
	std::mt19937_64 rnd(random());
	// 2�ܰ�, ���� ���� (����)
	std::uniform_int_distribution<int> range(min, max);
	// 3�ܰ�, �� ����
	return range(rnd);
}
bool General_Function::ask_do_or_not(std::string ask)
{
	std::cout << ask << std::endl;
	std::cout << "yes Ȥ�� no �� �Է��ϼ���. (�Է��� \"yes\" �� �ƴϸ� ���� \"no\"�� �����)" << std::endl;
	std::cout << "> ";
	std::string answer;
	std::cin >> answer;
	std::cin.ignore();
	if (answer == "yes")
		return true;
	return false;
}
std::string General_Function::sum_of_argv(int argc, char ** argv)
{
	std::string order = "";
	for (int i = 1; i < argc; i++)
	{	//0��° ���ڴ� ���α׷��̸��̹Ƿ� ����
		std::string temp_str(*(argv + i));
		order += temp_str;
		order += " ";
		std::cout << order << std::endl;
	}
	return order;
}
void General_Function::get_string_without_overflow(char *string, const int string_length)
{
	int index = 0;
	while ((string[index] = getchar()) != '\n')
		if (index < string_length - 1)
			index++;
	string[index] = NULL;
	return;
}
int General_Function::login()
{
	if (compile::do_check_basic_character)
	{
		if ((char)_getch() != compile::pass_char)
			return compile::login_fail;
	}
	if (compile::do_require_additional_password)
	{
		std::string passwd_input;
		std::cin >> passwd_input;
		if (passwd_input != compile::then_password)
			return compile::login_fail;
	}
	return compile::login_success;
}

void General_Function::show_order(Order_token * order)
{
	std::cout << "=< " << order->token_count << " > tokens ="<< std::endl;
	for (int i = 0; i < order->token_count; i++)
		std::cout << "\t[" << i << "] " << order->tokens[i] << std::endl;
}

void General_Function::help()
{
	std::cout << "add�� �߰��ϴ°�" << std::endl;
	std::cout << "del�� �����ϴ°�" << std::endl;
	std::cout << "update�� �����ϴ°�" << std::endl;
	std::cout << "save�� �����ϴ°�" << std::endl;
}

