#pragma once

#include "Worker.hpp"

class Boss :public Worker
{
public:
	Boss(int id, string name);

	//��ʾ������Ϣ
	virtual void ShowInfo();
};


