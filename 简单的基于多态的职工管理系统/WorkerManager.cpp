#include "WorkerManager.hpp"

WorkerManager::WorkerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//如果文件不存在
	if (!ifs.is_open())
	{
		//cout << "当前没有职工信息文件" << endl;
		this->m_CurrentNum = 0;
		this->m_EmpArry = nullptr;
		this->m_isFileEmpty = true;
		ifs.close();
		return;
	}

	//如果文件存在但数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "当前职工信息为空!" << endl;
		this->m_CurrentNum = 0;
		this->m_EmpArry = nullptr;
		this->m_isFileEmpty = true;
		ifs.close();
		return;
	}

	//文件存在并读取数据
	int num = this->GetNum();
	this->m_CurrentNum = num;
	this->m_isFileEmpty = false;
	this->m_EmpArry = new Worker * [num];
	this->LoadEmp();
}

WorkerManager::~WorkerManager()
{
	if (this->m_EmpArry != nullptr)
	{
		for (int i = 0; i < this->m_CurrentNum; i++)
			if (this->m_EmpArry[i] != NULL)
				delete this->m_EmpArry[i];

		delete[] this->m_EmpArry;
		this->m_EmpArry = nullptr;
		this->m_CurrentNum = 0;
	}
}

void WorkerManager::ShowMenu()
{
	cout << "*****************************************" << endl;
	cout << "********  欢迎使用职工管理系统!  ********" << endl;
	cout << "***********  1--退出管理程序  ***********" << endl;
	cout << "***********  2--显示所有职工  ***********" << endl;
	cout << "***********  3--增加员工信息  ***********" << endl;
	cout << "***********  4--删除员工信息  ***********" << endl;
	cout << "***********  5--修改职工信息  ***********" << endl;
	cout << "***********  6--查找职工信息  ***********" << endl;
	cout << "***********  7--按照编号排序  ***********" << endl;
	cout << "***********  8--清空所有信息  ***********" << endl;
	cout << "*****************************************" << endl;
	cout << endl;
}

void WorkerManager::ExitSys()
{
	exit(0);
}

void WorkerManager::ShowAllEmp()
{
	if (this->m_isFileEmpty || this->m_CurrentNum == 0)
	{
		cout << "文件不存在或记录为空!" << endl;
	}
	else
	{
		cout << "当前职工人数为:" << this->m_CurrentNum << "人" << endl;
		for (int i = 0; i < this->m_CurrentNum; i++)
			this->m_EmpArry[i]->ShowInfo();
	}
}

void WorkerManager::AddPerson()
{
	int addNum;
	cout << "请输入添加职工数量: ";
	cin >> addNum;
	
	if (addNum > 0)
	{
		//计算添加新空间的大小
		int newSize = this->m_CurrentNum + addNum;
		//开辟新空间
		Worker** newSpace = new Worker * [newSize];
		//将原来空间下的数据拷贝到新空间下
		if (this->m_EmpArry != nullptr)
		{
			for (int i = 0; i < this->m_CurrentNum; i++)
				newSpace[i] = this->m_EmpArry[i];
		};
		//批量添加新数据
		for (int i = this->m_CurrentNum; i < newSize; i++)
		{
			int id, select;
			string name;

			cout << "正在添加第" << i + 1 << "个员工:" << endl;
			cout << "  编号:";
			cin >> id;

			cout << "  姓名:";
			cin >> name;

POST:		cout << "请选择该员工的岗位:" << endl;
			cout << "1.普通职工\t"<< "2.高层管理\t" << "3.老板大人" << endl;
			cin >> select;

			Worker* worker = nullptr;
			switch (select)
			{
			case 1:
				worker = new Employee(id, name);
				break;
			case 2:
				worker = new Manager(id, name);
				break;
			case 3:
				worker = new Boss(id, name);
				break;
			default:
				cout << "请正确地选择岗位!" << endl;
				goto POST;
			}
			//将创建的职工指针保存到数组中
			newSpace[i] = worker;
		}
		//释放原有的空间
		delete[] this->m_EmpArry;

		//更改新空间的指向
		this->m_EmpArry = newSpace;
		//更新新的职工人数
		this->m_CurrentNum = newSize;

		this->m_isFileEmpty = false;
		cout << "成功添加" << addNum << "名新员工!" << endl;
		this->Save();
		system("pause");
		system("cls");
	}
	else
	{
		cout << "输入有误!" << endl;
		system("pause");
		system("cls");
	}
}

void WorkerManager::DelPerson()
{
	if (this->m_isFileEmpty)
		cout << "文件不存在或记录为空!" << endl;
	
	this->ShowAllEmp();
	int id,index=0;
	cout << "请输入您要删除职工的编号:" << endl;
	cin >> id;
	if (!isExist(id, &index))
	{
		cout << "未找到对应该编号的职工！" << endl;
		return;
	}

	for (int i = index; i < this->m_CurrentNum - 1; i++)
	{
		this->m_EmpArry[i] = this->m_EmpArry[i + 1];
	}
	this->m_CurrentNum--;
	this->Save();
	cout << "删除成功!" << endl;

	system("pause");
	system("cls");
}

void WorkerManager::ModifyPerson()
{
	if (this->m_isFileEmpty)
		cout << "文件不存在或记录为空!" << endl;
	else
	{
		cout << "请输入您要修改的职工的编号:";
		int id,index;
		cin >> id;
		if (!isExist(id, &index))
			cout << "找不到对应此编号的员工!" << endl;
		cout << "请选择您要修改的项目:"<<endl
			<< "1--员工编号\t2--员工姓名\t3--员工岗位" << endl;
		unsigned short choice;
		cin >> choice;
		if (choice == 1)
		{
			cout << "将" << this->m_EmpArry[index]->m_ID << "修改为:";
			int newid;
			cin >> newid;
			this->m_EmpArry[index]->m_ID = newid;
		}
		else if (choice == 2)
		{
			cout << "将" << this->m_EmpArry[index]->m_Name << "修改为:";
			string newName;
			cin >> newName;
			this->m_EmpArry[index]->m_Name = newName;
		}
		else
		{
			cout << "将职位修改为:" << endl;
POST2:		cout << "1.普通职工\t" << "2.高层管理\t" << "3.老板大人" << endl;
			unsigned short select;
			cin >> select;
			switch (select)
			{
			case 1:
				this->m_EmpArry[index]->m_Post = "普通职工";
				break;
			case 2:
				this->m_EmpArry[index]->m_Post = "高层管理";
				break;
			case 3:
				this->m_EmpArry[index]->m_Post = "老板大人";
				break;
			default:
				cout << "请输入正确的选项!" << endl;
				goto POST2;
			}
		}
		cout << "Modify Successfully!" << endl;
		this->Save();
		system("pause");
		system("cls");
	}
}

void WorkerManager::FindPerson()
{
	if (this->m_isFileEmpty)
		cout << "文件不存在或记录为空!" << endl;
	else
	{
FIND:	cout << "请输入您要查找的方式:" << endl
			<< "1--按编号查找" << endl
			<< "2--按姓名查找" << endl;
		unsigned short choice;
		cin >> choice;
		if (choice == 1)
		{
			cout << "请输入您要查找的员工的编号:";
			int index,id;
			cin >> id;
			if (this->isExist(id, &index) == false)
				cout << "找不到此员工!" << endl;
			else
				this->m_EmpArry[index]->ShowInfo();
		}
		else if (choice == 2)
		{
			cout << "请输入您要查找的员工的姓名:";
			int index;
			string name;
			cin >> name;
			if (this->isExist(name, &index) == false)
				cout << "找不到此员工!" << endl;
			else
				this->m_EmpArry[index]->ShowInfo();
		}
		else
		{
			cout << "输入有误!" << endl;
			goto FIND;
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::SortPerson()
{
	if (this->m_isFileEmpty)
	{
		cout << "文件不存在或记录为空!" << endl;
	}
	else
	{
		cout << "请选择排序方式:" << endl << "1--按编号升序排序 2--按编号降序排序" << endl;
		unsigned short select;
		cin >> select;
		for (int i = 0; i < m_CurrentNum; i++)
		{
			int MinOrMax = i;
			for (int j = i + 1; j < this->m_CurrentNum; j++)
			{
				if (select == 1)
				{
					if (this->m_EmpArry[MinOrMax]->m_ID > this->m_EmpArry[j]->m_ID)
						MinOrMax = j;
				}
				else
				{
					if (this->m_EmpArry[MinOrMax]->m_ID < this->m_EmpArry[j]->m_ID)
						MinOrMax = j;
				}
			}
			if (i != MinOrMax)
			{
				Worker* temp = this->m_EmpArry[i];
				this->m_EmpArry[i] = this->m_EmpArry[MinOrMax];
				this->m_EmpArry[MinOrMax] = temp;
			}
		}
		cout << "排序成功!排序后的结果为:" << endl;
		this->ShowAllEmp();
IsSave:	cout << "是否将排序结果保存到本地文件?(Y/N)" << endl;
		char choice;
		cin>>choice;
		if (choice == 'Y')
		{
			this->Save();
			cout << "Save Successfully!" << endl;
			system("pause");
		}
		else if (choice == 'N')
		{
			system("cls");
			return;
		}
		else
		{
			cout << "输入有误!" << endl;
			goto IsSave;
		}
		system("cls");
	}
}

void WorkerManager::ClrList()
{
CLS:cout << "确定是否清空?(Y/N)" << endl;
	char choice;
	cin >> choice;
	if (choice == 'Y' || choice == 'y')
	{
		ofstream ofs(FILENAME, ios::trunc); //此函数代表删除文件后重新新建
		ofs.close();

		if (this->m_EmpArry != nullptr)
		{
			for (int i = 0; i < this->m_CurrentNum; i++)
				if (this->m_EmpArry[i] != NULL)
				{
					delete this->m_EmpArry[i];
					this->m_EmpArry[i] = NULL;
				}

			delete[] this->m_EmpArry;
			this->m_EmpArry = nullptr;
			this->m_CurrentNum = 0;
			this->m_isFileEmpty = true;
		}
		cout << "清空成功!!" << endl;
	}
	else if (choice == 'N' || choice == 'n')
		;
	else
	{
		cout << "输入有误!" << endl;
		goto CLS;
	}
	system("pause");
	system("cls");
}

void WorkerManager::Save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	for (int i = 0; i < this->m_CurrentNum; i++)
	{
		ofs << this->m_EmpArry[i]->m_ID << "\t"
			<< this->m_EmpArry[i]->m_Name << "\t"
			<< this->m_EmpArry[i]->m_Post << endl;
	}

	ofs.close();
}

int WorkerManager::GetNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int ID;
	int num = 0;
	string name, post;
	while (ifs>>ID && ifs>>name && ifs>>post)
	{
		num++;
	}
	return num;
}

void WorkerManager::LoadEmp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int ID;
	int index = 0;
	string name, post;
	while (ifs>>ID && ifs>>name && ifs>>post)
	{
		Worker* worker = nullptr;
		if (post == "普通职工")
		{
			worker = new Employee(ID, name);
		}
		else if (post == "高层管理")
		{
			worker = new Manager(ID, name);
		}
		else
		{
			worker = new Boss(ID, name);
		}
		this->m_EmpArry[index] = worker;
		index++;
	}
}

bool WorkerManager::isExist(int id,int* index)
{
	for (int i = 0; i < this->m_CurrentNum; i++)
	{
		if (this->m_EmpArry[i]->m_ID == id)
		{
			*index = i;
			return true;
		}
	}
	return false;
}

bool WorkerManager::isExist(string name, int* index)
{
	for (int i = 0; i < this->m_CurrentNum; i++)
	{
		if (this->m_EmpArry[i]->m_Name == name)
		{
			*index = i;
			return true;
		}
	}
	return false;
}
