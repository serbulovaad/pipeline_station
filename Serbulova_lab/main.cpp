#include <iostream>
#include <string>
using namespace std;



//properties
struct pipe
{
	int name;
	int l; // length;
	float d; // diameter;
	bool repair; // 0 False - ready for use, 1 True - under repair
};

struct CS //Compressor station
{
	string name;
	int ws; // workstations in use
	string eff; //efficienty;

};

void inputCheck(int& x) // ���� � ���������, �� �����?
{
	while (1)
	{
		if (cin)
		{
			cin >> x;
			break;
		}
		else
		{
			cin.clear();
			cin.ignore(1000, '\n');
		}
	}
}
ostream& operator << (ostream& out, const pipe& p)
{
	out << "name: " << p.name << endl
		<< "d = " << p.d << endl
		<< "l = " << p.l << endl
		<< "repair = " << p.repair << endl;

	return out;
}

istream& operator >> (istream& in, pipe& p) // ��� ��� ������� ��������?
{
	cout << "name: ";
	in >> p.name;
	cout << "d = ";
	in >> p.d;
	cout << "l = ";
	in >> p.l;
	cout << "repair = ";
	in >> p.repair;

	return in;
}

int MenuOutput()
{
	while (1)
	{

		cout << "����\n�������� �����\n"
			"1. �������� �����\n2. �������� ��\n3. �������� ���� ��������"
			"\n4. ������������� �����\n5. ������������� ��\n"
			"6. ���������\n7. ���������\n"
			"0. �����\n" << endl;

		int option;
		cout << "�������� �����: ";
		inputCheck(option);
		cout << endl;
		
		if (option != 0)
		{
			switch (option)
			{
				case 1:
					cout << "�������� �����" << endl;

					cout << endl;
					break;
				case 2:
					cout << "�������� ��" << endl;

					cout << endl;
					break;
				case 3:
					cout << "�������� ���� ��������" << endl;

					cout << endl;
					break;
				case 4:
					cout << "�������������� �����" << endl;

					cout << endl;
					break;
				case 5:
					cout << "�������������� ��" << endl;

					cout << endl;
					break;
				case 6:
					cout << "����������" << endl;

					cout << endl;
					break;
				case 7:
					cout << "�����" << endl;

					cout << endl;
					break;
				default:
					cout << "������, ������� �������� �����" << option << endl
						<< "��������� �������" << endl << endl;
					break;
			}
		} 
		else 
		{
			cout << "�� ��������!" << endl;
			return 0;
		}
		
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");

	cout << "������ Hello" << endl;

	MenuOutput();


	return 0;
}