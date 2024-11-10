#pragma once
#include "help.h"
#include "pipe.h"
#include "CS.h"
#include "main.h"
using namespace std;
using namespace chrono;

template <typename T>
bool isMapEmpty(const unordered_map<int, T>& map)
{
	if (map.size() == 0) return true;
	else return false;
}

void coutNoObjectFound() { cout << "No objects found :(" << endl; }

template <typename T>
void printMap(const unordered_map<int, T>& map)
{
	for (auto& [id, val] : map)
		cout << val;
}

template<typename T>
void saveMap(std::ofstream& fout, const std::unordered_map<int, T>& map)
{
	fout << map.size() << endl;
	for (auto& [id, val] : map)
	{
		fout << id;
		fout << val;
	}
}

template<typename T>
void loadMap(std::ifstream& fin, std::unordered_map<int, T>& map)
{
	map.clear();
	int sizemap;
	fin >> sizemap;
	for (int i = 1; i <= sizemap; i++)
	{
		fin >> id;
		map[id] = val;
	}
}

void saveFile(const unordered_map<int, pipe>& pipemap, const unordered_map<int, CS>& csmap) // как правильно сохранять? --> либо флагами - любой порядок, либо отображ числа труб и кс - строгий порядок
{
	cout << "Enter file name: ";
	string filename = inputString();
	ofstream fout;
	fout.open(filename + ".txt", ios::out);
	if (fout)
	{
		saveMap(fout, pipemap);
		saveMap(fout, csmap);
		fout.close();
		cout << "Pipe saved = " << pipemap.size() << endl
			<< "CS saved = " << csmap.size() << endl;
	}
	else cout << "ERROR save" << endl;
}

void loadFile(unordered_map<int, pipe>& pipemap, unordered_map<int, CS>& csmap)
{
	cout << "Enter file name: ";
	string filename = inputString();
	ifstream fin;
	fin.open(filename + ".txt", ios::in);
	if (fin)
	{ // лучше clear и заново вводить или создать новые map и потом их присвоить старым? -> clear чтобы не путать ID
		loadMap(fin, pipemap);
		loadMap(fin, csmap);
		fin.close();
		cout << "Pipe loaded = " << pipemap.size() << endl
			<< "CS loaded = " << csmap.size() << endl;
	}
	else
		cout << "ERROR load" << endl;
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
			pipe p = pipe::addPipe();
			pipemap.emplace(p.getID(), p);
			break;
		}
		case 2:
		{
			CS cs = CS::addCS();
			csmap.emplace(cs.getID(), cs);
			break;
		}
		case 3:
		{
			cout << "View all objects" << endl;
			printMap(pipemap);
			printMap(csmap);
			if (isMapEmpty(pipemap) and isMapEmpty(csmap)) coutNoObjectFound();
			break;
		}
		case 4:
		{
			for (auto& [id, p] : pipemap)
				p.editPipe();
			if (!isMapEmpty(pipemap)) cout << "Repair status of all pipes were edited (inverted)!" << endl;
			else coutNoObjectFound();
			break;
		}
		case 5:
		{
			for (auto& [id, cs] : csmap)
				cs.editCS();
			if (!isMapEmpty(csmap)) cout << "Edited number of ws in work (+1) for all cs'es!" << endl;
			else coutNoObjectFound();
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
		//cout << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Привет Hello" << endl;

	//логирование в отдельный файл
	redirect_output_wrapper cerr_out(cerr);
	string time = std::format("{:%d_%m_%Y %H_%M_%OS}", system_clock::now());
	ofstream logfile("log_" + time + ".txt");
	if (logfile)
		cerr_out.redirect(logfile);

	MenuOutput();

	return 0;
}