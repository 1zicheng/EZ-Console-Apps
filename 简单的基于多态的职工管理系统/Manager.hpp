#pragma once

#include "Worker.hpp"

class Manager :public Worker
{
public:
	Manager(int id, string name);

	//显示个人信息
	virtual void ShowInfo();

};

