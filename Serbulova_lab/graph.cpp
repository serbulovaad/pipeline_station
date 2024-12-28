#include "graph.h"
#include <queue>
#include <algorithm>
#include <limits>
using namespace std;

template <typename T>
void graph::cout_matrix(const vector<vector<T>>& matrix)
{
    cout << endl;
    cout << "Matrix:" << endl;
    for (const auto& row : matrix) {
        for (T weight : row) {
            cout << weight << ' ';
        }
        cout << '\n';
    }
    cout << endl;
}
template void graph::cout_matrix(const vector<vector<int>>& matrix);
template void graph::cout_matrix(const vector<vector<double>>& matrix);

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

    cout_matrix(matrix);

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

    cout_matrix(matrix);

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



bool graph::findAugmentingPath(const std::vector<std::vector<double>>& residualGraph, int source, int sink, std::vector<int>& parent) {
    int n = residualGraph.size();
    parent.assign(n, -1); // Сбрасываем родительский массив
    std::queue<double> queue;
    queue.push(source);

    while (!queue.empty()) {
        double current = queue.front();
        queue.pop();

        for (int next = 0; next < n; ++next) {
            // Если есть пропускная способность и вершина не посещена
            if (residualGraph[current][next] > 0 && parent[next] == -1 && next != source) {
                parent[next] = current; // Сохраняем текущую вершину как родительскую
                if (next == sink) return true; // Если дошли до стока
                queue.push(next); // Продолжаем исследование
            }
        }
    }
    return false; // Пути нет
}

// Реализация алгоритма Эдмондса-Карпа
double graph::max_flow(std::vector<std::vector<double>> graph, int source, int sink) {
    int n = graph.size();
    std::vector<std::vector<double>> residualGraph(graph); // Создаем остаточную сеть
    std::vector<int> parent(n); // Для хранения пути
    double maxFlow = 0;

    // Повторяем поиск увеличивающих путей
    while (findAugmentingPath(residualGraph, source, sink, parent)) {
        // Вычисляем минимальную пропускную способность на найденном пути
        double flow = numeric_limits<double>::max();;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            flow = std::min(flow, residualGraph[u][v]);
        }

        // Обновляем остаточную сеть
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            residualGraph[u][v] -= flow;
            residualGraph[v][u] += flow;
        }

        // Увеличиваем общий поток
        maxFlow += flow;
    }

    return maxFlow;
}



double graph::path_length(const vector<vector<double>>& adj_matrix, const vector<int>& path) {
    double length = 0.0;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        length += adj_matrix[path[i]][path[i + 1]];
    }
    return length;
}

vector<int> graph::short_path(vector<vector<double>> adj_weight, int StartNode, int EndNode) {
    vector<int> dist(adj_weight.size(), INT_MAX);
    vector<int> prev(adj_weight.size(), -1);
    vector<bool> visited(adj_weight.size(), false);

    //StartNode = GetIndex(StartNode);
    //EndNode = GetIndex(EndNode);

    dist[StartNode] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({ 0, StartNode });

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (u == EndNode) { break; }

        visited[u] = true;

        for (int v = 0; v < adj_weight.size(); ++v) {
            if (!visited[v] && adj_weight[u][v] && dist[u] != INT_MAX &&
                dist[u] + adj_weight[u][v] < dist[v])
            {
                dist[v] = dist[u] + adj_weight[u][v];
                prev[v] = u;
                pq.push({ dist[v], v });
            }
        }
    }

    vector<int> path;
    int current_node = EndNode;
    while (current_node != StartNode) {
        /*path.push_back(nodes.at(current_node));*/
        path.push_back(current_node);
        if (prev[current_node] != -1) {
            current_node = prev[current_node];
        }
        else {
            return vector<int>();
        }
    }
    //path.push_back(nodes.at(StartNode));
    path.push_back(StartNode);
    reverse(path.begin(), path.end());
    return path;
}

