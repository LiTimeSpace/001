#include"workmanage.h"


workmanage::workmanage()
{
	//1 文件不存在

	ifstream ifs;
	ifs.open(filename, ios::in);

	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;

		//初始化
		this->m_empnum = 0;
		this->m_emparray = NULL;
		this->m_fileisempty = true;
		ifs.close();
		//return;
	}

	//2 文件存在 数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof())//只有一个结尾函数为真
	{
		//文件为空
		cout << "文件为空" << endl;
		this->m_empnum = 0;
		this->m_emparray = NULL;
		this->m_fileisempty = true;
		ifs.close();
		//return;
	}

	//3 文件存在 数据存在
	int num = this->get_empnum();
	cout << "职工人数为" << num << endl;
	this->m_empnum = num;
	this->m_emparray = new worker * [this->m_empnum];//文件中数据存在数组中，重新打开再次添加就不会删文件了
	this->init_emp();

	for (int i = 0; i < this->m_empnum; i++)
	{
		cout<<  this->m_emparray[i]->m_id << " "
			<< this->m_emparray[i]->m_name << " "
			<< this->m_emparray[i]->getdeptname() << endl;
	}
}


void workmanage::show_menu()
{
	cout << "*****************************" << endl;
	cout << "********* welcome ***********" << endl;
	cout << "********** 0 退出 ***********" << endl;
	cout << "********** 1 增加 ***********" << endl;
	cout << "********** 2 显示 ***********" << endl;
	cout << "********** 3 删除 ***********" << endl;
	cout << "********** 4 修改 ***********" << endl;
	cout << "********** 5 查找 ***********" << endl;
	cout << "********** 6 编号排序********" << endl;
	cout << "********** 7 清空 ***********" << endl;
	cout << endl;
}

void workmanage::exitsystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

void workmanage::add_emp()
{
	cout<< "请输入添加职工数目" << endl;
	int addnum = 0;
	cin >> addnum;

	if (addnum > 0)
	{
		int newsize = this->m_empnum + addnum;//计算新空间大小
		//开辟新空间
		worker** newspace = new worker * [newsize];
		//拷贝旧数据到新空间
		if (this->m_emparray != NULL)
		{
			for (int i = 0; i < this->m_empnum; i++)
			{
				newspace[i] = this->m_emparray[i];
			}
			//添加数据
			for (int i = 0; i < addnum; i++)
			{
				int id;
				string name;
				int dselect;
				cout << "请输入第" << i + 1 << "个新职工编号" << endl;
				cin >> id;

				int index = this->isexist(id);
				if (index == -1)
				{

					cout << "请输入第" << i + 1 << "个新职工姓名" << endl;
					cin >> name;

					cout << "请选择该职工岗位" << endl;
					cout << "1 职工" << endl;
					cout << "2 管理" << endl;
					cout << "3 老板" << endl;
					cin >> dselect;

					worker* worker = NULL;
					switch (dselect)
					{
					case 1:
						worker = new employee(id, name, 1);
						break;
					case 2:
						worker = new manager(id, name, 2);
						break;
					case 3:
						worker = new boss(id, name, 3);
						break;
					default:
						break;
					}
					//将创建的保存在数组中
					newspace[this->m_empnum + i] = worker;

					delete[] this->m_emparray;
					this->m_emparray = newspace;
					this->m_empnum = newsize;

					this->m_fileisempty = false;//文件不为空
					cout << "成功添加了" << addnum << "人" << endl;
					this->save();
				}
				else
				{
					cout << "重复编号" << endl;
				}
			}
		}
	}
	else
	{
		cout << "数据有误" << endl;
	}
	system("pause");//暂停效果
	system("cls");//清屏效果
}


void workmanage::save()
{
	ofstream ofs;
	ofs.open(filename, ios::out);
	for (int i = 0; i < this->m_empnum; i++)
	{
		ofs << this->m_emparray[i]->m_id << " "
			<< this->m_emparray[i]->m_name << " "
			<< this->m_emparray[i]->m_deptid << endl;

	}
	ofs.close();
}

int workmanage::get_empnum()
{
	ifstream ifs;
	ifs.open(filename, ios::in);

	int id;
	string name;
	int did;

	int num = 0;

	while (ifs >> id && ifs >> name && ifs >> did)
	{
		num++;
		
	}
	return num;
}


void workmanage::init_emp()
{
	ifstream ifs;
	ifs.open(filename, ios::in);

	int id;
	string name;
	int did;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> did)
	{
		worker* worker = NULL;


		if (did == 1)
		{
			worker = new employee(id, name, did);
		}
		else if (did == 2)
		{
			worker =new manager(id, name, did);
		}
		else
		{
			worker = new boss(id, name, did);
		}

		this->m_emparray[index] = worker;
		index++;
	}
	ifs.close();
}

void workmanage::show_emp()
{
	if (this->m_fileisempty)
	{
		cout << "文件不存在或者为空" << endl;
	}
	else
	{
		for (int i = 0; i < m_empnum; i++)
		{
			this->m_emparray[i]->showinfo();
		}
	}
	system("pause");
	system("cls");
}

int workmanage::isexist(int id)//判断职工是否存在
{
	int index = -1;
	for (int i = 0; i < this->m_empnum; i++)
	{
		if(this->m_emparray[i]->m_id==id)
		{
			index = i;
			break;
		}
		
	}
	return index;
}

void workmanage::del_emp()
{
	if (this->m_fileisempty)
	{
		cout << "文件为空" << endl;
	}
	else
	{
		cout << "输入删除职工的编号" << endl;
		int id = 0;
		cin >> id;

		int index = this->isexist(id);
		if (index != -1)
		{
			for (int i = index; i < this->m_empnum - 1; i++)
			{
				this->m_emparray[i] = this->m_emparray[i + 1];

			}
			this->m_empnum--;
			if (m_empnum == 0)
			{
				this->m_fileisempty = true;
			}
			this->save();
			cout << "删除成功" << endl;
		}
		else
		{
			cout << "删除失败" << endl;
		}
	}
	system("pause");
	system("cls");
}


void workmanage::mod_emp()
{
	if (this->m_fileisempty)
	{
		cout << "文件为空" << endl;
	}
	else
	{
		cout << "输入修改的员工信息编号" << endl;
		int idd = 0;
		cin >> idd;

		int ret = this->isexist(idd);

		if (ret != -1)
		{
			delete this->m_emparray[ret];

			int newid = 0;
			string newname = "";
			int ddselect = 0;

			cout << "查到" << idd << "号职工编号，输入新编号" << endl;
			cin >> newid;
			cout << "请输入新姓名" << endl;
			cin >> newname;

			cout << "请选择新职工岗位" << endl;
			cout << "1 职工" << endl;
			cout << "2 管理" << endl;
			cout << "3 老板" << endl;
			cin >>ddselect;

			worker* worker = NULL;
			if (ddselect == 1)
			{
				worker = new employee(newid, newname, ddselect);
			}
			else if (ddselect == 2)
			{
				worker = new manager(newid, newname, ddselect);
			}
			else
			{
				worker = new boss(newid, newname, ddselect);
			}

			this->m_emparray[ret] = worker;
			cout << "修改成功" << this->m_emparray[ret]->m_deptid <<"号员工" << endl;

			this->save();


		}
		else
		{
			cout << "修改失败，查无此人" << endl;
		}

	}
	system("pause");
	system("cls");
}

void workmanage::find_emp()
{
	if (this->m_fileisempty)
	{
		cout << "文件为空" << endl;
	}
	else
	{
		cout << "请输入查找方式" << endl;
		cout << "1 按照编号" << endl;
		cout << "2 按照姓名" << endl;

		int select = 0;
		cin >> select;

		if (select == 1)
		{
			int id;
			cout << "输入查找职工的编号" << endl;
			cin >> id;

			int ret = isexist(id);
			if (ret != -1)//找到职工
			{
				cout << "查找成功" << endl;
				this->m_emparray[ret]->showinfo();
			}
			else
			{
				cout << "查找失败" << endl;
			}

		}
		else if (select == 2)
		{
			string name;
			cout << "输入查找职工的姓名" << endl;
			cin >> name;

			bool flag = false;

			for (int i = 0; i < m_empnum; i++)
			{
				if (name == this->m_emparray[i]->m_name)
				{
					cout << "查找成功" << endl;
					this->m_emparray[i]->showinfo();
					flag = true;
				}
			}
			if (flag == false)
			{
				cout << "查找失败" << endl;
			}
			
		}
		else
		{
			cout << "输入有误" << endl;
		}
	}
}

void workmanage::sort_emp()
{
	if (this->m_fileisempty)
	{
		cout << "文件为空" << endl;
	}
	else
	{
		cout << "请输入编号排序方式" << endl;
		cout << "1 升序排列" << endl;
		cout << "2 降序排列" << endl;

		int select = 0;
		cin >> select;

		if (select == 1)
		{
			for (int i = 0; i < m_empnum; i++)
			{
				int temp=i;
				for (int j = i + 1; j < m_empnum; j++)
				{
					if (m_emparray[temp]->m_id > m_emparray[j]->m_id)
					{
						temp = j;
					}
					if (i != temp)
					{
						worker* tem = m_emparray[i];
						m_emparray[i] = m_emparray[j];
						m_emparray[j] = tem;
					}
				}
			}
		}
		else if (select == 2)
		{
			for (int i = 0; i < m_empnum; i++)
			{
				int temp = i;
				for (int j = i + 1; j < m_empnum; j++)
				{
					if (m_emparray[temp]->m_id < m_emparray[j]->m_id)
					{
						temp = j;
					}
					if (i != temp)
					{
						worker* tem = m_emparray[i];
						m_emparray[i] = m_emparray[j];
						m_emparray[j] = tem;
					}
				}
			}
		}
		else
		{
			cout << "输入有误" << endl;
		}
		this->save();
		this->show_emp();
	}
}


void workmanage::clean_file()
{
	cout << "确定清空？" << endl;
	cout << "1 确定" << endl;
	cout << "2 取消" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		ofstream ofs(filename, ios::trunc);
		ofs.close();

		if (this->m_emparray != NULL)
		{
			for (int i = 0; i < m_empnum; i++)
			{
				if (this->m_emparray[i] != NULL)
				{
					delete this->m_emparray[i];
				}
			}
			this->m_empnum = 0;
			delete[] this->m_emparray;
			this->m_emparray = NULL;
			this->m_fileisempty = true;
		}
		cout << "清空成功" << endl;
	}
	else if (select == 2)
	{
		return;
	}
}

workmanage::~workmanage()
{
	if (this->m_emparray != NULL)
	{
		for (int i = 0; i < m_empnum; i++)
		{
			if (this->m_emparray[i] != NULL)
			{
				delete this->m_emparray[i];
			}
		}
		delete[] this->m_emparray;
		this->m_emparray = NULL;
	}
}
