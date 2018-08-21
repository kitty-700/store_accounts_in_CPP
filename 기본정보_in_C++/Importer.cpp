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
	//data�� ���ڿ��� ������ϱ� ���� �����Ҵ�� ũ�⿡ 1�� ������ �� NULL�� ä���.
	this->di = 0;
	this->fp.read(this->data, this->data_size);
	this->fp.close();
	return;
}

void Importer::decrypt()
{	// ��� data�� �ص��Ѵ�.
	for (int i = 0; i < this->data_size; i++)
		data[i] = (~data[i]) ^ compile::xor_factor;
}

bool Importer::is_proper_transition(const int before_state, const int now_state)
{
	static int run_once = fiop::transition_graph_init(); //�Լ��� �� �ѹ��� �����Ű�� ���ؼ� static ������ ����. ���ϰ� ���ǹ�
	return fiop::transition_graph[before_state][now_state];
}

bool Importer::change_state(bool * is_successful)
{	//���º����Լ�. ���¶�? #0 ~ #9 .,
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

	case fiop::account_memo_assemblying://������ ����
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
{	//�Է¹��� �����͸� �����ؼ� '#'�� '0'�� �������� �Է¹޾��� ���� load_start �� true�� �����.
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
		if (this->data[this->di] == fiop::op_start_char) //data[di] �� '#'
			*(op_active) = true;
	}
}
bool Importer::assembly(bool * op_active, bool * is_successful)
{	/*
	�� ����Ʈ �� this->data���� �о�ͼ� ������ ��ġ�� �ִ´�.
	true ���� �� load ����, false ���Ͻ� load ����
	*/
	if (*(op_active) == true)
	{
		*(op_active) = false; //��ɻ��� ����
		return change_state(is_successful); //��ɾ� ���� ���ڿ� �������� ���¸� �ٲ۴�.
	}
	else
	{
		if (this->data[this->di] == fiop::op_start_char) //data[di] �� '#'
		{
			*(op_active) = true;
		}
		else if (
			this->data[this->di] == fiop::arg_input_finished_char ||
			this->data[this->di] == fiop::non_arg_char)
		{	// '$' �̳� '%'�� ������ str�� ������ ��ġ�� ������. ���� �� ��, str�� �ٽ� ""�� �ʱ�ȭ�ȴ�.
			if (fill_proper_place(state_was) == false)
			{
				std::cout << err_exp::msg_string_in_file_was_too_long << std::endl;
				return false;
			}
		}
		else
		{
			//�� ����Ʈ�� ���ڿ��� ����
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
			if (assembly(&op_active, &is_successful) == true) //true�� load ����, false�� load �ߴ�
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
	try { //���� �ε忡���� 3���� ��� �� ����ó���� 2���� ��쿡 ���ؼ� �Ѵ�.
		if (this->is_file_exists == false) //A. �ش��ϴ� ������ ���� �� -> temp_person�� is_alive�� true�̵�, ����Ʈ ���� 0��.
			throw err_exp::msg_file_doesnt_exist;
		if (is_person_initialized_well_with_raw_data() == true) //B. �����ϴ� ������ ���������� �ε�
			this->temp_person->set_is_alive(true);
		else //C. ������ ã������ �߸��� ������ ��
			throw err_exp::msg_wrong_file_detected;
	}
	catch (std::string error_message) {
		if (error_message == err_exp::msg_file_doesnt_exist)
		{	//A ���� ����ó�� (���� ����)
			std::cout << this->load_file_name << " ��� ������ ��� ���� ��������ϴ�." << std::endl;
			this->temp_person->set_is_alive(true); //��ǻ� ������ ���°� ������ �ƴϱ⿡ return ���� �ʴ´�.
			return;
		}
		else if (error_message == err_exp::msg_wrong_file_detected)
		{	//C ���� ����ó�� (���� �߸���)
			std::cout << error_message << std::endl;
			if (General_Function::ask_do_or_not("���� ������ �����ϰ� ���� ����ðڽ��ϱ�?") == true)
			{	//C - 1 ���� ����ó�� : ���� �ٽø��� ��� person �Ҵ� �� ���� ���� A���� ����ó���� ���� �ȴ�. 
				delete this->temp_person;
				this->temp_person = new Person();
				this->temp_person->set_is_alive(true);
				return;
			}
			else; //C - 2 ���� ����ó�� : �߸��� ������ ���� ������ �ʰ� ������.���Ŀ� ���ο� ������ �ٽ� �ε��� �� �ִ� �������� �־�����.
		}
	}
	if (compile::debug::load_raw_data_debug) //���Ϸε尡 �ǹ��ִ� B���� C-2�� ���̽��� ���ؼ��� ����ȴ�.
		show_now_data();
	return;
}

Person * Importer::return_person() {
	make_a_person();
	//A�� ���̽��� ���,	site_count �� 0�̰�			is_alive�� true�� person�� return,
	//B�� ���̽��� ���,	site_count �� 0�� �ƴϰ�	is_alive�� true�� person�� return,
	//C�� ���̽��� ���, 
	//	( C - 1 )	���θ��� : A�� ���̽��� ���� �ȴ�. 
	//	( C - 2 ) ���ξȸ��� : site_count �ʹ� �����ϰ� is_alive�� false�� person�� return�ȴ�. 
	//		�� C - 2 �� ��� ���Ŀ� ���ο� ������ �ٽ� �ε��� �� �ִ� �������� �־�����.
	return this->temp_person;
}