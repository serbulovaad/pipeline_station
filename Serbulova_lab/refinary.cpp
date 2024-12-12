#include "refinary.h"
using namespace std;

refinary::refinary()
{

};

void refinary::startPipe()
{
	pipe p = pipe::addPipe();
	pipemap.emplace(p.getID(), p);
}

void refinary::startCS()
{
	CS cs = CS::addCS();
	csmap.emplace(cs.getID(), cs);
}

void refinary::viewAll()
{
	cout << "Pipes" << endl;
	if (pipemap.empty()) 
		coutNoObjectFound();
	else
	{
		printMap(pipemap);
		cout << "-----" << endl;
	}
	cout << endl;


	cout << "CSs" << endl;
	if (csmap.empty()) 
		coutNoObjectFound();
	else
	{
		printMap(csmap);
		cout << "-----" << endl;
	}
}

template <typename T>
void refinary::printMap(const unordered_map<int, T>& map)
{
	for (auto& [id, val] : map)
	{
		cout << "-----" << endl;
		cout << val;
	}
}
template void refinary::printMap(const unordered_map<int, pipe>& map);
template void refinary::printMap(const unordered_map<int, CS>& map);

template<typename T>
void refinary::saveMap(std::ofstream& fout, const std::unordered_map<int, T>& map)
{
	fout << map.size() << endl;
	for (auto& [id, val] : map)
	{
		fout << val;
	}
}
template void refinary::saveMap(std::ofstream& fout, const std::unordered_map<int, pipe>& map);
template void refinary::saveMap(std::ofstream& fout, const std::unordered_map<int, CS>& map);

template<typename T>
void refinary::loadMap(std::ifstream& fin, std::unordered_map<int, T>& map)
{
	map.clear();
	T::resetMaxID();
	int sizemap;
	fin >> sizemap;
	for (int i = 1; i <= sizemap; i++)
	{
		T val; fin >> val;
		map.emplace(val.getID(), val);
	}
}
template void refinary::loadMap(std::ifstream& fin, std::unordered_map<int, pipe>& map);
template void refinary::loadMap(std::ifstream& fin, std::unordered_map<int, CS>& map);

void refinary::saveFile() // как правильно сохранять? --> либо флагами - любой порядок, либо отображ числа труб и кс - строгий порядок
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

void refinary::loadFile()
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

void refinary::deleteAll()
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
		pipe::resetMaxID();
		CS::resetMaxID();

		cout << "All objects are deleted" << endl;
	}
	return;
}
