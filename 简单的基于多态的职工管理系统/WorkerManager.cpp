#include "WorkerManager.hpp"

WorkerManager::WorkerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//����ļ�������
	if (!ifs.is_open())
	{
		//cout << "��ǰû��ְ����Ϣ�ļ�" << endl;
		this->m_CurrentNum = 0;
		this->m_EmpArry = nullptr;
		this->m_isFileEmpty = true;
		ifs.close();
		return;
	}

	//����ļ����ڵ�����Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "��ǰְ����ϢΪ��!" << endl;
		this->m_CurrentNum = 0;
		this->m_EmpArry = nullptr;
		this->m_isFileEmpty = true;
		ifs.close();
		return;
	}

	//�ļ����ڲ���ȡ����
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
	cout << "********  ��ӭʹ��ְ������ϵͳ!  ********" << endl;
	cout << "***********  1--�˳��������  ***********" << endl;
	cout << "***********  2--��ʾ����ְ��  ***********" << endl;
	cout << "***********  3--����Ա����Ϣ  ***********" << endl;
	cout << "***********  4--ɾ��Ա����Ϣ  ***********" << endl;
	cout << "***********  5--�޸�ְ����Ϣ  ***********" << endl;
	cout << "***********  6--����ְ����Ϣ  ***********" << endl;
	cout << "***********  7--���ձ������  ***********" << endl;
	cout << "***********  8--���������Ϣ  ***********" << endl;
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
		cout << "�ļ������ڻ��¼Ϊ��!" << endl;
	}
	else
	{
		cout << "��ǰְ������Ϊ:" << this->m_CurrentNum << "��" << endl;
		for (int i = 0; i < this->m_CurrentNum; i++)
			this->m_EmpArry[i]->ShowInfo();
	}
}

void WorkerManager::AddPerson()
{
	int addNum;
	cout << "���������ְ������: ";
	cin >> addNum;
	
	if (addNum > 0)
	{
		//��������¿ռ�Ĵ�С
		int newSize = this->m_CurrentNum + addNum;
		//�����¿ռ�
		Worker** newSpace = new Worker * [newSize];
		//��ԭ���ռ��µ����ݿ������¿ռ���
		if (this->m_EmpArry != nullptr)
		{
			for (int i = 0; i < this->m_CurrentNum; i++)
				newSpace[i] = this->m_EmpArry[i];
		};
		//�������������
		for (int i = this->m_CurrentNum; i < newSize; i++)
		{
			int id, select;
			string name;

			cout << "������ӵ�" << i + 1 << "��Ա��:" << endl;
			cout << "  ���:";
			cin >> id;

			cout << "  ����:";
			cin >> name;

POST:		cout << "��ѡ���Ա���ĸ�λ:" << endl;
			cout << "1.��ְͨ��\t"<< "2.�߲����\t" << "3.�ϰ����" << endl;
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
				cout << "����ȷ��ѡ���λ!" << endl;
				goto POST;
			}
			//��������ְ��ָ�뱣�浽������
			newSpace[i] = worker;
		}
		//�ͷ�ԭ�еĿռ�
		delete[] this->m_EmpArry;

		//�����¿ռ��ָ��
		this->m_EmpArry = newSpace;
		//�����µ�ְ������
		this->m_CurrentNum = newSize;

		this->m_isFileEmpty = false;
		cout << "�ɹ����" << addNum << "����Ա��!" << endl;
		this->Save();
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��������!" << endl;
		system("pause");
		system("cls");
	}
}

void WorkerManager::DelPerson()
{
	if (this->m_isFileEmpty)
		cout << "�ļ������ڻ��¼Ϊ��!" << endl;
	
	this->ShowAllEmp();
	int id,index=0;
	cout << "��������Ҫɾ��ְ���ı��:" << endl;
	cin >> id;
	if (!isExist(id, &index))
	{
		cout << "δ�ҵ���Ӧ�ñ�ŵ�ְ����" << endl;
		return;
	}

	for (int i = index; i < this->m_CurrentNum - 1; i++)
	{
		this->m_EmpArry[i] = this->m_EmpArry[i + 1];
	}
	this->m_CurrentNum--;
	this->Save();
	cout << "ɾ���ɹ�!" << endl;

	system("pause");
	system("cls");
}

void WorkerManager::ModifyPerson()
{
	if (this->m_isFileEmpty)
		cout << "�ļ������ڻ��¼Ϊ��!" << endl;
	else
	{
		cout << "��������Ҫ�޸ĵ�ְ���ı��:";
		int id,index;
		cin >> id;
		if (!isExist(id, &index))
			cout << "�Ҳ�����Ӧ�˱�ŵ�Ա��!" << endl;
		cout << "��ѡ����Ҫ�޸ĵ���Ŀ:"<<endl
			<< "1--Ա�����\t2--Ա������\t3--Ա����λ" << endl;
		unsigned short choice;
		cin >> choice;
		if (choice == 1)
		{
			cout << "��" << this->m_EmpArry[index]->m_ID << "�޸�Ϊ:";
			int newid;
			cin >> newid;
			this->m_EmpArry[index]->m_ID = newid;
		}
		else if (choice == 2)
		{
			cout << "��" << this->m_EmpArry[index]->m_Name << "�޸�Ϊ:";
			string newName;
			cin >> newName;
			this->m_EmpArry[index]->m_Name = newName;
		}
		else
		{
			cout << "��ְλ�޸�Ϊ:" << endl;
POST2:		cout << "1.��ְͨ��\t" << "2.�߲����\t" << "3.�ϰ����" << endl;
			unsigned short select;
			cin >> select;
			switch (select)
			{
			case 1:
				this->m_EmpArry[index]->m_Post = "��ְͨ��";
				break;
			case 2:
				this->m_EmpArry[index]->m_Post = "�߲����";
				break;
			case 3:
				this->m_EmpArry[index]->m_Post = "�ϰ����";
				break;
			default:
				cout << "��������ȷ��ѡ��!" << endl;
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
		cout << "�ļ������ڻ��¼Ϊ��!" << endl;
	else
	{
FIND:	cout << "��������Ҫ���ҵķ�ʽ:" << endl
			<< "1--����Ų���" << endl
			<< "2--����������" << endl;
		unsigned short choice;
		cin >> choice;
		if (choice == 1)
		{
			cout << "��������Ҫ���ҵ�Ա���ı��:";
			int index,id;
			cin >> id;
			if (this->isExist(id, &index) == false)
				cout << "�Ҳ�����Ա��!" << endl;
			else
				this->m_EmpArry[index]->ShowInfo();
		}
		else if (choice == 2)
		{
			cout << "��������Ҫ���ҵ�Ա��������:";
			int index;
			string name;
			cin >> name;
			if (this->isExist(name, &index) == false)
				cout << "�Ҳ�����Ա��!" << endl;
			else
				this->m_EmpArry[index]->ShowInfo();
		}
		else
		{
			cout << "��������!" << endl;
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
		cout << "�ļ������ڻ��¼Ϊ��!" << endl;
	}
	else
	{
		cout << "��ѡ������ʽ:" << endl << "1--������������� 2--����Ž�������" << endl;
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
		cout << "����ɹ�!�����Ľ��Ϊ:" << endl;
		this->ShowAllEmp();
IsSave:	cout << "�Ƿ����������浽�����ļ�?(Y/N)" << endl;
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
			cout << "��������!" << endl;
			goto IsSave;
		}
		system("cls");
	}
}

void WorkerManager::ClrList()
{
CLS:cout << "ȷ���Ƿ����?(Y/N)" << endl;
	char choice;
	cin >> choice;
	if (choice == 'Y' || choice == 'y')
	{
		ofstream ofs(FILENAME, ios::trunc); //�˺�������ɾ���ļ��������½�
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
		cout << "��ճɹ�!!" << endl;
	}
	else if (choice == 'N' || choice == 'n')
		;
	else
	{
		cout << "��������!" << endl;
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
		if (post == "��ְͨ��")
		{
			worker = new Employee(ID, name);
		}
		else if (post == "�߲����")
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
