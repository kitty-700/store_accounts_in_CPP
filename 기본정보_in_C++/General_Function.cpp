#include "General_Function.h"
using namespace std;
void General_Function::function_test()
{
	for (int i = 0; i < 100; i++)
		cout << get_random(200, 200) << endl;
}
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
		return error_expression::string_to_be_int_wasnt_entered;
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
	assert(0); //자릿수 구하는데에서 음수는 고려하지않음.
	return 0;
}
int General_Function::get_random(int min, int max)
{	
	assert(max >= min);
	/* 기존의 이 방식으론 짧은 시간동안 너무 많은 중복 수가 나와버린다.
	srand((unsigned)time(NULL));
	cout << rand() << endl;
	return rand() % (max - min) + min;
	*/
	// 1단계, 시드 설정	
	random_device random;
	mt19937_64 rnd(random());
	// 2단계, 분포 설정 (정수)
	uniform_int_distribution<int> range(min, max);
	// 3단계, 값 추출
	return range(rnd);
}

bool General_Function::ask_do_or_not(std::string ask)
{
	cout << ask << std::endl;
	cout << "yes 혹은 no 를 입력하세요. (입력이 \"yes\" 가 아니면 전부 \"no\"로 취급함)" << std::endl;
	cout << "> ";
	string answer;
	cin >> answer;
	cin.ignore();
	if (answer == "yes")
		return true;
	return false;
}
std::string General_Function::sum_of_argv(int argc, char ** argv)
{
	string order = "";
	for (int i = 1; i < argc; i++)
	{	//0번째 인자는 프로그램이름이므로 제외
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
	cout << "=< " << order->token_count << " > tokens ="<< endl;
	for (int i = 0; i < order->token_count; i++)
		cout << "\t[" << i << "] " << order->tokens[i] << endl;
}

void General_Function::help()
{	//Help 메뉴얼~~
	cout << thick_line << endl;
		printf("%s  / %s 버전!\n", __DATE__, __TIME__);
#if SHOW_SOURCE
		printf("kitty 제작, 메일은 knukit@naver.com 으로\n");
#endif
		cout << compile::source_message << endl;
		cout << thick_line;
		printf("%-10s (s)\t:리스트 보기\n", "ls");
		printf("%-10s (a)\t:사이트 혹은 계정 추가하기\n", "add");
		printf("%-10s (d)\t:사이트 혹은 계정 삭제하기\n", "del");
		printf("%-10s (u)\t:사이트 혹은 계정 변경하기\n", "upate");
		//printf("%-10s (w)\t:사이트 순서 변경\n", "swap");
		printf("%-10s (l)\t:변경 사항 출력\n", "history");
		printf("%-10s (c)\t:화면을 깨끗하게 지우기\n", "cls");
		printf("%-10s (v)\t:모든 정보를 파일에 저장\n", "save");
		printf("%-10s (q)\t:프로그램 종료\n", "exit");
		printf("\n");
		printf("보통의 상황에서 아무 입력도 안 하고 엔터를 누르면 작업취소를 의미합니다.\n");
		printf("진행중인 작업을 취소하는 것이 이상한 데이터를 집어넣는 것보다 낫습니다.\n");
		printf("\n");
		printf("Tip. [Win + R] 단축키 (실행창) 를 통해 빠르게 실행하는 방법\n");
		printf("\t\t환경변수 - 사용자변수 - Path 에 새로만들기 - 이 프로그램이 들어있는 폴더 경로를 추가\n");
		printf("\t\t이 프로그램 이름을 accounts로 해두었다면 실행 창에서 accounts 를 입력하면 바로 실행.\n");
		printf("\n");
		printf("명령어 \"c\" -> 화면 클리어.\n");
	}

