#include <iostream>
#include <string>
using namespace std;
#include "WorkerManager.hpp"

int main()
{
	WorkerManager wm;
	unsigned short usChoice;
	while (1)
	{
		wm.ShowMenu();
CHOICE:	cout << "请输入您的选择:";
		cin >> usChoice;
		switch (usChoice)
		{
		case 1:	//退出
			wm.ExitSys();
		case 2: //显示所有人
			wm.ShowAllEmp();
			system("pause");
			goto CHOICE;
		case 3: //增加;
			wm.AddPerson();
			break;
		case 4:	//删除
			wm.DelPerson();
			break;
		case 5:	//修改
			wm.ModifyPerson();
			break;
		case 6: //查找
			wm.FindPerson();
			break;
		case 7: //排序
			wm.SortPerson();
			break;
		case 8: //清空
			wm.ClrList();
			break;
		default:
			cout << "输入有误!" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	
	system("pasue");
	return 0;
}