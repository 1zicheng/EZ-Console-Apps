#pragma once
#include <fstream>
#include "Worker.hpp"
#include "Employee.hpp"
#include "Manager.hpp"
#include "Boss.hpp"

#define FILENAME "empFile.txt"

class WorkerManager
{
public:
	WorkerManager();
	~WorkerManager();
	void ShowMenu();
	void ExitSys();
	void ShowAllEmp();
	void AddPerson();
	void DelPerson();
	void ModifyPerson();
	void FindPerson();
	void SortPerson();
	void ClrList();
	
	bool m_isFileEmpty = true;
	int m_CurrentNum=0;//��ǰְ������
	Worker** m_EmpArry = nullptr;//ְ������ָ��

private:
	void Save();
	int GetNum();
	void LoadEmp();
	bool isExist(int id,int* index);
	bool isExist(string name, int* index);
};

