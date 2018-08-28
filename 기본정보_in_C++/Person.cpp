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
		if ((*each)->get_site_name() == site_name)
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
		if ((*each)->get_site_name() == site_name)
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
	if (temp_site->get_site_name() == err_exp::abnormal_Site_site_name)
	{
		delete temp_site;
		return nullptr;
	}
	return temp_site;
}
void Person::add()
{
	using namespace option::argument::instruction::add;
	try {
		if (Order::get_type() == add_site_only) { //����Ʈ�� �߰�
			add_site(Order::get_content(new_site_name_position));
		}
		else { //����Ʈ�� ���� �߰�
			if (Order::get_type() == add_account_without_memo) {
				Order::set_content(new_memo_position, "");
				Order::set_token_count(Order::get_token_count()+1);  // -> type��  add_account_with_memo ( �� )�� �ȴ�.
			}
			if (Order::get_type() == add_account_with_memo) {
				add_account(
					Order::get_content(new_site_name_position),
					Order::get_content(new_id_position),
					Order::get_content(new_pw_position),
					Order::get_content(new_memo_position)
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
		if (Order::get_type() == argument::instruction::add::add_account_with_memo)
			Log_Recorder::add_log(Order::get(), "����Ʈ �߰� ����, " + site_name);
		else
			Log_Recorder::add_log(Order::get(), "����Ʈ �߰�, " + site_name);
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
void Person::del()
{
	using namespace option::argument::instruction::del;
	try {
		if (Order::get_type() == delete_site) {
			del_site(Order::get_content(site_name_position));
		}
		else if (Order::get_type() == delete_account) {
			del_account(Order::get_content(site_name_position), Order::get_content(id_position));
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

void Person::sort(bool is_ascending)
{
	if(is_ascending)
		this->sites.sort([](Site*A_site, Site* B_site) {return A_site->get_site_name()[0] < B_site->get_site_name()[0]; });
	else
		this->sites.sort([](Site*A_site, Site* B_site) {return A_site->get_site_name()[0] > B_site->get_site_name()[0]; });
}

void Person::del_site(std::string site_name)
{
	for (std::list<Site*>::iterator each = this->sites.begin(); each != this->sites.end(); )
	{
		if ((*each)->get_site_name() == site_name)
		{
			int account_count = (*each)->get_account_count();
			std::string to_record =
				"������ ����Ʈ �̸� : " + site_name + ", " + std::to_string(account_count) + "���� ������ �����߾���.";
			(*each)->clean_itself();
			delete (*each);
			this->sites.erase(each);
			this->site_count--;
			Log_Recorder::add_log(Order::get(), to_record);
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
void Person::update()
{
	using namespace option::argument::instruction::update;
	if (Order::get_type() == modify_site_name) {
		update_site_name(
			Order::get_content(site_name_position),
			Order::get_content(new_site_name_position)
		);
	}
	else if (Order::get_type() == modify_account_attribute) {
		update_account_attribute(
			Order::get_content(site_name_position),
			Order::get_content(id_position),
			Order::get_content(attribute_select_position),
			Order::get_content(new_attribute_value_position)
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