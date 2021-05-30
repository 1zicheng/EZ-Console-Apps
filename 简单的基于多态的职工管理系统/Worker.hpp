#pragma once

#include <iostream>
#include <string>
using namespace std;

class Worker
{
public:
	//显示个人信息
	virtual void ShowInfo() = 0;

	int m_ID=0;
	string m_Name;
	string m_Post;
};