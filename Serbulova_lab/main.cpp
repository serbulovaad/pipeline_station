#pragma once
#include "help.h"
#include "pipe.h"
#include "CS.h"
#include "main.h"
using namespace std;
using namespace chrono;

template <typename T>
void printMap(const unordered_map<int, T>& map)
{
	for (auto& [id, val] : map)
	{
		cout << id;
		cout << val;
	}
}

template<typename T>
void saveMap(std::ofstream& fout, const std::unordered_map<int, T>& map)
{
	fout << map.size() << endl;
	for (auto& [id, val] : map)
	{
		fout << val;
	}
}

template<typename T>
void loadMap(std::ifstream& fin, std::unordered_map<int, T>& map)
{
	map.clear();
	T::resetMaxID();
	int sizemap;
	fin >> sizemap;
	for (int i = 1; i <= sizemap; i++)
	{
		T val; fin >> val;			
		map.emplace(val.getID(),val);
	}
}

void saveFile(const unordered_map<int, pipe>& pipemap, const unordered_map<int, CS>& csmap) // как правильно сохранять? --> либо флагами - любой порядок, либо отображ числа труб и кс - строгий порядок
{
	cout << "Enter file name: ";
	string filename = inputString();
	ofstream fout;
	fout.open(filename, ios::out);
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
	fin.open(filename, ios::in);
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

void coutNoObjectFound() { cout << "No objects found :(" << endl; }

template<typename T, typename U>
using Filter = bool(*)(T& val, U param);
template<typename T>
bool checkByName(T& val, string name)
{
	size_t pos = val.getName().find(name);
	if (pos != std::string::npos) return true;
	else return false;
}
bool checkByRepairStatus(pipe& p, bool status)
{
	return p.getInRepair() == status;
}
bool checkByWSInWork(CS& cs, double percent)
{
	return cs.getPercentWsInUse() >= percent;
}

template<typename T, typename U>
unordered_set<int> findByFilter(unordered_map<int, T>& map, Filter<T, U> f, U param)
{
	unordered_set<int> res;
	int i = 0;
	for (auto& [id, val]: map)
	{
		if (f(val, param))
			res.emplace(id);
	}
	return res;
}

unordered_set<int> selectByChosenFilter(unordered_map<int, pipe>& map)
{
	unordered_set<int> res;
	cout << "Choose filter:\n1. Name\n2. Repair status" << endl;
	switch (getCorrectNumber(1, 2))
	{
	case 1:
	{
		cout << "Enter part of name: "; string name = inputString();
		res = findByFilter(map, checkByName, name);
		break;
	}
	case 2:
	{
		cout << "Enter status \"in repair\": "; bool status = getCorrectNumber<int>(0, 1);
		res = findByFilter(map, checkByRepairStatus, status);
		break;
	}
	default:
		break;
	}
	return res;
}

unordered_set<int> selectByChosenFilter(unordered_map<int, CS>& map)
{
	unordered_set<int> res;
	cout << "Choose filter:\n1. Name\n2. Percent % of ws in use" << endl;
	switch (getCorrectNumber(1, 2))
	{
	case 1:
	{
		cout << "Enter part of name: "; string name = inputString();
		res = findByFilter(map, checkByName, name);
		break;
	}
	case 2:
	{
		cout << "Enter percent %: "; double percent = getCorrectNumber<double>(0.0, 100.0);
		res = findByFilter(map, checkByWSInWork, percent);
		break;
	}
	default:
		break;
	}
	return res;
}

template<typename T>
unordered_set<int> selectByChosenID(unordered_map<int, T>& map, unordered_set<int>& set = {})
{
	unordered_set<int> res;
	cout << "Enter all ID\nTo stop enter 0" << endl;
	while(1)
	{
		int id = inputNumber<int>();
		if (id == 0)
			break;
		if (set.size() == 0)
		{	if (map.contains(id)) res.emplace(id);	}
		else
			if (map.contains(id) and set.contains(id)) res.emplace(id);
	}
	return res;
}
void coutFoundWithId(unordered_set<int>& set)
{
	cout << "Found objects with id: ";
	for (int id : set)
		cout << id << " ";
	cout << endl;
}

void editMap(unordered_map<int, pipe>& map)
{
	for (auto& [id, p] : map)
		p.editPipe();
	if (!map.empty()) cout << "Repair status of all pipes were edited (inverted)!" << endl;
	else coutNoObjectFound();
}

void editMap(unordered_map<int, CS>& map)
{
	if (!map.empty()) cout << "Do you want to run or stop 1 ws for all CS?\n1. Run\n2. Stop" << endl;
	else coutNoObjectFound();
	switch (getCorrectNumber(1, 2))
	{
	case 1:
	{
		for (auto& [id, cs] : map)
			if (!cs.runWS())
				cout << "Cannot change CS " << id << endl;
		break;
	}
	case 2:
	{
		for (auto& [id, cs] : map)
			if (!cs.stopWS())
				cout << "Cannot change CS " << id << endl;

		break;
	}
	default:
		break;
	}

	if (!map.empty()) cout << "Well done!" << endl;
	else coutNoObjectFound();
}

template<typename T>
void editSelected(unordered_map<int, T>& map, unordered_set<int>& set)
{
	cout << "Choose what to do with selected objects:\n1. Print\n2. Edit\n3. Delete\0. Exit" << endl;
	switch (getCorrectNumber<int>(1,3))
	{
	case 1:
	{
		for (int id : set)
			cout << map[id];
		break;
	}
	case 2:
	{
		editMap(map);
		break;
	}
	case 3:
	{
		for (int id : set)
			map.erase(id);
		break;
	}
	case 0:
	{
		if (confirm("All your filters will be gone. Are you sure?"))
			break;
	}
	default:
		break;
	}
}

template<typename T>
void selectObjects(unordered_map<int, T>& map)
{
	unordered_set<int> res;
	if (map.empty())
	{
		coutNoObjectFound();
		return;
	}
	cout << "You want to select by ID or by Filter?\n1. ID\n2. Filter" << endl ;
	if (getCorrectNumber(1, 2) == 1) //ID
		res = selectByChosenID(map, res);
	else // Filter
		res = selectByChosenFilter(map);
	if (res.size() != 0)
	{
		coutFoundWithId(res);
		cout << "You want to select ALL or by ID?\n1. ALL\n2. ID" << endl;
		if (getCorrectNumber(1, 2) == 2) //ID
			res = selectByChosenID(map, res);
		if (res.size() != 0)
			editSelected(map, res);
		else coutNoObjectFound();
	}
	else coutNoObjectFound();
}

void deleteAll(unordered_map<int, pipe>& pipemap, unordered_map<int, CS>& csmap)
{
	if (pipemap.empty() && csmap.empty())
	{
		coutNoObjectFound();
		return;
	}
	if (confirm("Are you sure?"))
	{
		pipemap.clear();
		csmap.clear();
		cout << "All objects are deleted" << endl;
	}
	return;
}

int MenuOutput()
{
	unordered_map<int, pipe> pipemap;
	unordered_map<int, CS> csmap;

	while (1)
	{
		cout << "Menu\n"
			"1. Add pipe\n2. Add CS\n3. View all objects\n" 
			"4. Edit pipes\n5. Edit CSs\n"
			"6. Save\n7. Download\n8. Delete All\n"
			"0. Exit\n";
		cout << "Choose option: ";

		switch (getCorrectNumber(0, 8))
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
			if (pipemap.empty() and csmap.empty()) coutNoObjectFound();
			else
			{
			cout << "Pipes" << endl; printMap(pipemap);
			cout << "CSs" << endl; printMap(csmap);
			}
			break;
		}
		case 4:
		{
			selectObjects(pipemap);
			break;
		}
		case 5:
		{
			selectObjects(csmap);
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
		case 8:
		{
			deleteAll(pipemap, csmap);
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