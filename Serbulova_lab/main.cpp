#include <iostream>
#include <string>
using namespace std;

//properties
struct pipe
{
	int name;
	int length;
	float diameter;
	bool status_repair; // 0 False - ready for use, 1 True - under repair
};

struct CS //Compressor station
{
	string name;
	int number_ws; // workstations in use
	int efficienty;

};

int MenuOutput()
{
	cout << "����\n�������� �����\n"
		"1. �������� �����\n2. �������� ��\n3. �������� ���� ��������"
		"\n4. ������������� �����\n5. ������������� ��\n"
		"6. ���������\n7. ���������\n"
		"0. �����";
}

int main()
{
	setlocale(LC_ALL, "Russian");

	cout << "������ Hello" << endl;

	while (true)
	{
		int option = MenuOutput;
		if (option == 0)
			cout << "�� ��������!";
	}


	return 0;
}