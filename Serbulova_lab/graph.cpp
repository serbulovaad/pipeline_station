#include "graph.h"
using namespace std;

std::vector<std::vector<int>> graph::create_matrix(const std::set<link>& s) {
    int maxID = 0;
    for (const auto& l : s) { //��� ������� ������ ������� ���������
        if (l.csInID > maxID) maxID = l.csInID;
        if (l.csOutID > maxID) maxID = l.csOutID;
    }

    vector<vector<int>> matrix(maxID, vector<int>(maxID, 0)); // ��� ������� ������

    for (const auto& l : s) {
        matrix[l.csInID - 1][l.csOutID - 1] = l.pipeID; // ��� ���
    }

    cout << "Matrix:" << endl;
    cout << "  ";
    for (const auto& l : s) 
        cout << l.csInID << " ";
    cout << endl;
        
    for (const auto& row : matrix) {
        for (int weight : row) {
            cout << weight << ' ';
        }
        cout << '\n';
    }
    cout << endl;

    return matrix;
}


bool graph::dfs(int v, vector<int>& state, stack<int>& stk, const vector<vector<int>>& matrix) {
    state[v] = 1;

    for (int i = 0; i < matrix.size(); ++i) { 
        if (matrix[v][i] != 0) {
            if (state[i] == 1) {
                return false; 
            }
            if (state[i] == 0) {
                if (!dfs(i, state, stk, matrix)) {
                    return false;
                }
            }
        }
    }

    state[v] = 2; 
    stk.push(v); 
    return true;
}

void graph::topological_sort(const vector<vector<int>>& matrix) {
    stack<int> stk;
    vector<int> state(matrix.size(), 0);

    for (int i = 0; i < matrix.size(); ++i) {
        if (state[i] == 0) {
            if (!dfs(i, state, stk, matrix)) {
                cout << "The graph has a cycle -> topological sorting is impossible" << endl;
                return;
            }
        }
    }

    cout << "Topological sorting (ID CSes) : ";
    while (!stk.empty()) {
        cout << stk.top() + 1 << " "; 
        stk.pop();
    }
    cout << endl;
}







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
