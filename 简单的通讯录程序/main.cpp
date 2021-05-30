#include<iostream>
#include<string>
#include<fstream>

using namespace std;

constexpr auto MAX = 100;//通讯录最大容量;

bool running = true;

typedef short int si;

//结束清屏函数
void EndClean()
{
	system("pause");
	system("cls");
}

//设置联系人结构体
struct Person
{
	string name;
	string sex;
	string age;
	string num;
};

//设置通讯录结构体
struct AddressBook
{
	Person personArr[MAX]; //通讯录最大容量
	si size = 0; //通讯录当前人员个数
};

//显示菜单函数
void ShowMenu()
{
	cout << endl;
	cout << "\t\t\t\t--------------通讯录管理系统V1.0-------------" << endl;
	cout << "\t\t\t\t*********************************************" << endl;
	cout << "\t\t\t\t************    1--添加联系人    ************" << endl;
	cout << "\t\t\t\t************    2--显示联系人    ************" << endl;
	cout << "\t\t\t\t************    3--删除联系人    ************" << endl;
	cout << "\t\t\t\t************    4--查找联系人    ************" << endl;
	cout << "\t\t\t\t************    5--修改联系人    ************" << endl;
	cout << "\t\t\t\t************    6--清空通讯录    ************" << endl;
	cout << "\t\t\t\t************    0--退出通讯录    ************" << endl;
	cout << "\t\t\t\t*********************************************" << endl;
}

//添加联系人函数
void AddPerson(AddressBook* arb)
{
	if (arb->size == MAX)
	{
		cout << "添加联系人失败！！因为通讯录已满！！" << endl;
		return;
	}
	else
	{
		while (1)
		{
			//姓名
			cout << "姓名: ";
			cin >> arb->personArr[arb->size].name;
			//性别
			cout << "性别: ";
			cin >> arb->personArr[arb->size].sex;
			//年龄
			cout << "年龄: ";
			cin >> arb->personArr[arb->size].age;
			//号码
			cout << "号码: ";
			cin >> arb->personArr[arb->size].num;
			//更新通讯录人数
			arb->size++;
			cout << "添加联系人成功!!" << endl; //提示信息'
			cout << "是否还要继续添加？(Y/N)" << endl;
			string ques;
			cin >> ques;
			if (ques == "N" || ques == "n")
			{
				break;
			}
		}
		system("cls"); //清屏操作
	}
}

//显示联系人函数
void ShowPerson(AddressBook* arb)
{
	if (arb->size == 0)
	{
		cout << "当前记录为空!" << endl;
	}
	else
	{
		for (si i = 0; i < arb->size; i++)
		{
			cout << "姓名: " << arb->personArr[i].name << "\t";
			cout << "性别: " << arb->personArr[i].sex << "\t";
			cout << "年龄: " << arb->personArr[i].age << "\t";
			cout<< "电话: " << arb->personArr[i].num << endl;
		}
	}
	EndClean();
}

//判断联系人是否存在函数
si IsExist(AddressBook* arb, string name)
{
	for (si i = 0; i < arb->size; i++)
	{
		if (arb->personArr[i].name == name)
		{
			return i;
		}
	}
	return -1;
}

//删除联系人函数
void DelPerson(AddressBook* arb)
{
	string name;
	cout << "请输入您要删除的联系人: ";
	cin >> name;
	if (arb->size == 0)
	{
		cout << "请先添加联系人！" << endl;
		EndClean();
	}
	else
	{
		si ret = IsExist(arb, name);
		if (ret != -1)
		{
			for (si i = ret; i < arb->size; i++)
			{
				arb->personArr[i] = arb->personArr[i + 1];
				arb->size--;
			}
			cout << "删除成功！" << endl;
			EndClean();
		}
		else
		{
			cout << "查无此人!!" << endl;
			EndClean();
		}
	}
}

//查找联系人函数
void FindPerson(AddressBook* arb)
{
	cout << "请输入您要查找的联系人:" << endl;
	string name;
	cin >> name;
	si ret = IsExist(arb, name);
	if (ret != -1)
	{
		cout << "姓名: " << arb->personArr[ret].name << "\t";
		cout << "性别: " << arb->personArr[ret].sex<< "\t";
		cout << "年龄: " << arb->personArr[ret].age << "\t";
		cout << "电话: " << arb->personArr[ret].num << endl;
	}
	else
	{
		cout << "查无此人！！" << endl;
	}
	EndClean();

}

//修改联系人
void ModifyPerson(AddressBook* arb)
{
	cout << "请输入您要修改的联系人: " << endl;
	string name;
	cin >> name;
	si ret = IsExist(arb, name);
	bool running = true;
	if (ret != -1)
	{
		while (running)
		{
			cout << "姓名: " << arb->personArr[ret].name << "\t";
			cout << "性别: " << arb->personArr[ret].sex << "\t";
			cout << "年龄: " << arb->personArr[ret].age << "\t";
			cout << "电话: " << arb->personArr[ret].num << endl;
			cout << "----------------------------------" << endl;
			cout << "----------  1---姓名  ------------" << endl;
			cout << "----------  2---性别  ------------" << endl;
			cout << "----------  3---年龄  ------------" << endl;
			cout << "----------  4---电话  ------------" << endl;
			cout << "----------  0---返回  ------------" << endl;
			cout << "请输入您要进行修改的操作：";
			string name, sex, age, num;
			si opration;
			cin >> opration;
			switch (opration)
			{
			case 1:
				cout << "姓名: " << endl;
				cin >> name;
				arb->personArr[ret].name = name;
				cout << "修改成功!!" << endl;
				break;
			case 2:
				cout << "性别: " << endl;
				cin >> sex;
				arb->personArr[ret].sex = sex;
				cout << "修改成功!!" << endl;
				break;
			case 3:
				cout << "年龄: " << endl;
				cin >> age;
				arb->personArr[ret].age = age;
				cout << "修改成功!!" << endl;
				break;
			case 4:
				cout << "电话: " << endl;
				cin >> num;
				arb->personArr[ret].num = num;
				cout << "修改成功!!" << endl;
				break;
			case 0:
				running = false;
				break;
			}
		}
		
	}
	else
	{
		cout << "查无此人!!" << endl;
	}
	EndClean();
}

//清空通讯录
void CleanPerson(AddressBook* arb)
{
	string choice1, choice2;
	cout << "是否清空通讯录？(Y/N)" << endl;
	cin >> choice1;
	if (choice1 == "Y" || choice1 == "y")
	{
		cout << "在下方键入“CLEAN”以清空通讯录.(警告：这是不可逆的操作！！这将会删除所有联系人数据!!)" << endl;
		cin >> choice2;
		if (choice2 == "CLEAN")
		{
			arb->size = 0;
			cout << "通讯录已清空!" << endl;
		}
		else
		{
			cout << "清空操作取消!" << endl;
		}
	}
	else
	{
		cout << "清空操作取消!" << endl;
	}
	EndClean();
}

//用户选择处理函数
void Select(si select, AddressBook *P)
{
	switch (select)
	{
	case 1: 
		AddPerson(P);//添加联系人
		break;
	case 2: 
		ShowPerson(P);//显示联系人
		break;
	case 3:
		DelPerson(P);//删除联系人
		break;
	case 4:
		FindPerson(P);//查找联系人
		break;
	case 5:
		ModifyPerson(P);//修改联系人
		break;
	case 6:
		CleanPerson(P);//清空通讯录
		break;
	case 0: //退出通讯录
		cout << "期待您的下次使用！！" << endl;
		running = false;
		break;
	}
}

//文件处理函数
void DocOprate(AddressBook* P)
{
	ofstream ofs;
	ofs.open("AddressBook.txt", ios::out);
	for (si i = 0; i < P->size; i++)
	{
		ofs << "姓名:" << P->personArr[i].name << "\t";
		ofs << "性别:" << P->personArr[i].sex << "\t";
		ofs << "年龄:" << P->personArr[i].age << "\t";
		ofs << "电话:" << P->personArr[i].num << endl;
	}
	ofs.close();
}

int main()
{
	AddressBook arb = {{}}; //创建通讯录
	arb.size = 0; //初始化通讯录人员个数
	AddressBook* P = &arb; //定义该结构体指针
	while (running)
	{
		ShowMenu();//菜单调用
		si select = 0; //创建用户选择变量
		cout << "请输入您的操作：";
		cin >> select;
		Select(select, P);
	}
	DocOprate(P);
	system("pause");
	return 0;
}