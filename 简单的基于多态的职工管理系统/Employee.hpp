#pragma once

#include "Worker.hpp"

class Employee: public Worker
{
public:
	Employee(int id, string name);

	//��ʾ������Ϣ
	virtual void ShowInfo();

};

