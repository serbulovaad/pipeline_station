#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "help.h"
#include "pipe.h"
#include "CS.h"
#include "link.h"


class refinary
{
private:
	std::unordered_map<int, pipe> pipemap;
	std::unordered_map<int, CS> csmap;
	//std::set<link> linkset;
	std::unordered_map<int, std::vector<link>> linkset;

public:
	refinary();

	void startPipe();
	void startCS();
	void viewAll();

	void saveSet(std::ofstream& fout, const std::unordered_map<int, std::vector<link>>& set);

	template <typename T>
	void printMap(const std::unordered_map<int, T>& map); // тут не понимаю как норм сделать а не через эту _опу
	template<typename T>
	void saveMap(std::ofstream& fout, const std::unordered_map<int, T>& map);

	template<typename T>
	void loadMap(std::ifstream& fin, std::unordered_map<int, T>& map);

	void loadSet(std::ifstream& fin, std::unordered_map<int, std::vector<link>>& set);

	void saveFile();
	void loadFile();
	void deleteAll();

	void printConnection();
	template <typename T>
	int input_ID_if_found(T map, std::string s);
	void connectCS();

	void disconnectCS();

	void create_matrix(std::vector<std::vector<int>>& adjMatrix, int& size);
	bool topological_sort(const std::vector<std::vector<int>>& adjMatrix, std::vector<int>& sortedOrder);
	void start_sort();

	double findMaxFlow(int currentCSID, int endCSID, const std::unordered_map<int, std::vector<link>>& linkset, std::unordered_map<int, bool>& visited);
	void printPath(int endCSID, const std::unordered_map<int, int>& predecessor);
	void start_pathlen();

	void dijkstra(int startCSID, int endCSID, const std::unordered_map<int, std::vector<link>>& linkset);
	void start_short();


	//editor
	friend void coutFoundWithId(std::unordered_set<int>& set);

	void delete_it(std::unordered_map<int, pipe>& map, std::unordered_set<int>& set);
	void delete_it(std::unordered_map<int, CS>& map, std::unordered_set<int>& set);

	void pipeEditor();
	void CSEditor();
	template<typename T>
	void Editor(std::unordered_map<int, T>& map);

	friend std::unordered_set<int> selectByChosenFilter(std::unordered_map<int, pipe>& map);
	friend std::unordered_set<int> selectByChosenFilter(std::unordered_map<int, CS>& map);

	template<typename T>
	void editSelected(std::unordered_map<int, T>& map, std::unordered_set<int>& set);

	friend void editMap(std::unordered_map<int, pipe>& map);
	friend void editMap(std::unordered_map<int, CS>& map);

	//filters
	
	template<typename T, typename U>
	using Filter = bool(*)(T& val, U param);
	template<typename T>
	friend bool checkByName(T val, std::string name)
	{
		size_t pos = val.getName().find(name);
		if (pos != std::string::npos) return true;
		else return false;
	}
	friend bool checkByRepairStatus(pipe& p, bool status);
	friend double checkByDiam(pipe& p, double diam);
	friend bool checkByWSInWork(CS& cs, double percent);

	template<typename T, typename U>
	friend std::unordered_set<int> findByFilter(std::unordered_map<int, T>& map, Filter<T, U> f, U param)
	{
		std::unordered_set<int> res;
		int i = 0;
		for (auto& [id, val] : map)
		{
			if (f(val, param))
				res.emplace(id);
		}
		return res;
	}

	template<typename T>
	friend std::unordered_set<int> selectByChosenID(std::unordered_map<int, T>& map, std::unordered_set<int>& set);
	friend std:: unordered_set<int> selectByChosenFilter(std::unordered_map<int, pipe>& map);
	friend std::unordered_set<int> selectByChosenFilter(std::unordered_map<int, CS>& map);
};






