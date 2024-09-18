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

void inputCheck(int& x) // ввод с проверкой, он нужен?
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

istream& operator >> (istream& in, pipe& p) // как тут сделать проверку?
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

		cout << "Меню\nВыберите опцию\n"
			"1. Добавить трубу\n2. Добавить КС\n3. Просмотр всех объектов"
			"\n4. Редактировать трубу\n5. Редактировать КС\n"
			"6. Сохранить\n7. Загрузить\n"
			"0. Выход\n" << endl;

		int option;
		cout << "Выберите опцию: ";
		inputCheck(option);
		cout << endl;
		
		if (option != 0)
		{
			switch (option)
			{
				case 1:
					cout << "Добавьте трубу" << endl;

					cout << endl;
					break;
				case 2:
					cout << "Добавьте КС" << endl;

					cout << endl;
					break;
				case 3:
					cout << "Просмотр всех объектов" << endl;

					cout << endl;
					break;
				case 4:
					cout << "Редактирование трубы" << endl;

					cout << endl;
					break;
				case 5:
					cout << "Редактирование КС" << endl;

					cout << endl;
					break;
				case 6:
					cout << "Сохранение" << endl;

					cout << endl;
					break;
				case 7:
					cout << "Выход" << endl;

					cout << endl;
					break;
				default:
					cout << "Ошибка, введено неверное число" << option << endl
						<< "Повторите попытку" << endl << endl;
					break;
			}
		} 
		else 
		{
			cout << "До свидания!" << endl;
			return 0;
		}
		
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");

	cout << "Привет Hello" << endl;

	MenuOutput();


	return 0;
}