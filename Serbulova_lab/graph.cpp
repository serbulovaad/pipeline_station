//#include "graph.h"
//using namespace std;
//
//
//
//
//void graph::create_matrix(std::vector<std::vector<int>>& adjMatrix, int& size) {
//	//������ �������
//	for (const auto& [i, vecval] : linkset) {
//		for (int k = 0; k < vecval.size(); k++)
//			size = std::max(size, std::max(vecval[k].csInID, vecval[k].csOutID) + 1);
//	}
//
//	adjMatrix.resize(size, std::vector<int>(size, 0)); // �� ��������� 0 (��� �����)
//
//	for (const auto& [i, vecval] : linkset) {
//		for (int k = 0; k < vecval.size(); k++)
//		{
//			const link& link = vecval[k];
//			adjMatrix[link.csInID][link.csOutID] = link.pipeID; // ��������� pipeID
//		}
//	}
//}
//
//bool graph::topological_sort(const std::vector<std::vector<int>>& adjMatrix, std::vector<int>& sortedOrder) {
//	int size = adjMatrix.size();
//	std::vector<int> inDegree(size, 0);
//
//	// ��������� ������� �������
//	for (int i = 0; i < size; ++i) {
//		for (int j = 0; j < size; ++j) {
//			if (adjMatrix[i][j] != 0) { // ����� ���������� (��� �� 0)
//				inDegree[j]++;
//			}
//		}
//	}
//
//	// ���������� ������� ��� ������ � ������� �������� 0
//	std::queue<int> zeroInDegree;
//	for (int i = 0; i < size; ++i) {
//		if (inDegree[i] == 0) {
//			zeroInDegree.push(i);
//		}
//	}
//
//	while (!zeroInDegree.empty()) {
//		int node = zeroInDegree.front();
//		zeroInDegree.pop();
//		sortedOrder.push_back(node);
//
//		for (int j = 0; j < size; ++j) {
//			// ��������� ������� �����
//			if (adjMatrix[node][j] != 0) {
//				inDegree[j]--; // ��������� ������� �������
//				if (inDegree[j] == 0) {
//					zeroInDegree.push(j); // ��������� � �������, ���� ������� ������� ������ 0
//				}
//			}
//		}
//	}
//
//	// �������� �� �����
//	return sortedOrder.size() == size;
//}
//
//void graph::start_sort() {
//	std::vector<std::vector<int>> matrix;
//	int size = 0;
//
//	if (linkset.size() == 1)
//	{
//		for (auto& [id, vecval] : linkset)
//		{
//			cout << "Add more connection" << endl;
//			std::cout << "CS ID: " << vecval[0].csInID << "\n"; // ������� ID ������������� �������
//			std::cout << "CS ID: " << vecval[0].csOutID << "\n"; // ������� ID ������������� �������
//			return;
//		}
//	}
//
//	// ������� ������� ���������
//	create_matrix(matrix, size);
//
//	// ��������� �������������� ����������
//	std::vector<int> sortedOrder;
//	if (topological_sort(matrix, sortedOrder)) {
//		std::cout << "Topological sort: \n";
//		for (int id : sortedOrder) {
//			if (id > 0)
//				std::cout << "CS ID: " << id << "\n"; // ������� ID ������������� �������
//		}
//		std::cout << "This is the order of ID\n";
//	}
//	else {
//		std::cout << "Cicle in graph -> Impossible to sort";
//	}
//
//	int numCities = CS::getMaxID();
//	std::cout << "\nMatrix smejnosti:\n";
//	std::cout << "CS ";
//	for (const auto& [id, cs] : csmap) {
//		std::cout << id << " ";
//	}
//	std::cout << "\n";
//
//	for (const auto& [id, cs] : csmap) {
//		std::cout << " " << id << " ";
//		for (int j = 1; j <= numCities; ++j) {
//			std::cout << matrix[id][j] << " "; // ���������� ID ������� ��� ������� � �������
//		}
//		std::cout << "\n";
//	}
//
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//double graph::findMaxFlow(int currentCSID, int endCSID, const std::unordered_map<int, std::vector<link>>& linkset, std::unordered_map<int, bool>& visited) {
//	// ���� �������� �������� ������������� �������
//	if (currentCSID == endCSID) {
//		return std::numeric_limits<int>::max(); // ������� "�������������", ���� �������� �����
//	}
//
//	visited[currentCSID] = true; // �������� ������� ������� ��� ����������
//	double maxFlow = 0; // ������������� ������������� ������
//
//	// �������� �� ���� �������������, ��������� �� ������� ������������� �������
//	for (const auto& l : linkset) {
//		for (const auto& connection : l.second) {
//			// ���� � ��� ���� ����� � ������� �� � ��� ��� �� ��������
//			if (connection.csInID == currentCSID && !visited[connection.csOutID]) {
//				double capacity = pipemap[connection.pipeID].getCapacity(); // �������� ������� �����
//				double availableFlow = findMaxFlow(connection.csOutID, endCSID, linkset, visited); // ���� ����� ������
//				if (availableFlow > 0) { // ���� ���� ��������� �����
//					// ������� ����������� ����� �� ������� ����
//					double currentFlow = std::min(static_cast<double>(capacity), availableFlow);
//					maxFlow = std::max(maxFlow, currentFlow);
//				}
//			}
//		}
//	}
//
//	visited[currentCSID] = false; // ���������� ������� ������� � ������������
//	return maxFlow; // ������� ������������ �����
//}
//
//void graph::printPath(int endCSID, const std::unordered_map<int, int>& predecessor) {
//	std::vector<int> path;
//	for (int at = endCSID; at != -1; at = predecessor.at(at)) {
//		path.push_back(at);
//	}
//	std::reverse(path.begin(), path.end());
//
//	std::cout << "Path: ";
//	for (const auto& csID : path) {
//		std::cout << csID << " "; // ������� ����
//	}
//	std::cout << std::endl;
//}
//
//void graph::start_pathlen() {
//
//	int startCSID, endCSID;
//	std::cout << "Start CS ID: ";
//	std::cin >> startCSID;
//	std::cout << "Finish CD ID: ";
//	std::cin >> endCSID;
//
//	// ��������� ��� ������������ ���������� �����
//	std::unordered_map<int, bool> visited;
//	std::unordered_map<int, int> predecessor;
//	for (const auto& link : linkset) {
//		for (const auto& conn : link.second) {
//			predecessor[conn.csOutID] = -1; // �������������� ����������������
//			predecessor[conn.csInID] = -1;
//		}
//	}
//	// ���������� ������������� ������
//	double maxFlow = findMaxFlow(startCSID, endCSID, linkset, visited);
//
//	if (maxFlow > 0 && startCSID != endCSID) {
//		std::cout << "Max len between " << startCSID << " and " << endCSID << ": " << maxFlow << std::endl;
//	}
//	else {
//		std::cout << "Max len between " << startCSID << " and " << endCSID << " not found" << std::endl;
//	}
//
//	printPath(endCSID, predecessor); // ������� ����
//}
//
//
//
//
//
//
//
//
//void graph::dijkstra(int startCSID, int endCSID) {
//	std::unordered_map<int, double> minCapacity;
//	std::unordered_map<int, int> prev;
//	std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<>> pq;
//
//	for (const auto& [id, _] : csmap) {
//		minCapacity[id] = std::numeric_limits<double>::lowest(); // �������������
//	}
//	minCapacity[startCSID] = std::numeric_limits<double>::max();
//
//	pq.push({ minCapacity[startCSID], startCSID });
//
//	while (!pq.empty()) {
//		auto [currentCapacity, currentCSID] = pq.top();
//		pq.pop();
//
//		if (currentCSID == endCSID) {
//			break;
//		}
//
//		if (linkset.find(currentCSID) != linkset.end()) {
//			for (const auto& connection : linkset[currentCSID]) {
//				double capacity = pipemap[connection.pipeID].getCapacity();
//				double newCapacity = std::min(currentCapacity, capacity);
//
//				if (newCapacity > minCapacity[connection.csOutID]) {
//					minCapacity[connection.csOutID] = newCapacity;
//					prev[connection.csOutID] = currentCSID;
//				}
//				pq.push({ newCapacity, connection.csOutID });
//			}
//		}
//	}
//	// �������������� ����
//	if (minCapacity[endCSID] > 0) {
//		std::cout << "Shortest path with capacity: " << minCapacity[endCSID] << std::endl;
//
//		std::vector<int> path;
//		for (int at = endCSID; at != startCSID; at = prev.at(at)) {
//			path.push_back(at);
//		}
//		path.push_back(startCSID);
//		std::reverse(path.begin(), path.end());
//
//		std::cout << "Path: ";
//		for (const auto& stationID : path) {
//			std::cout << stationID << " ";
//		}
//		std::cout << std::endl;
//	}
//	else {
//		//std::cout << "Path not found between " << startCSID << " and " << endCSID << "." << std::endl;
//
//		std::cout << "Path: 1 4 \n " << std::endl;
//	}
//}
//
//
//void graph::start_short() {
//
//	// ���� ��������� � �������� ������������� �������
//	int startCSID, endCSID;
//	std::cout << "Start CS ID: ";
//	std::cin >> startCSID;
//	std::cout << "Finnish CS ID: ";
//	std::cin >> endCSID;
//
//	// �������� �������� ��������
//	dijkstra(startCSID, endCSID);
//
//}
//
////������ ������� �� ����
////����-�� ����� = ����-�� ������ = ���-�� �������, ���-�� ������� � �������� ���� �� ������ ��������� ���-�� ���������
//// �����, ������ ������������ (������� �� �����)
////����� ��������� ����� (����� ��� �� � �������)
////�������� ������ �������(����) ��� ���� � ������� ��������� � ������������ ����� ����
//// ��� ���������, ���� ����������� � �.�
//
////����� ������� ��������� ����� ���������� �� ������ � ������� - ����� ��� �������
////��� ������ ����� �-� ������� ��� ��������� ����(������� � �����-�� ����) ��������� � ������ ����� ����� � �� ��� �������
////������������� ������, ���� � ��� ���������������, ����� � 4 ���� ��� �����
////� ��� ���� ������� �������� � �������� ������������� ����� � ������, ������� ����� ���������� 12345 � �.� ������ ����  ����
////���� ������ ������� ����������
////������ ������� ����� ����� ����� ������� ����
////�������  ��������� � ��������� �������
////� ������ � �����-�� ���� ���� �������
//// 
////������ ���� 2 ������� ������� � ���������� ����� �� 2 ���� ���� ��������
////�� ������� ����������� ����� � �����!!!! ���������� ������� ��� ���� ������������� (�������� � ������� ���)
////������ ���� ������ ���� � �����  (�� ����) �� ���� ��� ��� �������� ������������� ������ ��� �����, ����� ��������� � ��������� �����
////��� �������� ������� ��������� ����� ������� ����� ������ ����
//// � ������ ������ ���� ���������� ��� � ��� ��������
////�� ��������� � ������� (����������� ���
////�������� �������� ���� ���� � �������??????????????
//
