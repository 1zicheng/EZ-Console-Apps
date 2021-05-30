#pragma once

#include "Worker.hpp"

class Boss :public Worker
{
public:
	Boss(int id, string name);

	//显示个人信息
	virtual void ShowInfo();
};


