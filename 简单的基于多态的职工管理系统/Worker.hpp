#pragma once

#include <iostream>
#include <string>
using namespace std;

class Worker
{
public:
	//��ʾ������Ϣ
	virtual void ShowInfo() = 0;

	int m_ID=0;
	string m_Name;
	string m_Post;
};