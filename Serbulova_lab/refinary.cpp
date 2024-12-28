#include "refinary.h"
#include "link.h"
using namespace std;

//функции с linkset которые приходится исправлять искать по SETTRBL

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

void refinary::printPipes()
{
	if (pipemap.empty())
	{
		coutNoObjectFound("pipes");
		return;
	}

	cout << "Pipes = " << pipemap.size() << endl;
	printMap(pipemap);
	cout << "-----" << endl;
}

void refinary::printCSs()
{
	cout << "CSs = " << csmap.size() << endl;
	if (csmap.empty())
		coutNoObjectFound("CSs");
	else
	{
		printMap(csmap);
		cout << "-----" << endl;
	}
}

void refinary::printConnection() 
{
	if (pipemap.empty())
	{
		coutNoObjectFound("connections");
		return;
	}
	cout << "All your connections:" << endl;
	cout << "From CS >==( pipe )==> to CS" << endl;
	for (auto& val : linkset)
		cout << val.csInID << " >==(" << val.pipeID << ")==> " << val.csOutID << endl;
}

void refinary::viewAll()
{
	printPipes();
	cout << endl;
	printCSs();
}

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

void refinary::saveSet(std::ofstream& fout, const  std::set<link>& set) //SETTRBL
{
	fout << set.size() << endl;
	for (auto& val : linkset)
	{
		fout << val.csInID << endl;
		fout << val.csOutID << endl;
		fout << val.pipeID << endl;
	}
}

void refinary::loadSet(std::ifstream& fin, std::set<link>& set) //SETTRBL
{
	set.clear();
	int sizeset;
	fin >> sizeset;
	for (int i = 1; i <= sizeset; i++)
	{
		link val;
		fin >> val.csInID;
		fin >> val.csOutID;
		fin >> val.pipeID;
		set.emplace(val);
	}
}

void refinary::saveFile() // как правильно сохранять? --> либо флагами - любой порядок, либо отображ числа труб и кс - строгий порядок
{
	cout << "Enter file name (e.g. \"name\"): ";
	string filename = inputString();
	ofstream fout;
	fout.open(filename, ios::out);
	if (fout)
	{
		saveMap(fout, pipemap);
		saveMap(fout, csmap);
		saveSet(fout, linkset);
		fout.close();
		cout << "Pipe saved = " << pipemap.size() << endl
			<< "CS saved = " << csmap.size() << endl
			<< "Connections saved = " << linkset.size() << endl;
	}
	else cout << "ERROR save" << endl;
}

void refinary::loadFile()
{
	cout << "Enter file name (e.g. \"name\"): ";
	string filename = inputString();
	ifstream fin;
	fin.open(filename, ios::in);
	if (fin)
	{ // лучше clear и заново вводить или создать новые map и потом их присвоить старым? -> clear чтобы не путать ID
		loadMap(fin, pipemap);
		loadMap(fin, csmap);
		loadSet(fin, linkset);
		fin.close();
		cout << "Pipe loaded = " << pipemap.size() << endl
			<< "CS loaded = " << csmap.size() << endl
			<< "Connections loaded = " << linkset.size() << endl;
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
		linkset.clear();
		pipe::resetMaxID();
		CS::resetMaxID();

		cout << "All objects are deleted" << endl;
	}
	return;
}

template <typename T>
int refinary::input_ID_if_found(std::unordered_map<int, T> map, string s)
{
	while (1)
	{
		cout << s;
		int id = inputNumber<int>();
		if (map.contains(id))
			return id;
		else
			cout << "ERROR: Element with this ID is not existing -> try again";
	}
	return 0;
}
template int refinary::input_ID_if_found(std::unordered_map<int, pipe> map, string s);
template int refinary::input_ID_if_found(std::unordered_map<int, CS> map, string s);


double checkByDiam(pipe& p, double diam);

void refinary::connectCS() //SETTRBL
{
	if (csmap.size() < 2)
	{
		cout << "Impossible to create connection -> Add more CSs";
		return;
	}
	link l;
	cout << "Creating connection" << endl;
	l.csInID = input_ID_if_found(csmap, "From CS with ID = ");
	l.csOutID = input_ID_if_found(csmap, "To CS with ID = ");
	cout << "With pipe with diam = ";
	int diam = inputNumber<int>();
	l.pipeID = 0;
	for (auto& [id, val] : pipemap)
	{
		if (checkByDiam(val, diam))
		{
			if (pipemap[id].getInRepair())
			{
				cout << pipemap[id].getInRepair()<< endl;
				cout << "Found pipe with ID = " << id << endl;
				l.pipeID = id;
				break;
			} 
			else
			{
				cout << "Pipe with diam = " << diam << " ID = " << id << " are in repair" << endl;
			}
		}
	}
	if (l.pipeID == 0)
	{
		cout << "Not found working pipe with this diam"<<endl;
		if (confirm("Create new one?"))
		{
			cout << "name (str) = ";
			string nam = inputString();
			cout << "l (double) = ";
			double len = getPositiveNumber<double>();
			pipe p(nam, len, diam);
			cout << "Your new pipe:\n";
			cout << p;
			pipemap.emplace(p.getID(), p);
			l.pipeID = p.getID();
		}
		else return;
	}
	linkset.emplace(l);
	cout << endl;

}

bool refinary::try_disconnect_pipe_with_id(int id) //SETTRBL
{
	set<link> helpo;
	for (auto& val : linkset)
		if (val.pipeID == id)
			helpo.emplace(val);

	for (auto& val : helpo)
		linkset.erase(val);

	std::cout << "Pipe with ID = " << id << " disconnected" << endl;
	return !(helpo.empty());
}

bool refinary::try_disconnect_cs_with_id(int id) //SETTRBL
{
	set<link> helpo_in;
	for (auto& val : linkset)
		if (val.csInID == id)
			helpo_in.emplace(val);

	for (auto& val : helpo_in)
		linkset.erase(val);

	set<link> helpo_out;
	for (auto& val : linkset)
		if (val.csOutID == id)
			helpo_out.emplace(val);

	for (auto& val : helpo_out)
		linkset.erase(val);

	std::cout << "CS with ID = " << id << " disconnected" << endl;

	return !(helpo_in.empty() and helpo_out.empty());
}

void refinary::disconnectCS() //SETTRBL
{
	if (linkset.empty())
	{
		cout << "No connections found -> Add more CSs";
		return;
	}
	printConnection();

	cout << "Disconnect...\n1. Pipe\n2. CS" << endl;
	switch (getCorrectNumber(1, 2))
	{
	case 1:
	{
		cout << "Pipe ID = ";
		int id = inputNumber<int>();

		if (try_disconnect_pipe_with_id(id))
			cout << "Pipes was disconnected from system";
		else
			cout << "No connections were found";
		break;
	}
	case 2:
	{
		cout << "CS ID = ";
		int id = inputNumber<int>();

		if (try_disconnect_cs_with_id(id))
			cout << "CS was disconnected from system";
		else
			cout << "No connections were found";
		break;
	}
	default:
		break;
	}
	cout << endl;
}