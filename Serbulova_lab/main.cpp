#pragma once
#include "help.h"
#include "pipe.h"
#include "CS.h"
using namespace std;

template <typename T>
void printMap(const unordered_map<int, T>& map)
{
	//for (const auto& val : map)
	for (auto& [id, val] : map)
		cout << val << endl;
}

template <typename T>
T selectObject(const unordered_map<int, T>& map)
{
	int id = inputNumber();
	if (iter != map.end())
		cout << map[id] << endl;
	else cout << "No object with id = " << id << endl;

}

void saveFile(const unordered_map<int, pipe>& pipemap, const unordered_map<int, CS>& csmap) // как правильно сохран€ть? --> либо флагами - любой пор€док, либо отображ числа труб и кс - строгий пор€док
{
	ofstream fout;
	fout.open("data.txt", ios::out);
	if (fout)
	{//???????????????????????
		for (auto& map : (pipemap, csmap) )
			fout << map.size();
			for (auto& [id, val] : pipemap)
				fout << val;
		fout.close();
		cout << "Pipe saved = " << pipemap.size() << endl
			<< "CS saved = " << csmap.size() << endl;
	}
	else cerr << "ERROR save" << endl;
}

void loadFile(unordered_map<int, pipe>& pipemap, unordered_map<int, CS>& csmap)
{
	ifstream fin;
	fin.open("data.txt", ios::in);
	if (fin)
	{ // лучше clear и заново вводить или создать новые map и потом их присвоить старым?
		for (auto& map : { pipemap, csmap })
			map.clear;
			int sizemap;
			fin >> sizemap;
			for (int i = 1; i <= sizemap; i++)
				fin >> map[i];
		fin.close();
		cout << "Pipe loaded = " << pipemap.size() << endl
			<< "CS loaded = " << csmap.size() << endl;
	}
	else
		cerr << "ERROR load" << endl;
}

int MenuOutput()
{
	unordered_map<int, pipe> pipemap;
	unordered_map<int, CS> csmap;

	while (1)
	{
		cout << "Menu\n"
			"1. Add pipe\n2. Add CS\n3. View all objects"
			"\n4. Edit pipe (repair status) \n5. Edit CS (numder of ws in repair)\n"
			"6. Save\n7. Download\n"
			"0. Exit\n";
		cout << "Choose option 0-7 (int): ";

		switch (getCorrectNumber(0, 7))
		{
		case 0:
		{
			cout << "Goodbye" << endl;
			return 0;
		}
		case 1:
		{
			pipe p;
			pipemap.emplace(p.getID(), p.addPipe());
			break;
		}
		case 2:
		{
			CS cs;
			csmap.emplace(cs.getID(), cs.addCS());
			break;
		}
		case 3:
		{
			cout << "View all objects" << endl;
			for (auto& map : { pipemap, csmap })
				printMap(map)
			break;
		}
		case 4:
		{
			//p.editPipe(p);
			break;
		}
		case 5:
		{
			//cs.editCS(cs);
			break;
		}
		case 6:
		{
			saveFile(pipemap, csmap);
			break;
		}
		case 7:
		{
			loadFile(pipemap, csmap);
			break;
		}
		default:
		{
			cerr << "ERROR unexpected" << endl << "Prigrammer forgot to use getCorrectNumber function :)" << endl;
			return 0;
		}
		}
		//cout << endl << "Press Enter to continue";
		//cin.get(); cin.get();
		cout << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "ѕривет Hello" << endl;
	
	unordered_map<int, int> map;
	map = { {1, 12}, {2,23}, {3,36} };

	//std::system("2<log.txt");

	//MenuOutput();

	return 0;
}