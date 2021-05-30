#include "Manager.hpp"

Manager::Manager(int id, string name)
{
	this->m_ID = id;
	this->m_Name = name;
	this->m_Post = "高层管理";
}

void Manager::ShowInfo()
{
	cout << "职工编号:" << this->m_ID
		<< "\t职工姓名:" << this->m_Name
		<< "\t职工岗位:" << this->m_Post << endl;
}