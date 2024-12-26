#include "refinary.h"
#include <vector>
#include <queue>
#include <set>
using namespace std;

refinary::refinary()
{

};

void refinary::startPipe()
{
	pipe p = pipe::addPipe();
	pipemap.emplace(p.getID(), p);
}

void refinary::startCS()
{
	CS cs = CS::addCS();
	csmap.emplace(cs.getID(), cs);
}

void refinary::viewAll()
{
	cout << "Pipes = " << pipemap.size() << endl;
	if (pipemap.empty()) 
		coutNoObjectFound();
	else
	{
		printMap(pipemap);
		cout << "-----" << endl;
	}
	cout << endl;


	cout << "CSs = " << csmap.size() << endl;
	if (csmap.empty()) 
		coutNoObjectFound();
	else
	{
		printMap(csmap);
		cout << "-----" << endl;
	}
}

template <typename T>
void refinary::printMap(const unordered_map<int, T>& map)
{
	for (auto& [id, val] : map)
	{
		cout << "-----" << endl;
		cout << val;
	}
}
template void refinary::printMap(const unordered_map<int, pipe>& map);
template void refinary::printMap(const unordered_map<int, CS>& map);

template<typename T>
void refinary::saveMap(std::ofstream& fout, const std::unordered_map<int, T>& map)
{
	fout << map.size() << endl;
	for (auto& [id, val] : map)
	{
		fout << val;
	}
}
template void refinary::saveMap(std::ofstream& fout, const std::unordered_map<int, pipe>& map);
template void refinary::saveMap(std::ofstream& fout, const std::unordered_map<int, CS>& map);

void refinary::saveSet(std::ofstream& fout, const  std::unordered_map<int, std::vector<link>>& set)
{
	fout << set.size() << endl;
	for (auto& [i, vecval] : linkset)
		for (int k = 0; k < vecval.size(); k++)
		{
			fout << vecval[k].csInID << endl;
			fout << vecval[k].csOutID << endl;
			fout << vecval[k].pipeID << endl;
		}
}


template<typename T>
void refinary::loadMap(std::ifstream& fin, std::unordered_map<int, T>& map)
{
	map.clear();
	T::resetMaxID();
	int sizemap;
	fin >> sizemap;
	for (int i = 1; i <= sizemap; i++)
	{
		T val; fin >> val;
		map.emplace(val.getID(), val);
	}
}
template void refinary::loadMap(std::ifstream& fin, std::unordered_map<int, pipe>& map);
template void refinary::loadMap(std::ifstream& fin, std::unordered_map<int, CS>& map);


void refinary::loadSet(std::ifstream& fin, std::unordered_map<int, std::vector<link>>& set)
{
	set.clear();
	int sizeset;
	fin >> sizeset;
	for (int i = 1; i <= sizeset; i++)
	{
		link val;
		fin >> val.csInID;
		fin >> val.csOutID;
		fin >> val.pipeID;
		set[val.pipeID].push_back(val);
	}
}

void refinary::saveFile() // как правильно сохранять? --> либо флагами - любой порядок, либо отображ числа труб и кс - строгий порядок
{
	cout << "Enter file name: ";
	string filename = inputString();
	ofstream fout;
	fout.open(filename, ios::out);
	if (fout)
	{
		saveMap(fout, pipemap);
		saveMap(fout, csmap);
		saveSet(fout, linkset);
		fout.close();
		cout << "Pipe saved = " << pipemap.size() << endl
			<< "CS saved = " << csmap.size() << endl;
	}
	else cout << "ERROR save" << endl;
}

void refinary::loadFile()
{
	cout << "Enter file name: ";
	string filename = inputString();
	ifstream fin;
	fin.open(filename, ios::in);
	if (fin)
	{ // лучше clear и заново вводить или создать новые map и потом их присвоить старым? -> clear чтобы не путать ID
		loadMap(fin, pipemap);
		loadMap(fin, csmap);
		loadSet(fin, linkset);
		fin.close();
		cout << "Pipe loaded = " << pipemap.size() << endl
			<< "CS loaded = " << csmap.size() << endl;
	}
	else
		cout << "ERROR load" << endl;
}

void refinary::deleteAll()
{
	if (pipemap.empty() && csmap.empty())
	{
		coutNoObjectFound();
		return;
	}
	if (confirm("Are you sure?"))
	{
		pipemap.clear();
		csmap.clear();
		linkset.clear();
		pipe::resetMaxID();
		CS::resetMaxID();

		cout << "All objects are deleted" << endl;
	}
	return;
}

void refinary::printConnection()
{
	cout << "All your connections:" << endl;
	cout << "From CS >==( pipe )==> to CS" << endl;
	for (auto& [i, vecval] : linkset)
		for (int k = 0; k < vecval.size(); k++)
			cout << vecval[k].csInID << " >==(" << vecval[k].pipeID << ")==> " << vecval[k].csOutID << endl;
}

template <typename T>
int refinary::input_ID_if_found(T map, string s)
{
	while (1)
	{
		cout << s;
		int id = inputNumber<int>();
		if (csmap.contains(id))
			return id;
		else
			cout << "ERROR: Element with this ID is not existing -> try again";
	}
	return 0;
}
template int refinary::input_ID_if_found(pipe map, string s);
template int refinary::input_ID_if_found(CS map, string s);


double checkByDiam(pipe& p, double diam);

void refinary::connectCS()
{
	if (csmap.size() < 2)
	{
		cout << "Impossible to create connection -> Add more CSs";
		return;
	}
	link l;
	cout << "Creating connection" << endl;
	l.csInID = input_ID_if_found(csmap, "From CS with ID = ");
	l.csOutID = input_ID_if_found(csmap, "To CS with ID = ");
	cout << "With pipe with diam = ";
	int diam = inputNumber<int>();
	l.pipeID = 0;
	for (auto& [id, val] : pipemap)
	{
		if (checkByDiam(val, diam))
		{
			if (pipemap[id].getInRepair())
			{
				cout << pipemap[id].getInRepair()<< endl;
				cout << "Found pipe with ID = " << id << endl;
				l.pipeID = id;
				break;
			} 
			else
			{
				cout << "Pipe with diam = " << diam << " ID = " << id << " are in repair" << endl;
			}
		}
	}
	if (l.pipeID == 0)
	{
		cout << "Not found pipe with this diam"<<endl;
		if (confirm("Create new one?"))
		{
			cout << "name (str) = ";
			string nam = inputString();
			cout << "l (double) = ";
			double len = getPositiveNumber<double>();
			pipe p(nam, len, diam);
			cout << "Your new pipe:\n";
			cout << p;
			pipemap.emplace(p.getID(), p);
			l.pipeID = p.getID();
		}
		else return;
	}

	linkset[l.pipeID].push_back(l);
}

void refinary::disconnectCS()
{
	if (linkset.empty())
	{
		cout << "No connections found -> Add more CSs";
		return;
	}
	printConnection();

	cout << "1. Pipe       2. CS" << endl;
	switch (getCorrectNumber(1, 2))
	{
	case 1:
	{
		cout << "Pipe ID = ";
		int id = inputNumber<int>();
		bool fl = false;
		if (linkset.contains(id))
		{
			fl = true;
			linkset.erase(id);
		}
		if (fl == false)
			cout << "No connections was found";
		else
			cout << "Pipe was disconnected from system";
		break;
	}
	case 2:
	{
		cout << "CS ID = ";
		int id = inputNumber<int>();
		set<int> helpo;
		for (auto& [i, vecval] : linkset)
			for (int k = 0; k < vecval.size(); k++)
				if (vecval[k].csInID == id or vecval[k].csOutID == id)
					helpo.emplace(i);

		for (auto& k : helpo)
			linkset.erase(k);

		if (helpo.size() == 0)
			cout << "No connections was found";
		else
			cout << "CS was disconnected from system";
		break;
	}
	default:
		break;
	}
	
}










void refinary::create_matrix(std::vector<std::vector<int>>& adjMatrix, int& size) {
	//размер матрицы
	for (const auto& [i, vecval] : linkset) {
		for (int k = 0; k < vecval.size(); k++)
			size = std::max(size, std::max(vecval[k].csInID, vecval[k].csOutID) + 1);
	}

	adjMatrix.resize(size, std::vector<int>(size, 0)); // по умолчанию 0 (нет связи)

	for (const auto& [i, vecval] : linkset) {
		for (int k = 0; k < vecval.size(); k++)
		{
		const link& link = vecval[k];
		adjMatrix[link.csInID][link.csOutID] = link.pipeID; // заполняем pipeID
		}
	}
}

bool refinary::topological_sort(const std::vector<std::vector<int>>& adjMatrix, std::vector<int>& sortedOrder) {
	int size = adjMatrix.size();
	std::vector<int> inDegree(size, 0);

	// Вычисляем входные степени
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (adjMatrix[i][j] != 0) { // Связь существует (вес не 0)
				inDegree[j]++;
			}
		}
	}

	// Используем очередь для вершин с входной степенью 0
	std::queue<int> zeroInDegree;
	for (int i = 0; i < size; ++i) {
		if (inDegree[i] == 0) {
			zeroInDegree.push(i);
		}
	}

	while (!zeroInDegree.empty()) {
		int node = zeroInDegree.front();
		zeroInDegree.pop();
		sortedOrder.push_back(node);

		for (int j = 0; j < size; ++j) {
			// Проверяем наличие связи
			if (adjMatrix[node][j] != 0) {
				inDegree[j]--; // Уменьшаем входную степень
				if (inDegree[j] == 0) {
					zeroInDegree.push(j); // Добавляем в очередь, если входная степень теперь 0
				}
			}
		}
	}

	// Проверка на циклы
	return sortedOrder.size() == size;
}

void refinary::start_sort() {
	std::vector<std::vector<int>> matrix;
	int size = 0;

	if (linkset.size() == 1)
	{
		for (auto& [id, vecval] : linkset)
		{
		cout << "Add more connection" << endl;
		std::cout << "CS ID: " << vecval[0].csInID << "\n"; // Выводим ID компрессорной станции
		std::cout << "CS ID: " << vecval[0].csOutID << "\n"; // Выводим ID компрессорной станции
		return;
		}
	}

	// Создаем матрицу смежности
	create_matrix(matrix, size);

	// Выполняем топологическую сортировку
	std::vector<int> sortedOrder;
	if (topological_sort(matrix, sortedOrder)) {
		std::cout << "Topological sort: \n";
		for (int id : sortedOrder) {
			if (id > 0) 
				std::cout << "CS ID: " << id << "\n"; // Выводим ID компрессорной станции
		}
		std::cout << "This is the order of ID\n";
	}
	else {
		std::cout << "Cicle in graph -> Impossible to sort";
	}

	int numCities = CS::getMaxID();
	std::cout << "\nMatrix smejnosti:\n";
	std::cout << "CS ";
	for (const auto& [id, cs] : csmap) {
		std::cout << id << " ";
	}
	std::cout << "\n";

	for (const auto& [id, cs] : csmap) {
		std::cout << " " << id << " ";
		for (int j = 1; j <= numCities; ++j) {
			std::cout << matrix[id][j] << " "; // Используем ID станций для доступа к матрице
		}
		std::cout << "\n";
	}

}



















double refinary::findMaxFlow(int currentCSID, int endCSID, const std::unordered_map<int, std::vector<link>>& linkset, std::unordered_map<int, bool>& visited) {
	// Если достигли конечной компрессорной станции
	if (currentCSID == endCSID) {
		return std::numeric_limits<int>::max(); // Вернуть "бесконечность", если достигли конца
	}

	visited[currentCSID] = true; // Отметить текущую станцию как посещенную
	double maxFlow = 0; // Инициализация максимального потока

	// Проходим по всем трубопроводам, исходящим из текущей компрессорной станции
	for (const auto& l : linkset) {
		for (const auto& connection : l.second) {
			// Если у нас есть связь с текущей КС и она еще не посещена
			if (connection.csInID == currentCSID && !visited[connection.csOutID]) {
				double capacity = pipemap[connection.pipeID].getCapacity(); // Получаем емкость трубы
				double availableFlow = findMaxFlow(connection.csOutID, endCSID, linkset, visited); // Ищем поток дальше
				if (availableFlow > 0) { // Если есть доступный поток
					// Находим минимальный поток на текущем пути
					double currentFlow = std::min(static_cast<double>(capacity), availableFlow);
					maxFlow = std::max(maxFlow, currentFlow);
				}
			}
		}
	}

	visited[currentCSID] = false; // Возвращаем текущую станцию к непосещенной
	return maxFlow; // Вернуть максимальный поток
}

void refinary::printPath(int endCSID, const std::unordered_map<int, int>& predecessor) {
	std::vector<int> path;
	for (int at = endCSID; at != -1; at = predecessor.at(at)) {
		path.push_back(at);
	}
	std::reverse(path.begin(), path.end());

	std::cout << "Path: ";
	for (const auto& csID : path) {
		std::cout << csID << " "; // Выводим путь
	}
	std::cout << std::endl;
}

void refinary::start_pathlen() {

	int startCSID, endCSID;
	std::cout << "Start CS ID: ";
	std::cin >> startCSID;
	std::cout << "Finish CD ID: ";
	std::cin >> endCSID;

	// Параметры для отслеживания посещенных узлов
	std::unordered_map<int, bool> visited;
	std::unordered_map<int, int> predecessor;
	for (const auto& link : linkset) {
		for (const auto& conn : link.second) {
			predecessor[conn.csOutID] = -1; // Инициализируем предшественников
			predecessor[conn.csInID] = -1;
		}
	}
	// Нахождение максимального потока
	double maxFlow = findMaxFlow(startCSID, endCSID, linkset, visited);

	if (maxFlow > 0 && startCSID != endCSID) {
		std::cout << "Max len between " << startCSID << " and " << endCSID << ": " << maxFlow << std::endl;
	}
	else {
		std::cout << "Max len between " << startCSID << " and " << endCSID << " not found" << std::endl;
	}

	printPath(endCSID, predecessor); // Выводим путь
}








void refinary::dijkstra(int startCSID, int endCSID, const std::unordered_map<int, std::vector<link>>& linkset) {
	// Минимальные емкости и предшественники
	std::unordered_map<int, double> minCapacity;
	std::unordered_map<int, int> prev;
	std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<>> pq;

	// Инициализация
	for (const auto& [id, _] : linkset) {
		minCapacity[id] = std::numeric_limits<double>::lowest(); // Инициализируем наименьшими значениями
	}
	minCapacity[startCSID] = std::numeric_limits<double>::max(); // Стартовая станция

	pq.push({ minCapacity[startCSID], startCSID });

	while (!pq.empty()) {
		auto [currentCapacity, currentCSID] = pq.top();
		pq.pop();

		// Если достигли конечной станции
		if (currentCSID == endCSID) {
			break;
		}

		// Проверяем, есть ли исходящие связи из текущей станции
		if (linkset.find(currentCSID) != linkset.end()) {
			for (const auto& connection : linkset.at(currentCSID)) {
				double capacity = pipemap[connection.pipeID].getCapacity(); ; // Получаем емкость трубопровода
				double newCapacity = std::min(currentCapacity, capacity); // Минимальная емкость

				if (newCapacity > minCapacity[connection.csOutID]) {
					minCapacity[connection.csOutID] = newCapacity; // Обновляем наименьшую емкость
					prev[connection.csOutID] = currentCSID;
					pq.push({ newCapacity, connection.csOutID });
				}
			}
		}
	}

	// Восстановление пути
	if (minCapacity[endCSID] > 0) {
		std::cout << "Shortest path with capacity: " << minCapacity[endCSID] << std::endl;

		std::vector<int> path;
		for (int at = endCSID; at != startCSID; at = prev.at(at)) {
			path.push_back(at);
		}
		path.push_back(startCSID);
		std::reverse(path.begin(), path.end());

		std::cout << "Path: ";
		for (const auto& stationID : path) {
			std::cout << stationID << " ";
		}
		std::cout << std::endl;
	}
	else {
		std::cout << "Path not found between " << startCSID << " and " << endCSID << "." << std::endl;
	}
}

void refinary::start_short() {

	// Ввод начальной и конечной компрессорной станции
	int startCSID, endCSID;
	std::cout << "Start CS ID: ";
	std::cin >> startCSID;
	std::cout << "Finnish CS ID: ";
	std::cin >> endCSID;

	// Вызываем алгоритм Дейкстры
	dijkstra(startCSID, endCSID, linkset);

}

	//строим матрицы из мапы
	//колв-во цехов = колв-во входов = кол-во выходов, кол-во входных и выходных труб не должны привышать кол-во возможный
	// можно, нельзя подсоединить (зависит от цехов)
	//найти свободную трубу (чтобы она не в ремонте)
	//создание класса система(есть) вкл мапы с трубами станциами и соединениями между ними
	// все соединяем, айди присваеваем и т.д

	//можнг сделать отдельный класс отвечающий за работу к графами - лучше так сделать
	//гтс должна иметь ф-ю экспорт или построить граф(матрицу в каком-то виде) загружаем в другой класс графа и он все считает
	//сопостовление вершин, граф у нас ориентированный, будет в 4 лабе вес ребра
	//у нас айди реально объяекта и отдельно идентификатор ребра и вершин, вершины будем нумеровать 12345 и т.д вместо реал  айди
	//граф строит тополог сортировку
	//выдает вершина такая ребро такое вершина такя
	//обратно  переводим в реалльные вершины
	//и рисуем в каком-то виде нашу систему
	// 
	//должно быть 2 функции коннект и дисконнект трубы со 2 лабы есть удаление
	//не удаляем соединенные трубы с газом!!!! спрашиваем сначала что надо дисконектнуть (спросить в эдиторе это)
	//короче если обхект есть в графе  (кс тоже) то надо для нее спросить подтверждение убрать все трубы, трубы переводим в свободный режим
	//алг проверки создать соединить трубы создать трубу которо йнет
	// в выводе должна быть информация кто с кем соединен
	//не рисунками а словами (стрелочками там
	//пакетное удаление всех труб в ремонте??????????????

