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
CHOICE:	cout << "����������ѡ��:";
		cin >> usChoice;
		switch (usChoice)
		{
		case 1:	//�˳�
			wm.ExitSys();
		case 2: //��ʾ������
			wm.ShowAllEmp();
			system("pause");
			goto CHOICE;
		case 3: //����;
			wm.AddPerson();
			break;
		case 4:	//ɾ��
			wm.DelPerson();
			break;
		case 5:	//�޸�
			wm.ModifyPerson();
			break;
		case 6: //����
			wm.FindPerson();
			break;
		case 7: //����
			wm.SortPerson();
			break;
		case 8: //���
			wm.ClrList();
			break;
		default:
			cout << "��������!" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	
	system("pasue");
	return 0;
}