#pragma once

#include "Worker.hpp"

class Manager :public Worker
{
public:
	Manager(int id, string name);

	//��ʾ������Ϣ
	virtual void ShowInfo();

};

