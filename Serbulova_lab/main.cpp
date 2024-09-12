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
	cout << "Меню\nВыберите опцию\n"
		"1. Добавить трубу\n2. Добавить КС\n3. Просмотр всех объектов"
		"\n4. Редактировать трубу\n5. Редактировать КС\n"
		"6. Сохранить\n7. Загрузить\n"
		"0. Выход";
}

int main()
{
	setlocale(LC_ALL, "Russian");

	cout << "Привет Hello" << endl;

	while (true)
	{
		int option = MenuOutput;
		if (option == 0)
			cout << "До свидания!";
	}


	return 0;
}