#include<iostream>
#include<string>
#include<fstream>

using namespace std;

constexpr auto MAX = 100;//ͨѶ¼�������;

bool running = true;

typedef short int si;

//������������
void EndClean()
{
	system("pause");
	system("cls");
}

//������ϵ�˽ṹ��
struct Person
{
	string name;
	string sex;
	string age;
	string num;
};

//����ͨѶ¼�ṹ��
struct AddressBook
{
	Person personArr[MAX]; //ͨѶ¼�������
	si size = 0; //ͨѶ¼��ǰ��Ա����
};

//��ʾ�˵�����
void ShowMenu()
{
	cout << endl;
	cout << "\t\t\t\t--------------ͨѶ¼����ϵͳV1.0-------------" << endl;
	cout << "\t\t\t\t*********************************************" << endl;
	cout << "\t\t\t\t************    1--�����ϵ��    ************" << endl;
	cout << "\t\t\t\t************    2--��ʾ��ϵ��    ************" << endl;
	cout << "\t\t\t\t************    3--ɾ����ϵ��    ************" << endl;
	cout << "\t\t\t\t************    4--������ϵ��    ************" << endl;
	cout << "\t\t\t\t************    5--�޸���ϵ��    ************" << endl;
	cout << "\t\t\t\t************    6--���ͨѶ¼    ************" << endl;
	cout << "\t\t\t\t************    0--�˳�ͨѶ¼    ************" << endl;
	cout << "\t\t\t\t*********************************************" << endl;
}

//�����ϵ�˺���
void AddPerson(AddressBook* arb)
{
	if (arb->size == MAX)
	{
		cout << "�����ϵ��ʧ�ܣ�����ΪͨѶ¼��������" << endl;
		return;
	}
	else
	{
		while (1)
		{
			//����
			cout << "����: ";
			cin >> arb->personArr[arb->size].name;
			//�Ա�
			cout << "�Ա�: ";
			cin >> arb->personArr[arb->size].sex;
			//����
			cout << "����: ";
			cin >> arb->personArr[arb->size].age;
			//����
			cout << "����: ";
			cin >> arb->personArr[arb->size].num;
			//����ͨѶ¼����
			arb->size++;
			cout << "�����ϵ�˳ɹ�!!" << endl; //��ʾ��Ϣ'
			cout << "�Ƿ�Ҫ������ӣ�(Y/N)" << endl;
			string ques;
			cin >> ques;
			if (ques == "N" || ques == "n")
			{
				break;
			}
		}
		system("cls"); //��������
	}
}

//��ʾ��ϵ�˺���
void ShowPerson(AddressBook* arb)
{
	if (arb->size == 0)
	{
		cout << "��ǰ��¼Ϊ��!" << endl;
	}
	else
	{
		for (si i = 0; i < arb->size; i++)
		{
			cout << "����: " << arb->personArr[i].name << "\t";
			cout << "�Ա�: " << arb->personArr[i].sex << "\t";
			cout << "����: " << arb->personArr[i].age << "\t";
			cout<< "�绰: " << arb->personArr[i].num << endl;
		}
	}
	EndClean();
}

//�ж���ϵ���Ƿ���ں���
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

//ɾ����ϵ�˺���
void DelPerson(AddressBook* arb)
{
	string name;
	cout << "��������Ҫɾ������ϵ��: ";
	cin >> name;
	if (arb->size == 0)
	{
		cout << "���������ϵ�ˣ�" << endl;
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
			cout << "ɾ���ɹ���" << endl;
			EndClean();
		}
		else
		{
			cout << "���޴���!!" << endl;
			EndClean();
		}
	}
}

//������ϵ�˺���
void FindPerson(AddressBook* arb)
{
	cout << "��������Ҫ���ҵ���ϵ��:" << endl;
	string name;
	cin >> name;
	si ret = IsExist(arb, name);
	if (ret != -1)
	{
		cout << "����: " << arb->personArr[ret].name << "\t";
		cout << "�Ա�: " << arb->personArr[ret].sex<< "\t";
		cout << "����: " << arb->personArr[ret].age << "\t";
		cout << "�绰: " << arb->personArr[ret].num << endl;
	}
	else
	{
		cout << "���޴��ˣ���" << endl;
	}
	EndClean();

}

//�޸���ϵ��
void ModifyPerson(AddressBook* arb)
{
	cout << "��������Ҫ�޸ĵ���ϵ��: " << endl;
	string name;
	cin >> name;
	si ret = IsExist(arb, name);
	bool running = true;
	if (ret != -1)
	{
		while (running)
		{
			cout << "����: " << arb->personArr[ret].name << "\t";
			cout << "�Ա�: " << arb->personArr[ret].sex << "\t";
			cout << "����: " << arb->personArr[ret].age << "\t";
			cout << "�绰: " << arb->personArr[ret].num << endl;
			cout << "----------------------------------" << endl;
			cout << "----------  1---����  ------------" << endl;
			cout << "----------  2---�Ա�  ------------" << endl;
			cout << "----------  3---����  ------------" << endl;
			cout << "----------  4---�绰  ------------" << endl;
			cout << "----------  0---����  ------------" << endl;
			cout << "��������Ҫ�����޸ĵĲ�����";
			string name, sex, age, num;
			si opration;
			cin >> opration;
			switch (opration)
			{
			case 1:
				cout << "����: " << endl;
				cin >> name;
				arb->personArr[ret].name = name;
				cout << "�޸ĳɹ�!!" << endl;
				break;
			case 2:
				cout << "�Ա�: " << endl;
				cin >> sex;
				arb->personArr[ret].sex = sex;
				cout << "�޸ĳɹ�!!" << endl;
				break;
			case 3:
				cout << "����: " << endl;
				cin >> age;
				arb->personArr[ret].age = age;
				cout << "�޸ĳɹ�!!" << endl;
				break;
			case 4:
				cout << "�绰: " << endl;
				cin >> num;
				arb->personArr[ret].num = num;
				cout << "�޸ĳɹ�!!" << endl;
				break;
			case 0:
				running = false;
				break;
			}
		}
		
	}
	else
	{
		cout << "���޴���!!" << endl;
	}
	EndClean();
}

//���ͨѶ¼
void CleanPerson(AddressBook* arb)
{
	string choice1, choice2;
	cout << "�Ƿ����ͨѶ¼��(Y/N)" << endl;
	cin >> choice1;
	if (choice1 == "Y" || choice1 == "y")
	{
		cout << "���·����롰CLEAN�������ͨѶ¼.(���棺���ǲ�����Ĳ��������⽫��ɾ��������ϵ������!!)" << endl;
		cin >> choice2;
		if (choice2 == "CLEAN")
		{
			arb->size = 0;
			cout << "ͨѶ¼�����!" << endl;
		}
		else
		{
			cout << "��ղ���ȡ��!" << endl;
		}
	}
	else
	{
		cout << "��ղ���ȡ��!" << endl;
	}
	EndClean();
}

//�û�ѡ������
void Select(si select, AddressBook *P)
{
	switch (select)
	{
	case 1: 
		AddPerson(P);//�����ϵ��
		break;
	case 2: 
		ShowPerson(P);//��ʾ��ϵ��
		break;
	case 3:
		DelPerson(P);//ɾ����ϵ��
		break;
	case 4:
		FindPerson(P);//������ϵ��
		break;
	case 5:
		ModifyPerson(P);//�޸���ϵ��
		break;
	case 6:
		CleanPerson(P);//���ͨѶ¼
		break;
	case 0: //�˳�ͨѶ¼
		cout << "�ڴ������´�ʹ�ã���" << endl;
		running = false;
		break;
	}
}

//�ļ�������
void DocOprate(AddressBook* P)
{
	ofstream ofs;
	ofs.open("AddressBook.txt", ios::out);
	for (si i = 0; i < P->size; i++)
	{
		ofs << "����:" << P->personArr[i].name << "\t";
		ofs << "�Ա�:" << P->personArr[i].sex << "\t";
		ofs << "����:" << P->personArr[i].age << "\t";
		ofs << "�绰:" << P->personArr[i].num << endl;
	}
	ofs.close();
}

int main()
{
	AddressBook arb = {{}}; //����ͨѶ¼
	arb.size = 0; //��ʼ��ͨѶ¼��Ա����
	AddressBook* P = &arb; //����ýṹ��ָ��
	while (running)
	{
		ShowMenu();//�˵�����
		si select = 0; //�����û�ѡ�����
		cout << "���������Ĳ�����";
		cin >> select;
		Select(select, P);
	}
	DocOprate(P);
	system("pause");
	return 0;
}