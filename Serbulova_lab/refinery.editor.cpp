#include "refinary.h"
#include "help.h"
using namespace std;

void coutFoundWithId(unordered_set<int>& set)
{
	cout << "Found objects:" << endl;
	for (int id : set)
		cout << "ID = " << id << endl;

}

template<typename T>
void Editor(std::unordered_map<int, T>& map);

void refinary::pipeEditor()
{
	Editor(pipemap);
}
void refinary::CSEditor()
{
	Editor(csmap);
}

unordered_set<int> selectByChosenFilter(unordered_map<int, pipe>& map);
unordered_set<int> selectByChosenFilter(unordered_map<int, CS>& map);
template<typename T>
unordered_set<int> selectByChosenID(unordered_map<int, T>& map, unordered_set<int>& set);

template<typename T>
void Editor(std::unordered_map<int, T>& map)
{
	unordered_set<int> res;
	if (map.empty())
	{
		coutNoObjectFound();
		return;
	}
	cout << "You want to select by ID or by Filter?\n1. ID\n2. Filter\n0. Exit" << endl << "> ";
	switch (getCorrectNumber(0, 2))
	{
	case 0:
		return;
	case 1:
	{

		res = selectByChosenID(map, res);
		break;
	}
	case 2:
	{

		res = selectByChosenFilter(map);
		break;
	}
	default:
		break;
	}

	if (res.size() == 0)
	{
		coutNoObjectFound();
	}
	else
	{
		coutFoundWithId(res);
		cout << "You want to select ALL or by ID?\n1. ALL\n2. ID\n0. Exit" << endl << "> ";
		switch (getCorrectNumber(0, 2))
		{
		case 0:
			return;
		case 1:
			break;
		case 2:
		{
			res = selectByChosenID(map, res);
			break;
		}
		default:
			break;
		}

		if (res.size() != 0)
		{
			coutFoundWithId(res);
			editSelected(map, res);
		}
		else
		{
			//Editor(map);
			coutNoObjectFound();
		}
	}
}

void editMap(unordered_map<int, pipe>& map)
{
	cout << "Do you want all repair statuses to be..\n1. Inverted\n2. Set as TRUE or 1\n3.Set as FALSE or 0\n0.Exit" << endl << "> ";
	int mark = 2;
	switch (getCorrectNumber(0, 3))
	{
	case 0:
		return;
	case 1:
	{
		mark = 2;
		break;
	}
	case 2:
	{
		mark = 1;
		break;
	}
	case 3:
	{
		mark = 0;
		break;
	}
	default:
		break;
	}
	for (auto& [id, p] : map)
		p.editPipe(mark);
	std::cout << "All selected objects were edited" << endl;
}

void editMap(unordered_map<int, CS>& map)
{
	if (!map.empty()) 
		cout << "Do you want to do for all CSes?\n1. Run one ws\n2. Stop one ws\n0. Exit" << endl << "> ";
	else 
		coutNoObjectFound();
	switch (getCorrectNumber(1, 2))
	{
	case 0:
		return;
	case 1:
	{
		for (auto& [id, cs] : map)
			if (!cs.runWS())
				cout << "Cannot change CS with ID = " << id << endl;
		break;
	}
	case 2:
	{
		for (auto& [id, cs] : map)
			if (!cs.stopWS())
				cout << "Cannot change CS with ID = " << id << endl;

		break;
	}
	default:
		break;
	}
	std::cout << "All possible selected objects were edited" << endl;
}

template<typename T>
void editSelected(std::unordered_map<int, T>& map, std::unordered_set<int>& set)
{
	std::cout << "Choose what to do with selected objects:\n1. Print\n2. Edit\n3. Delete\n0. Exit" << std::endl << "> ";
	switch (getCorrectNumber<int>(0, 3))
	{
	case 0:
		return;
	case 1:
	{
		std::cout << "Your objects:" << endl;
		std::cout << "-----" << endl;
		for (int id : set)
			std::cout << map[id] << "-----" << endl;
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
		std::cout << "All selected objects were deleted" << endl;
		return;
	}
	default:
		break;
	}
	editSelected(map, set);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}
template void editSelected(std::unordered_map<int, pipe>& map, std::unordered_set<int>& set);
template void editSelected(std::unordered_map<int, CS>& map, std::unordered_set<int>& set);
