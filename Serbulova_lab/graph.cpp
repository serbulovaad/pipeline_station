#include "graph.h"
#include <queue>
#include <algorithm>
#include <limits>
using namespace std;

std::vector<std::vector<int>> graph::create_matrix(const std::set<link>& s) {
    int maxID = 0;
    for (const auto& l : s) { //тут выбрали размер матрицы смежности
        if (l.csInID > maxID) maxID = l.csInID;
        if (l.csOutID > maxID) maxID = l.csOutID;
    }

    vector<vector<int>> matrix(maxID, vector<int>(maxID, 0)); // тут создали вектор

    for (const auto& l : s) {
        matrix[l.csInID - 1][l.csOutID - 1] = l.pipeID; // тут вес
    }

    cout << "Matrix:" << endl;        
    for (const auto& row : matrix) {
        for (int weight : row) {
            cout << weight << ' ';
        }
        cout << '\n';
    } 
    cout << endl;

    return matrix;
}

std::vector<std::vector<double>> graph::create_double_matrix(const std::set<link>& s, std::unordered_map<int, pipe>& pipemap) 
{
    int maxID = 0;
    for (const auto& l : s) { //тут выбрали размер матрицы смежности
        if (l.csInID > maxID) maxID = l.csInID;
        if (l.csOutID > maxID) maxID = l.csOutID;
    }

    vector<vector<double>> matrix(maxID, vector<double>(maxID, 0)); // тут создали вектор

    for (const auto& l : s) {
        if (pipemap[l.pipeID].getInRepair() == 1)
            matrix[l.csInID - 1][l.csOutID - 1] = 0;
        else
            matrix[l.csInID - 1][l.csOutID - 1] = pipemap[l.pipeID].getCapacity();
    }

    cout << "Matrix:" << endl;
    for (const auto& row : matrix) {
        for (double weight : row) {
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






bool graph::bfs(const vector<vector<double>>& capacity, vector<int>& parent, int source, int sink) {
    int n = capacity.size();
    vector<bool> visited(n, false);
    queue<int> q;

    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < n; ++v) {
            if (!visited[v] && capacity[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
                if (v == sink) {
                    return true;
                }
            }
        }
    }

    return false;
}

double graph::max_flow(const vector<vector<double>>& capacity, int source, int sink) {
    int n = capacity.size();
    vector<vector<double>> residualCapacity = capacity;
    vector<int> parent(n);
    double maxFlow = 0;

    while (bfs(residualCapacity, parent, source, sink)) {
        double pathFlow = numeric_limits<double>::max();
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, residualCapacity[u][v]);
        }

        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            residualCapacity[u][v] -= pathFlow;
            residualCapacity[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}


vector<double> graph::short_path(const vector<vector<double>>& graph, int source, int target) {
    int n = graph.size();
    vector<double> distances(n, numeric_limits<double>::max());
    vector<bool> visited(n, false);
    distances[source] = 0;

    using P = pair<double, int>;
    priority_queue<P, vector<P>, greater<P>> pq;
    pq.push({ 0, source }); 

    while (!pq.empty()) {
        double currentDistance = pq.top().first;
        int currentNode = pq.top().second;
        pq.pop();

        if (visited[currentNode]) {
            continue; 
        }

        visited[currentNode] = true;

        for (int neighbor = 0; neighbor < n; ++neighbor) {
            double edgeWeight = graph[currentNode][neighbor];

            if (edgeWeight > 0 && !visited[neighbor]) { 
                double newDistance = currentDistance + edgeWeight;

                if (newDistance < distances[neighbor]) {
                    distances[neighbor] = newDistance;
                    pq.push({ newDistance, neighbor });
                }
            }
        }
    }

    return distances; 
}