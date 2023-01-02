#include"workmanage.h"


workmanage::workmanage()
{
	//1 �ļ�������

	ifstream ifs;
	ifs.open(filename, ios::in);

	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;

		//��ʼ��
		this->m_empnum = 0;
		this->m_emparray = NULL;
		this->m_fileisempty = true;
		ifs.close();
		//return;
	}

	//2 �ļ����� ����Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())//ֻ��һ����β����Ϊ��
	{
		//�ļ�Ϊ��
		cout << "�ļ�Ϊ��" << endl;
		this->m_empnum = 0;
		this->m_emparray = NULL;
		this->m_fileisempty = true;
		ifs.close();
		//return;
	}

	//3 �ļ����� ���ݴ���
	int num = this->get_empnum();
	cout << "ְ������Ϊ" << num << endl;
	this->m_empnum = num;
	this->m_emparray = new worker * [this->m_empnum];//�ļ������ݴ��������У����´��ٴ���ӾͲ���ɾ�ļ���
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
	cout << "********** 0 �˳� ***********" << endl;
	cout << "********** 1 ���� ***********" << endl;
	cout << "********** 2 ��ʾ ***********" << endl;
	cout << "********** 3 ɾ�� ***********" << endl;
	cout << "********** 4 �޸� ***********" << endl;
	cout << "********** 5 ���� ***********" << endl;
	cout << "********** 6 �������********" << endl;
	cout << "********** 7 ��� ***********" << endl;
	cout << endl;
}

void workmanage::exitsystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

void workmanage::add_emp()
{
	cout<< "���������ְ����Ŀ" << endl;
	int addnum = 0;
	cin >> addnum;

	if (addnum > 0)
	{
		int newsize = this->m_empnum + addnum;//�����¿ռ��С
		//�����¿ռ�
		worker** newspace = new worker * [newsize];
		//���������ݵ��¿ռ�
		if (this->m_emparray != NULL)
		{
			for (int i = 0; i < this->m_empnum; i++)
			{
				newspace[i] = this->m_emparray[i];
			}
			//�������
			for (int i = 0; i < addnum; i++)
			{
				int id;
				string name;
				int dselect;
				cout << "�������" << i + 1 << "����ְ�����" << endl;
				cin >> id;

				int index = this->isexist(id);
				if (index == -1)
				{

					cout << "�������" << i + 1 << "����ְ������" << endl;
					cin >> name;

					cout << "��ѡ���ְ����λ" << endl;
					cout << "1 ְ��" << endl;
					cout << "2 ����" << endl;
					cout << "3 �ϰ�" << endl;
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
					//�������ı�����������
					newspace[this->m_empnum + i] = worker;

					delete[] this->m_emparray;
					this->m_emparray = newspace;
					this->m_empnum = newsize;

					this->m_fileisempty = false;//�ļ���Ϊ��
					cout << "�ɹ������" << addnum << "��" << endl;
					this->save();
				}
				else
				{
					cout << "�ظ����" << endl;
				}
			}
		}
	}
	else
	{
		cout << "��������" << endl;
	}
	system("pause");//��ͣЧ��
	system("cls");//����Ч��
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
		cout << "�ļ������ڻ���Ϊ��" << endl;
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

int workmanage::isexist(int id)//�ж�ְ���Ƿ����
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
		cout << "�ļ�Ϊ��" << endl;
	}
	else
	{
		cout << "����ɾ��ְ���ı��" << endl;
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
			cout << "ɾ���ɹ�" << endl;
		}
		else
		{
			cout << "ɾ��ʧ��" << endl;
		}
	}
	system("pause");
	system("cls");
}


void workmanage::mod_emp()
{
	if (this->m_fileisempty)
	{
		cout << "�ļ�Ϊ��" << endl;
	}
	else
	{
		cout << "�����޸ĵ�Ա����Ϣ���" << endl;
		int idd = 0;
		cin >> idd;

		int ret = this->isexist(idd);

		if (ret != -1)
		{
			delete this->m_emparray[ret];

			int newid = 0;
			string newname = "";
			int ddselect = 0;

			cout << "�鵽" << idd << "��ְ����ţ������±��" << endl;
			cin >> newid;
			cout << "������������" << endl;
			cin >> newname;

			cout << "��ѡ����ְ����λ" << endl;
			cout << "1 ְ��" << endl;
			cout << "2 ����" << endl;
			cout << "3 �ϰ�" << endl;
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
			cout << "�޸ĳɹ�" << this->m_emparray[ret]->m_deptid <<"��Ա��" << endl;

			this->save();


		}
		else
		{
			cout << "�޸�ʧ�ܣ����޴���" << endl;
		}

	}
	system("pause");
	system("cls");
}

void workmanage::find_emp()
{
	if (this->m_fileisempty)
	{
		cout << "�ļ�Ϊ��" << endl;
	}
	else
	{
		cout << "��������ҷ�ʽ" << endl;
		cout << "1 ���ձ��" << endl;
		cout << "2 ��������" << endl;

		int select = 0;
		cin >> select;

		if (select == 1)
		{
			int id;
			cout << "�������ְ���ı��" << endl;
			cin >> id;

			int ret = isexist(id);
			if (ret != -1)//�ҵ�ְ��
			{
				cout << "���ҳɹ�" << endl;
				this->m_emparray[ret]->showinfo();
			}
			else
			{
				cout << "����ʧ��" << endl;
			}

		}
		else if (select == 2)
		{
			string name;
			cout << "�������ְ��������" << endl;
			cin >> name;

			bool flag = false;

			for (int i = 0; i < m_empnum; i++)
			{
				if (name == this->m_emparray[i]->m_name)
				{
					cout << "���ҳɹ�" << endl;
					this->m_emparray[i]->showinfo();
					flag = true;
				}
			}
			if (flag == false)
			{
				cout << "����ʧ��" << endl;
			}
			
		}
		else
		{
			cout << "��������" << endl;
		}
	}
}

void workmanage::sort_emp()
{
	if (this->m_fileisempty)
	{
		cout << "�ļ�Ϊ��" << endl;
	}
	else
	{
		cout << "������������ʽ" << endl;
		cout << "1 ��������" << endl;
		cout << "2 ��������" << endl;

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
			cout << "��������" << endl;
		}
		this->save();
		this->show_emp();
	}
}


void workmanage::clean_file()
{
	cout << "ȷ����գ�" << endl;
	cout << "1 ȷ��" << endl;
	cout << "2 ȡ��" << endl;

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
		cout << "��ճɹ�" << endl;
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
