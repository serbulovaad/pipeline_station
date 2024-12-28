#pragma once
#include "help.h"
#include "pipe.h"
#include "CS.h"
#include "link.h"

class graph
{
private:
	std::set<link> receivedset;

public:
	void setSet(std::set<link> newset)
	{
		receivedset = newset;
	}

	void create_matrix(std::vector<std::vector<int>>& adjMatrix, int& size);

	bool topological_sort(const std::vector<std::vector<int>>& adjMatrix, std::vector<int>& sortedOrder);
	void start_sort();

	double findMaxFlow(int currentCSID, int endCSID, const std::unordered_map<int, std::vector<link>>& linkset, std::unordered_map<int, bool>& visited);
	void printPath(int endCSID, const std::unordered_map<int, int>& predecessor);
	void start_pathlen();

	void dijkstra(int startCSID, int endCSID);
	void start_short();
};