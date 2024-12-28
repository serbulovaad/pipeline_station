#pragma once
#include "help.h"
#include "pipe.h"
#include "CS.h"
#include "link.h"

class graph
{
public:
	static std::vector<std::vector<int>> create_matrix(const std::set<link>&);

	static bool dfs(int v, std::vector<int>&, std::stack<int>&, const std::vector<std::vector<int>>&);
	static void topological_sort(const std::vector<std::vector<int>>&);


};