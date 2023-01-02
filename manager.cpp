#include"manager.h"

manager::manager(int id, string name, int did)
{
	this->m_id = id;
	this->m_name = name;
	this->m_deptid = did;

}

void manager::showinfo()
{
	cout << "职工编号：" << this->m_id
		<< "\t职工姓名：" << this->m_name
		<< "\t岗位：" << this->getdeptname()
		<< "\t职责：完成老板任务" << endl;
}
string manager::getdeptname()
{
	return string("管理");
}