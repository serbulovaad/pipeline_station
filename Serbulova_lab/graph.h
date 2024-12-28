#pragma once
#include "help.h"
#include "pipe.h"
#include "CS.h"
#include "link.h"

class graph
{
public:
	static std::vector<std::vector<int>> create_matrix(const std::set<link>&);
	static std::vector<std::vector<double>> create_double_matrix(const std::set<link>& s, std::unordered_map<int, pipe>& pipemap);
	static bool dfs(int v, std::vector<int>&, std::stack<int>&, const std::vector<std::vector<int>>&);
	static void topological_sort(const std::vector<std::vector<int>>&);

	static bool bfs(const std::vector<std::vector<double>>& capacity, std::vector<int>& parent, int source, int sink);
	static double max_flow(const std::vector<std::vector<double>>& capacity, int source, int sink);

	static std::vector<double> short_path(const std::vector<std::vector<double>>& graph, int source, int target);

};