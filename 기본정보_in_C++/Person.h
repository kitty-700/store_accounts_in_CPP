#pragma once
#ifndef _PERSON_H_
#define _PERSON_H_ 
#include <list>
#include <string>
#include <windows.h>
#include "Order.h"
#include "Options.h"
#include "Site.h"
#include "Structs.h"
class Importer;
class Person {
	friend class Importer;
	friend class Exporter;
	friend class Module_tester;
	//	friend void Importer::make_a_person(); //�̰� �� �� �Ǵ���? Importer�� ��������� �����ؼ� Ŭ�����ܿ��� friend ������ϳ�?
	std::list<Site*> sites;
	int site_count;
	bool is_alive; //���� ���Ϸκ��� �������� ������ �����ߴٸ� true�� ���Ѵ�.
private:
	bool is_redundancy_site_name(std::string site_name);
	Site * make_site(std::string site_name);	//����Ʈ �ϳ��� ����
	Site * add_site(std::string site_name);	//����Ʈ �ϳ��� �߰� (���⼭ make_siteȣ��)
	void add_account(std::string site_name, std::string ID, std::string PW, std::string memo = "");	//���� �ϳ��� �߰�
	void del_site(std::string site_name);	//����Ʈ �ϳ��� ����
	void del_account(std::string site_name, std::string ID);	//���� �ϳ��� ����
	void update_site_name(std::string site_name, std::string new_site_name); //����Ʈ �̸� ������Ʈ
	void update_account_attribute(std::string site_name, std::string ID, std::string what_attribute, std::string new_value); 
																																									//����Ʈ �� ���� ������Ʈ
	void set_is_alive(bool is_alive);

public:
	Person();
	~Person();
	void operator+=(Site * site);
	void show_site_name_list();
	void show_all_sites_information();
	void show_one_site_information(Site * site, int number);
	void print_site_number(int number);
	int get_site_count() const;
	bool get_is_alive() const;
	Site * find_Site(std::string site_name);
	Site * find_Site(int site_number);
	int find_Site_number(std::string site_name);
	void add(Order_token * order);
	void del(Order_token * order);
	void update(Order_token * order);
	void sort(bool is_ascending);
	void clean_itself();	//Person ��ü�� ���� ��� ����Ʈ ������ ���� ������ ��ü�Ѵ�. (�����Ǵ� ���� �ƴ϶� ���α׷� ����)
};
#endif