#include "Importer.h"
namespace fiop = option::file_io_parameter;
namespace err_exp = option::error_expression;
Importer::Importer(std::string load_file_name) :
	load_file_name(load_file_name),
	temp_person(nullptr),
	temp_site(nullptr),
	temp_account(nullptr),
	temp_str(""),
	state_was(fiop::not_in_process),
	data(nullptr),
	data_size(fiop::file_doesnt_exist),
	di(fiop::file_doesnt_exist),
	is_file_exists(false)
{
	load_raw_data();
}

Importer::~Importer()
{
	delete this->data;
}

void Importer::get_data_size()
{
	this->fp.seekg(0, std::ios::end);
	this->data_size = (int)this->fp.tellg();
	this->fp.seekg(0, std::ios::beg);
}

void Importer::load_raw_data()
{
	try {
		this->fp.open(this->load_file_name, std::ios::binary);
		if (this->fp.is_open() == false)
			throw fiop::file_doesnt_exist;
	}
	catch (...)
	{
		this->is_file_exists = false;
		this->fp.close();
		return;
	}
	this->is_file_exists = true;
	get_data_size();
	this->data = new char[this->data_size + 1];
	this->data[this->data_size] = NULL;
	//data를 문자열로 디버깅하기 위해 동적할당시 크기에 1을 더해준 후 NULL로 채운다.
	this->di = 0;
	this->fp.read(this->data, this->data_size);
	this->fp.close();
	return;
}

void Importer::decrypt()
{	// 멤버 data를 해독한다.
	for (int i = 0; i < this->data_size; i++)
		data[i] = (~data[i]) ^ compile::xor_factor;
}

bool Importer::is_proper_transition(const int before_state, const int now_state)
{
	static int run_once = fiop::transition_graph_init(); //함수를 단 한번만 실행시키기 위해서 static 변수를 선언. 리턴값 무의미
	return fiop::transition_graph[before_state][now_state];
}

bool Importer::change_state(bool * is_successful)
{	//상태변경함수. 상태란? #0 ~ #9 .,
	int state_will = this->data[this->di] - char_to_int_fix;
	switch (state_will)
	{
	case fiop::site_assemblying_started:
		if (is_proper_transition(this->state_was, state_will) == false)
			goto STOP_LOADING;
		this->state_was = state_will;

		this->temp_site = new Site();
		goto CONTINUE_LOADING;

	case fiop::account_id_assemblying:
		if (is_proper_transition(this->state_was, state_will) == false)
			goto STOP_LOADING;
		this->state_was = state_will;

		this->temp_account = new Account();
		goto CONTINUE_LOADING;

	case fiop::account_pw_assemblying:
		if (is_proper_transition(this->state_was, state_will) == false)
			goto STOP_LOADING;
		this->state_was = state_will;
		goto CONTINUE_LOADING;

	case fiop::account_ud_assemblying:
		if (is_proper_transition(this->state_was, state_will) == false)
			goto STOP_LOADING;
		this->state_was = state_will;
		goto CONTINUE_LOADING;

	case fiop::account_memo_assemblying:
		if (is_proper_transition(this->state_was, state_will) == false)
			goto STOP_LOADING;
		this->state_was = state_will;

		goto CONTINUE_LOADING;

	case fiop::site_assemblying_finished:
		if (is_proper_transition(this->state_was, state_will) == false)
			goto STOP_LOADING;
		this->state_was = state_will;

		*(this->temp_person) += this->temp_site;
		this->temp_site = nullptr;
		goto CONTINUE_LOADING;

	case fiop::load_finished:
		*(is_successful) = true;
		goto STOP_LOADING;
	default: //fail
		*(is_successful) = false;
		goto STOP_LOADING;
	}
CONTINUE_LOADING:
	return true;
STOP_LOADING:
	return false;
}
bool Importer::fill_proper_place(const int state_was)
{
	switch (state_was)
	{
	case fiop::site_assemblying_started:
		if (this->temp_str.size() > buffer::site_name_length)
			return false;
		strcpy_s(this->temp_site->site_name, buffer::site_name_length, this->temp_str.c_str());
		break;

	case fiop::account_id_assemblying:
		if (this->temp_str.size() > buffer::id_length)
			return false;
		strcpy_s(this->temp_account->ID, buffer::id_length, this->temp_str.c_str());
		break;

	case fiop::account_pw_assemblying:
		if (this->temp_str.size() > buffer::password_length)
			return false;
		strcpy_s(this->temp_account->PW, buffer::password_length, this->temp_str.c_str());
		break;

	case fiop::account_ud_assemblying:
		if (this->temp_str.size() > buffer::update_time_length)
			return false;
		strcpy_s(this->temp_account->update_time, buffer::update_time_length, this->temp_str.c_str());
		break;

	case fiop::account_memo_assemblying://여까지 성공
		if (this->temp_str.size() > buffer::memo_length)
			return false;
		strcpy_s(this->temp_account->memo, buffer::memo_length, this->temp_str.c_str());

		this->temp_site->accounts.push_back(this->temp_account);
		this->temp_site->account_count++;
		this->temp_account = nullptr;
		break;

	default: //fail
		return false;
	}
	this->temp_str = "";
	return true;
}
void Importer::boot_load(bool * load_start, bool * op_active)
{	//입력받은 데이터를 참조해서 '#'과 '0'을 연속으로 입력받았을 때만 load_start 를 true로 만든다.
	if ((*op_active) == true)
	{
		*(op_active) = false;
		if (this->data[this->di] - char_to_int_fix == fiop::load_started)
		{
			*(load_start) = true;
			this->state_was = fiop::load_started;
		}
	}
	else //if ((*op_active) == false) 
	{
		if (this->data[this->di] == fiop::op_start_char) //data[di] 가 '#'
			*(op_active) = true;
	}
}
bool Importer::assembly(bool * op_active, bool * is_successful)
{	/*
	한 바이트 씩 this->data에서 읽어와서 적당한 위치에 넣는다.
	true 리턴 시 load 지속, false 리턴시 load 종료
	*/
	if (*(op_active) == true)
	{
		*(op_active) = false; //명령상태 해제
		return change_state(is_successful); //명령어 시작 문자와 합쳐져서 상태를 바꾼다.
	}
	else
	{
		if (this->data[this->di] == fiop::op_start_char) //data[di] 가 '#'
		{
			*(op_active) = true;
		}
		else if (
			this->data[this->di] == fiop::arg_input_finished_char ||
			this->data[this->di] == fiop::non_arg_char)
		{	// '$' 이나 '%'을 받으면 str을 적절한 위치로 보낸다. 물론 이 때, str은 다시 ""로 초기화된다.
			if (fill_proper_place(state_was) == false)
			{
				std::cout << err_exp::msg_string_in_file_was_too_long << std::endl;
				return false;
			}
		}
		else
		{
			//한 바이트씩 문자열에 저장
			this->temp_str += this->data[this->di];
		}
	}
	return true;
}


bool Importer::is_person_initialized_well_with_raw_data()
{
	if (compile::active_decryption == true)
		decrypt();
	bool load_start = false;
	bool op_active = false;
	bool is_successful = false;

	for (this->di = 0; this->di < this->data_size; this->di++)
	{
		if (load_start == false)
		{
			boot_load(&load_start, &op_active);
			continue;
		}
		else
		{
			if (assembly(&op_active, &is_successful) == true) //true면 load 지속, false면 load 중단
				continue;
			else
				break;
		}
	}
	return is_successful;
}

void Importer::show_now_data()
{
	for (int i = 0; i < this->data_size; i++)
		std::cout << data[i];
}

void Importer::make_a_person()
{
	this->temp_person = new Person();
	try { //파일 로드에서의 3가지 경우 중 예외처리는 2가지 경우에 대해서 한다.
		if (this->is_file_exists == false) //A. 해당하는 파일이 없을 때 -> temp_person의 is_alive는 true이되, 사이트 수는 0개.
			throw err_exp::msg_file_doesnt_exist;
		if (is_person_initialized_well_with_raw_data() == true) //B. 존재하는 파일을 정상적으로 로드
			this->temp_person->set_is_alive(true);
		else //C. 파일은 찾았으나 잘못된 파일일 때
			throw err_exp::msg_wrong_file_detected;
	}
	catch (std::string error_message) {
		if (error_message == err_exp::msg_file_doesnt_exist)
		{	//A 번의 예외처리 (파일 없음)
			std::cout << this->load_file_name << " 라는 파일이 없어서 새로 만들었습니다." << std::endl;
			this->temp_person->set_is_alive(true); //사실상 파일이 없는건 오류가 아니기에 return 하지 않는다.
			return;
		}
		else if (error_message == err_exp::msg_wrong_file_detected)
		{	//C 번의 예외처리 (파일 잘못됨)
			std::cout << error_message << std::endl;
			if (General_Function::ask_do_or_not("기존 파일을 무시하고 새로 만드시겠습니까?") == true)
			{	//C - 1 번의 예외처리 : 새로 다시만들 경우 person 할당 및 해제 이후 A번의 예외처리랑 같게 된다. 
				delete this->temp_person;
				this->temp_person = new Person();
				this->temp_person->set_is_alive(true);
				return;
			}
			else; //C - 2 번의 예외처리 : 잘못된 파일을 새로 만들지 않고 끝낸다.이후에 새로운 파일을 다시 로드할 수 있는 선택지가 주어진다.
		}
	}
	if (compile::debug::load_raw_data_debug) //파일로드가 의미있는 B번과 C-2번 케이스에 대해서만 실행된다.
		show_now_data();
	return;
}

Person * Importer::return_person() {
	make_a_person();
	//A번 케이스의 경우,	site_count 가 0이고			is_alive가 true인 person이 return,
	//B번 케이스의 경우,	site_count 가 0이 아니고	is_alive가 true인 person이 return,
	//C번 케이스의 경우, 
	//	( C - 1 )	새로만듬 : A번 케이스와 같게 된다. 
	//	( C - 2 ) 새로안만듬 : site_count 와는 무관하고 is_alive가 false인 person이 return된다. 
	//		└ C - 2 의 경우 이후에 새로운 파일을 다시 로드할 수 있는 선택지가 주어진다.
	return this->temp_person;
}