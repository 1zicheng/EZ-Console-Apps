#include "Manager.hpp"

Manager::Manager(int id, string name)
{
	this->m_ID = id;
	this->m_Name = name;
	this->m_Post = "�߲����";
}

void Manager::ShowInfo()
{
	cout << "ְ�����:" << this->m_ID
		<< "\tְ������:" << this->m_Name
		<< "\tְ����λ:" << this->m_Post << endl;
}