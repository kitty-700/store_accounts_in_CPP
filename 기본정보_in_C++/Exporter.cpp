#include "Exporter.h"
namespace fiop = option::parameters::file_io;
namespace compile = option::parameters::compile;
Exporter::Exporter(Person * person, std::string save_file_name) : person_to_export(person), save_file_name(save_file_name)
{
	this->fp.open(this->save_file_name, std::ios::binary);
}
void Exporter::encrypt(std::string& data)
{
	for (int i = 0; i < data.size(); i++)
		data[i] = (~data[i]) ^ compile::xor_factor;
}
void Exporter::encrypt(char* data)
{
	*data = (~(*data)) ^ compile::xor_factor;
}
void Exporter::put_on_file(char data)
{
	if (compile::active_encryption == true)
		encrypt(&data);
	this->fp << data;
}
void Exporter::junk_byte_input()
{
	const int trials = General_Function::get_random(compile::min_junk_bytes, compile::max_junk_bytes); //디버깅결과 실제로 병목이 되는 부분임.
	char to_add;
	for (int i = 0; i < trials; i++)
	{
		to_add = General_Function::get_random(0x00, 0xFF);
		if (to_add == fiop::op_start_char)
		{	/*
			#0이 동시에 나와버리면 junk byte 만으로 데이터 로드를 시작해버리기 때문에,
			'#' 과 다른 문자들간의 빈도수를 맞추면서 '#'과 '0', 둘이 동시에 나오지 않게한다.
			빈도수 분석을 통해 파일의 성질을 추정하는 것을 방해한다.
			*/
			if (i % 2 == 0)
				continue;
			else //확률은 1/2이다. 각각 아예 '#'를 넣지 않거나(if), 한번에 두 개를 넣거나(else).
				put_on_file(to_add);
			//가끔 메모장으로 데이터를 읽어보면 ?#j~~~ 처럼 #가 하나만 있는 경우가 있는데 이건 한글이랑 겹쳐서 출력된거고, 실제로는  ##가 있다.
		}
		put_on_file(to_add);
	}
}
void Exporter::person_byte_input()
{
	this->temp_string = "";
	this->temp_string += fiop::op_start_char;
	this->temp_string += std::to_string(fiop::load_started); //#0 만들기
	for (
		std::list<Site*>::iterator each = this->person_to_export->sites.begin(); \
		each != this->person_to_export->sites.end();
		each++)
	{
		site_byte_input(*each);	//여기에서 #1~6이 만들어진다.
	}
	this->temp_string += fiop::op_start_char;
	this->temp_string += std::to_string(fiop::load_finished); //#9 만들기

	if (compile::active_encryption == true) //출력 파일에 암호화 옵션을 적용할지?
		encrypt(this->temp_string);
	this->fp << this->temp_string;
}
void Exporter::site_byte_input(Site * temp_site)
{
	this->temp_string += fiop::op_start_char;
	this->temp_string += std::to_string(fiop::site_assemblying_started); //#1 만들기
	this->temp_string += temp_site->site_name;
	this->temp_string += fiop::arg_input_finished_char;

	for (
		std::list<Account*>::iterator each = temp_site->accounts.begin(); \
		each != temp_site->accounts.end();
		each++)
	{
		account_byte_input(*each); //여기에서 #2~#5가 만들어진다.
	}
	this->temp_string += fiop::op_start_char;
	this->temp_string += std::to_string(fiop::site_assemblying_finished); //#6
}
void Exporter::account_byte_input(Account * temp_account)
{
	this->temp_string += fiop::op_start_char;
	this->temp_string += std::to_string(fiop::account_id_assemblying);//#2
	this->temp_string += temp_account->ID;
	this->temp_string += fiop::arg_input_finished_char;

	this->temp_string += fiop::op_start_char;
	this->temp_string += std::to_string(fiop::account_pw_assemblying);//#3
	this->temp_string += temp_account->PW;
	this->temp_string += fiop::arg_input_finished_char;

	this->temp_string += fiop::op_start_char;
	this->temp_string += std::to_string(fiop::account_ud_assemblying);//#4
	this->temp_string += temp_account->update_time;
	this->temp_string += fiop::arg_input_finished_char;

	this->temp_string += fiop::op_start_char;
	this->temp_string += std::to_string(fiop::account_memo_assemblying);//#5
	if (std::string(temp_account->memo) == "")
		this->temp_string += fiop::non_arg_char;
	else
	{
		this->temp_string += temp_account->memo;
		this->temp_string += fiop::arg_input_finished_char;
	}
}
void Exporter::save()
{
	if (compile::generate_junk_bytes == true)
		junk_byte_input();
	person_byte_input();
	if (compile::generate_junk_bytes == true)
		junk_byte_input();
	Log_Recorder::clear_itself();
}
