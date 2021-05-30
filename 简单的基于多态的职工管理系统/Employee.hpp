#pragma once

#include "Worker.hpp"

class Employee: public Worker
{
public:
	Employee(int id, string name);

	//显示个人信息
	virtual void ShowInfo();

};

