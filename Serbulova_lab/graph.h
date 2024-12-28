#pragma once
#include "help.h"
#include "pipe.h"
#include "CS.h"
#include "link.h"


class graph
{
public:
	template <typename T>
	static void cout_matrix(const std::vector<std::vector<T>>& matrix);

	static std::vector<std::vector<int>> create_matrix(const std::set<link>&);
	static std::vector<std::vector<double>> create_double_matrix(const std::set<link>& s, std::unordered_map<int, pipe>& pipemap);

	static bool dfs(int v, std::vector<int>&, std::stack<int>&, const std::vector<std::vector<int>>&);
	static void topological_sort(const std::vector<std::vector<int>>&);

	static bool findAugmentingPath(const std::vector<std::vector<double>>& residualGraph, int source, int sink, std::vector<int>& parent);
	static double max_flow(std::vector<std::vector<double>> graph, int source, int sink);

	static double path_length(const std::vector<std::vector<double>>& adj_matrix, const std::vector<int>& path);
	static std::vector<int> short_path(std::vector<std::vector<double>> adj_matrix, int sourse, int sink);

};