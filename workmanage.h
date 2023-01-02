#pragma once

#include<iostream>
#include<fstream>
using namespace std;

#include"worker.h"
#include"manager.h"
#include"employee.h"
#include"boss.h"

#define filename "empfile.txt"

class workmanage
{
public:
	workmanage();

	void show_menu();

	void exitsystem();

	void add_emp();

	void save();

	//�ж��ļ��Ƿ�Ϊ��
	bool m_fileisempty;

	//ͳ���ļ�������
	int get_empnum();

	//��ʼ��Ա��
	void init_emp();

	//��ʾְ��
	void show_emp();

	//ɾ��ְ��
	void del_emp();
	int isexist(int id);

	//�޸�ְ��
	void mod_emp();

	//����ְ��
	void find_emp();

	//����ְ��
	void sort_emp();

	//�������
	void clean_file();

	~workmanage();

	int m_empnum;
	worker ** m_emparray;

};
