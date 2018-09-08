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
	//	friend void Importer::make_a_person(); //이건 왜 안 되는지? Importer의 멤버변수로 존재해서 클래스단에서 friend 해줘야하나?
	std::list<Site*> sites;
	int site_count;
	bool is_alive; //만일 파일로부터 정보들을 적절히 적재했다면 true로 셋한다.
private:
	bool is_redundancy_site_name(std::string site_name);
	Site * make_site(std::string site_name);	//사이트 하나를 생성
	Site * add_site(std::string site_name);	//사이트 하나를 추가 (여기서 make_site호출)
	void add_account(std::string site_name, std::string ID, std::string PW, std::string memo = "");	//계정 하나를 추가
	void del_site(std::string site_name);	//사이트 하나를 삭제
	void del_account(std::string site_name, std::string ID);	//계정 하나를 삭제
	void update_site_name(std::string site_name, std::string new_site_name); //사이트 이름 업데이트
	void update_account_attribute(std::string site_name, std::string ID, std::string what_attribute, std::string new_value); 
																																									//사이트 내 계정 업데이트
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
	void clean_itself();	//Person 객체가 가진 모든 사이트 정보와 계정 정보를 해체한다. (삭제되는 것이 아니라 프로그램 종료)
};
#endif