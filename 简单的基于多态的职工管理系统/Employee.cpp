#include "Employee.hpp"

Employee::Employee(int id, string name)
{
	this->m_ID = id;
	this->m_Name = name;
	this->m_Post = "普通职工";
}

void Employee::ShowInfo()
{
	cout << "职工编号:" << this->m_ID
		<< "\t职工姓名:" << this->m_Name
		<< "\t职工岗位:" << this->m_Post << endl;
}

