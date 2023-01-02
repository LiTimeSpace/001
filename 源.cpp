#include<iostream>
#include<string>
#include<fstream>

using namespace std;

#include"workmanage.h"
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"




int main()
{

	//worker* worker = NULL;
	//worker = new employee(1, "tom", 1);
	//worker->showinfo();
	//delete worker;


	//worker = new manager(2, "ham", 2);
	//worker->showinfo();
	//delete worker;

	//worker = new boss(3, "big", 3);
	//worker->showinfo();
	//delete worker;

	workmanage m;
	int choice = 0;
	
	while (true)
	{
		m.show_menu();
		cout << "输入选择" << endl;
		cin >> choice;

		switch (choice)
		{
		case 0:
			m.exitsystem();//退出
			break;
		case 1:
			m.add_emp();//添加职工
			break;
		case 2:
			m.show_emp();
			break;
		case 3:
			m.del_emp();
			break;
		case 4:
			m.mod_emp();
			break;
		case 5:
			m.find_emp();
			break;
		case 6:
			m.sort_emp();
			break;
		case 7:
			m.clean_file();
			break;
		default:
			system("cls");
			break;
		}
	}
	
	return 0;
} 