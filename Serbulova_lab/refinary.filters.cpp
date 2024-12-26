#include "refinary.h"
#include "help.h"
using namespace std;

template<typename T, typename U>
using Filter = bool(*)(T& val, U param);
template<typename T>
bool checkByName(T val, std::string name);
bool checkByRepairStatus(pipe& p, bool status)
{
	return p.getInRepair() == status;
}
bool checkByWSInWork(CS& cs, double percent)
{
	return cs.getPercentWsInUse() >= percent;
}

double checkByDiam(pipe& p, double diam)
{
	return p.getDiam() == diam;
}

template<typename T, typename U>
std::unordered_set<int> findByFilter(std::unordered_map<int, T>& map, Filter<T, U> f, U param);

unordered_set<int> selectByChosenFilter(unordered_map<int, pipe>& map)
{
	unordered_set<int> res;
	cout << "Choose filter:\n1. Name\n2. Repair status\n0. Exit" << endl << "> ";
	switch (getCorrectNumber(0, 2))
	{
	case 0:
		return res;
	case 1:
	{

		cout << "Enter part of name: "; string name = inputString();
		res = findByFilter(map, checkByName, name);
		break;
	}
	case 2:
	{

		cout << "Enter status \"in repair\"(1 or 0): "; bool status = getCorrectNumber<int>(0, 1);
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
	cout << "Choose filter:\n1. Name\n2. Percent % of ws in use\n0. Exit" << endl << "> ";
	switch (getCorrectNumber(0, 2))
	{
	case 1:
	{

		cout << "Enter part of name: "; string name = inputString();
		res = findByFilter(map, checkByName, name);
		break;
	}
	case 2:
	{

		cout << "Enter percent % (min): "; double percent = getCorrectNumber<double>(0.0, 100.0);
		res = findByFilter(map, checkByWSInWork, percent);
		break;
	}
	case 0:
	{
		return res;
		break;
	}
	default:
		break;
	}
	return res;
}


template<typename T>
std::unordered_set<int> selectByChosenID(std::unordered_map<int, T>& map, std::unordered_set<int>& set)
{
	std::unordered_set<int> res;
	std::cout << "Enter all ID\nTo stop enter 0" << std::endl;
	while (1)
	{
		cout << "> ";
		int id = inputNumber<int>();
		if (id == 0)
			break;
		if (set.size() == 0) // found with ID - first step to choose among all things
		{
			if (map.contains(id))
				res.emplace(id);
		}
		else
			if (map.contains(id) && set.contains(id))
				res.emplace(id); // found with ID - second step to choose among the filtred things
	}

	return res;
}
template unordered_set<int> selectByChosenID(std::unordered_map<int, pipe>& map, std::unordered_set<int>& set);
template unordered_set<int> selectByChosenID(std::unordered_map<int, CS>& map, std::unordered_set<int>& set);



