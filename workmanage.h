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

	//判断文件是否为空
	bool m_fileisempty;

	//统计文件中人数
	int get_empnum();

	//初始化员工
	void init_emp();

	//显示职工
	void show_emp();

	//删除职工
	void del_emp();
	int isexist(int id);

	//修改职工
	void mod_emp();

	//查找职工
	void find_emp();

	//排序职工
	void sort_emp();

	//清空数据
	void clean_file();

	~workmanage();

	int m_empnum;
	worker ** m_emparray;

};
