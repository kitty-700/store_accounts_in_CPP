#include "Person.h"
namespace err_exp = option::expression::error;
Person::Person() : 
	site_count(0), 
	is_alive(false) {}
Person::~Person()
{
	clean_itself();
}
void Person::operator+=(Site * site)
{
	this->sites.push_back(site);
	this->site_count++;
}
int Person::get_site_count() const
{
	return this->site_count;
}
void Person::print_site_number(int site_number)
{
	std::cout << "[";
	std::cout.fill('0');
	std::cout.width(General_Function::get_cipher(this->site_count));
	std::cout << site_number << "] ";
}
void Person::set_is_alive(bool is_alive)
{
	this->is_alive = is_alive;
}
bool Person::get_is_alive() const
{
	return this->is_alive;
}

void Person::clean_itself()
{//Person �� ����, �����Ҵ��� ��� ��� ���ؼ� �Ҵ� �����Ѵ�.
	for (std::list<Site*>::iterator position = this->sites.begin(); position != this->sites.end(); )
	{
		del_site((*position)->get_site_name());
		position = this->sites.begin();
	}
}

Site* Person::find_Site(std::string site_name)
{
	for (std::list<Site*>::iterator each = this->sites.begin(); each != this->sites.end(); each++)
		if (*(*each) == site_name)
			return (*each);
	return nullptr;
}
Site * Person::find_Site(int site_number)
{
	int count = 0;
	for (
		std::list<Site*>::iterator each = this->sites.begin(); \
		each != this->sites.end();
		each++, count++)
	{
		if (count == site_number - option::expression::normal::index_fix)
			return *(each);
	}
	return nullptr;
}
int Person::find_Site_number(std::string site_name)
{
	int count = 1;
	for (
		std::list<Site*>::iterator each = this->sites.begin(); \
		each != this->sites.end();
		each++, count++)
	{
		if (*(*each) == site_name)
			return count;
	}
	return -1;
}
bool Person::is_redundancy_site_name(std::string site_name)
{
	if (find_Site(site_name) == nullptr)
		return false;
	return true;
}
Site * Person::make_site(std::string site_name)
{	//site_name�� ������ Site�� �� ���� �ÿ� nullptr�� ��ȯ. ��������� �� ����Ʈ�� �ּҸ� ��ȯ�Ѵ�.
	Site * temp_site = new Site();
	temp_site->update_site_name("site_name", site_name);
	if (*temp_site == err_exp::abnormal_Site_site_name)
	{
		delete temp_site;
		return nullptr;
	}
	return temp_site;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////ADD///////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////ADD///////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void Person::add(Order_token * order)
{
	using namespace option::argument::instruction::add;
	try {
		if (order->token_count == add_site_only) { //����Ʈ�� �߰�
			add_site(order->tokens[new_site_name_position]);
		}
		else { //����Ʈ�� ���� �߰�
			if (order->token_count == add_account_without_memo) {
				order->tokens[new_memo_position] = "";
				order->token_count++;  // -> type��  add_account_with_memo ( �� )�� �ȴ�.
			}
			if (order->token_count == add_account_with_memo) {
				add_account(
					order->tokens[new_site_name_position],
					order->tokens[new_id_position],
					order->tokens[new_pw_position],
					order->tokens[new_memo_position]
				);
			}
			else {
				throw err_exp::msg_unsupport_order_form;
			}
		}
	}
	catch (std::string error_message) {
		std::cout << error_message << std::endl;
		return;
	}
}
Site * Person::add_site(std::string site_name)
{	//person�� ���������� site�� �߰��Ǿ����� ����Ʈ�� �ּҸ�, �߰� ���� �ÿ��� nullptr�� ��ȯ.
	try {
		if (is_redundancy_site_name(site_name) == true)
			throw site_name + err_exp::msg_already_existing_site_name;
		Site * temp_site = make_site(site_name);
		if (temp_site == nullptr)
			throw err_exp::msg_cant_make_site;
		//������ ����� �������� �Ǵٴ� ���� �Ͽ� �ٸ��� �����Ѵ�. (Site::update_site_name () ������ ���� ����ش�.)
		*(this) += temp_site;
		if (Main_Order::get_type() == argument::instruction::add::add_account_with_memo ||
			//���� ����� �迡 ���޾� ����Ʈ�� ������ ���
			Main_Order::get_type() == argument::instruction::add::add_site_only)
			//������ ����Ʈ ��ü�� ó������ ����� ���
			Log_Recorder::record_add_site(Main_Order::get(), site_name);
		return temp_site;
	}
	catch (std::string error_message) {
		std::cout << error_message << std::endl;
		return nullptr;
	}
}
void Person::add_account(std::string site_name, std::string ID, std::string PW, std::string memo )
{	//������ �߰��ϴ� �Լ�������, ���� ����Ʈ�� ���ٸ� ����Ʈ�� ������ �Ŀ� �߰��Ѵ�.
	Site * temp_site;
	if ((temp_site = find_Site(site_name)) == nullptr)
	{
		temp_site = add_site(site_name); //���� ����Ʈ �̸��̾��ٸ� add_site()�� ������ ���� ����������? -> �ִ�. ������ ���ڰ� ���ԵǾ��� ��
		if (temp_site == nullptr)
			return;
	}
	temp_site->add_account(ID, PW, memo);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////DEL///////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////DEL///////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void Person::del(Order_token * order)
{
	using namespace option::argument::instruction::del;
	try {
		if (order->token_count == delete_site) {
			del_site(
				order->tokens[site_name_position]);
		}
		else if (order->token_count == delete_account) {
			del_account(
				order->tokens[site_name_position], 
				order->tokens[id_position]);
		}
		else {
			throw err_exp::msg_unsupport_order_form;
		}
	}
	catch (std::string error_message) {
		std::cout << error_message << std::endl;
		return;
	}
}
void Person::del_site(std::string site_name)
{
	for (std::list<Site*>::iterator each = this->sites.begin(); each != this->sites.end(); )
	{
		if (*(*each) == site_name)
		{
			int account_count = (*each)->get_account_count();
			std::string to_record =
				"������ ����Ʈ �̸� : " + site_name + ", " + std::to_string(account_count) + "���� ������ �����߾���.";
			if (Main_Order::get_type() == argument::instruction::del::delete_site)
				Log_Recorder::pre_recording_procedure(); //�α׶����ְ�
			(*each)->clean_itself();
			delete (*each);
			this->sites.erase(each);
			this->site_count--;
			return;
		}
		each++;
	}
	try {
		throw err_exp::msg_no_existing_site_name;
	}
	catch (std::string error_message) {
		std::cout << error_message << std::endl;
		return;
	}
}
void Person::del_account(std::string site_name, std::string ID)
{
	Site * temp_site = find_Site(site_name);
	try {
		if (temp_site == nullptr)
			throw err_exp::msg_no_existing_site_name;
	}
	catch (std::string error_message) {
		std::cout << error_message << std::endl;
		return;
	}
	temp_site->del_account(ID);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////UPDATE///////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////UPDATE///////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void Person::update(Order_token * order)
{
	using namespace option::argument::instruction::update;
	if (order->token_count == modify_site_name) {
		update_site_name(
			order->tokens[site_name_position],
			order->tokens[new_site_name_position]
		);
	}
	else if (order->token_count == modify_account_attribute) {
		update_account_attribute(
			order->tokens[site_name_position],
			order->tokens[id_position],
			order->tokens[attribute_select_position],
			order->tokens[new_attribute_value_position]
		);
	}
	else {
		std::cout << err_exp::msg_unsupport_order_form << std::endl;
	}
}
void Person::update_site_name(std::string site_name, std::string new_site_name)
{
	Site* temp_site = find_Site(site_name);
	try {
		if (temp_site == nullptr)
			throw err_exp::msg_no_existing_site_name;
		if (is_redundancy_site_name(new_site_name) == true)
			throw site_name + err_exp::msg_already_existing_site_name;
	}
	catch (std::string error_message) {
		std::cout << error_message << std::endl;
		return;
	}
	temp_site->update_site_name("site_name", new_site_name);
}

void Person::update_account_attribute(std::string site_name, std::string ID, std::string what_attribute, std::string new_value)
{
	Site* temp_site = find_Site(site_name);
	try {
		if (temp_site == nullptr)
			throw err_exp::msg_no_existing_site_name;
	}
	catch (std::string error_message) {
		std::cout << error_message << std::endl;
		return;
	}
	temp_site->update_account_attribute(ID, what_attribute, new_value);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////SHOW/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void Person::show_one_site_information(Site * site, int site_number)
{
	namespace color = option::parameters::console_color;
	SET_CONSOLE_COLOR(color::site_name_color);
	print_site_number(site_number);
	std::cout << site->get_site_name() << std::endl;
	SET_CONSOLE_COLOR_DEFAULT;
	site->show_account_information();
}

void Person::show_all_sites_information()
{	// ��ɾ� ll �ÿ�, ��� ����Ʈ �̸��� �׿� ���� ���� ������ ���� �����Ѵ�.
	int count = 1;
	for (
		std::list<Site*>::iterator each = this->sites.begin(); \
		each != this->sites.end(); \
		each++, count++)
	{ 
		show_one_site_information(*(each), count);
	}
}

void Person::show_site_name_list()
{	// ��ɾ� ls �ÿ�, ����Ʈ �̸� ����� ����Ѵ�.
	int count = 1;
	namespace color = option::parameters::console_color;
	SET_CONSOLE_COLOR(color::site_name_color);
	for (std::list<Site*>::iterator each = this->sites.begin(); each != this->sites.end(); each++)
	{
		print_site_number(count);
		std::cout << (*each)->get_site_name();
		std::cout << "     ( " << (*each)->get_account_count() << " ���� ���� �� )" << std::endl;
		count++;
	}
	SET_CONSOLE_COLOR_DEFAULT;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////SORT//////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void Person::sort(bool is_ascending)
{
	if (is_ascending)
		this->sites.sort([](Site*A_site, Site* B_site) {return *A_site < *B_site; });
	else
		this->sites.sort([](Site*A_site, Site* B_site) {return *A_site > *B_site; });
}
