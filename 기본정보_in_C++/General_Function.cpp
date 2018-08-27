#include "General_Function.h"
using namespace std;
namespace err_exp = option::expression::error;

bool General_Function::is_natural_number(string str)
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
int General_Function::string_to_integer(string str)
{
	if (str == "")
		return expression::error::string_to_be_int_wasnt_entered;
	else if (str.size() > 0) {
		const char * c_style_string = str.c_str();
		return atoi(c_style_string);
	}
	else	{
		assert(0);
		return -9999;//i dont know. 
	}
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
	return -999;
}
int General_Function::get_random(int min, int max)
{	//2���� ����� �ִµ�, 2��° ����� �ӵ��� �ʹ� ������.
	assert(max >= min);
	//������ �� ������� ª�� �ð����� �ʹ� ���� �ߺ� ���� ���͹�����. (�õ� ������ 1�ʶ�)
	//�� �� ������ �Ͼ ������ �Լ��� ȣ��� ������ �õ带 �����߱� ����. �ƿ� main()�ʿ��� �� �ѹ��� �õ带 ������ �� �ְ� �ٲ��.
	const static int interval = max - min;
	return (rand() % interval) + min;
	////////////////////////////////////////////////////////
	/*
	// 1�ܰ�, �õ� ����
	random_device random;
	mt19937_64 rnd(random());
	// 2�ܰ�, ���� ���� (����)
	uniform_int_distribution<int> range(min, max);
	// 3�ܰ�, �� ����
	return range(rnd);
	*/
}

bool General_Function::ask_do_or_not(std::string ask)
{
	cout << ask << std::endl;
	cout << "yes Ȥ�� no �� �Է��ϼ���. (�Է��� \"yes\" �� �ƴϸ� ���� \"no\"�� �����)" << std::endl;
	cout << "> ";
	string answer;
	order_color_input(answer);
	if (answer == "yes")
		return true;
	return false;
}
void General_Function::order_color_input(std::string &order)
{
	SET_CONSOLE_COLOR(console_color::order_color);
	std::getline(std::cin, order, '\n');
	SET_CONSOLE_COLOR_DEFAULT;
}
std::string General_Function::sum_of_argv(int argc, char ** argv)
{
	string order = "";
	for (int i = 1; i < argc; i++)
	{	//0��° ���ڴ� ���α׷��̸��̹Ƿ� ����
		string temp_str(*(argv + i));
		order += temp_str;
		order += " ";
		cout << order << std::endl;
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
	if (compile::pass_char_ipnut)
	{
		if ((char)_getch() != compile::pass_char)
			return compile::login_fail;
	}
	if (compile::require_additional_password)
	{
		string passwd_input;
		cin >> passwd_input;
		if (passwd_input != compile::then_password)
			return compile::login_fail;
	}
	return compile::login_success;
}

void General_Function::show_order(Order_token * order)
{
	for (int i = 0; i < order->token_count; i++)
		cout << order->tokens[i] << " ";
	cout << endl;
}

void General_Function::print_thick_line()
{
	cout << option::expression::normal::thick_line << endl;
}

void General_Function::print_thin_line()
{
	cout << option::expression::normal::thin_line << endl;
}

void General_Function::help()
{	//Help �޴���~~
	General_Function::print_thin_line();
	printf("%s  / %s ����!\n", __DATE__, __TIME__);
	if (compile::is_show_the_source == true)
		cout << compile::source_message << endl;
	General_Function::print_thin_line();
	printf("%-10s \t:����Ʈ ����\n", "ls");
	printf("%-10s \t:����Ʈ Ȥ�� ���� �߰��ϱ�\n", "add");
	printf("%-10s \t:����Ʈ Ȥ�� ���� �����ϱ�\n", "del");
	printf("%-10s \t:����Ʈ Ȥ�� ���� �����ϱ�\n", "upate");
	//printf("%-10s (w)\t:����Ʈ ���� ����\n", "swap");
	printf("%-10s \t:���� ���� ���\n", "log");
	printf("%-10s \t:ȭ���� �����ϰ� �����\n", "cls");
	printf("%-10s \t:��� ������ ���Ͽ� ����\n", "save");
	printf("%-10s \t:���α׷� ����\n", "exit");
	printf("\n");
	printf("������ ��Ȳ���� �ƹ� �Էµ� �� �ϰ� ���͸� ������ �۾���Ҹ� �ǹ��մϴ�.\n");
	printf("�������� �۾��� ����ϴ� ���� �̻��� �����͸� ����ִ� �ͺ��� �����ϴ�.\n");
	printf("\n");
	printf("Tip. [Win + R] ����Ű (����â) �� ���� ������ �����ϴ� ���\n");
	printf("\t\tȯ�溯�� - ����ں��� - Path �� ���θ���� - �� ���α׷��� ����ִ� ���� ��θ� �߰�\n");
	printf("\t\t�� ���α׷� �̸��� accounts�� �صξ��ٸ� ���� â���� accounts �� �Է��ϸ� �ٷ� ����.\n");
}

