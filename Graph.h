#pragma once
#include "Maze.h"
#include "Cell.h"

#ifdef NDEBUG
constexpr auto RUN_TYPE = "RELEASE";
#else
constexpr auto RUN_TYPE = "DEBUG";
#endif

template<class T> class Node;
template<class T> class Edge;
template<class T> class Graph;
template<class T> class CmpNodePtrsForDijkstra;
template<class T> class CmpNodePtrsForAStar;
class Cell;

// Klasa Node (bo Vertex jest zajête w enum) czyli wierzcho³ka grafu
template<class T>
class Node {
	T data;
	std::vector<Edge<T>> neighbours;
	bool visited;
	Node<T>* parent;
	double cost_to_parent;
	double cost_to_origin;
	double predicted_cost;
	double total_cost;
public:
	Node(T data);
	void addEdge(Node<T>* dest, double cost);

	friend class Graph<T>;
	friend class CmpNodePtrsForDijkstra<T>;
	friend class CmpNodePtrsForAStar<T>;
	template<class T> friend std::ostream& operator<<(std::ostream& os, const Graph<T>& g);
};

template<class T>
class CmpNodePtrsForDijkstra
{
public:
	bool operator()(const Node<T>* l, const Node<T>* r) const
	{
		return l->cost_to_origin > r->cost_to_origin;
	}
};

template<class T>
class CmpNodePtrsForAStar
{
public:
	bool operator()(const Node<T>* l, const Node<T>* r) const
	{
		return l->total_cost > r->total_cost;
	}
};

template<class T>
inline Node<T>::Node(T data)
{
	this->data = data;
	this->visited = false;
	this->parent = nullptr;
	this->cost_to_parent = 0;
	this->cost_to_origin = FLT_MAX;
	this->predicted_cost = 0;
	this->total_cost = FLT_MAX;
}

template<class T>
inline void Node<T>::addEdge(Node<T>* dest, double cost)
{
	Edge<T> temp(dest, cost);
	this->neighbours.push_back(temp);
}

// Klasa Edge czyli krawêdzi grafu
template<class T>
class Edge {
	Node<T>* dest;
	double cost;
	bool visited;
public:
	Edge(Node<T>* dest, double cost);

	friend class Node<T>;
	friend class Graph<T>;
	template<class T> friend std::ostream& operator<<(std::ostream& os, const Graph<T>& g);
};

template<class T>
inline Edge<T>::Edge(Node<T>* dest, double cost) : dest(dest), cost(cost), visited(false) {};

// Klasa Graph
template<class T>
class Graph {
	std::vector<Node<T>*> vertices;
public:
	Graph() = default;
	~Graph();
	void addVertex(const T&);
	void addEdge(const T&, const T&, double);
	Node<T>* findVertex(const T&);
	int size();

	// Konstruktor konwertuj¹cy labirynt na graf
	Graph(const Maze&);
private:
	void findNeighbour(Maze&, const Cell&);
	void findDiagonalNeigbour(int x, int y, Maze& map, const Cell& vertex);
	void findStraightNeighboursRec(Maze&, const Cell&, const Cell&, int, int);

public:
	template<class T> friend std::ostream& operator<<(std::ostream& os, const Graph<T>& g);

public:
	Path<T> dfs(T, T);
	Path<T> dijkstra(T, T);
	Path<T> bfs(T, T);
	Path<T> Astar(T, T, double (*predict_distance)(Cell&, Cell&));

private:
	void resetVisits();
	void saveDuration(unsigned int, int, std::string);
};

template<class T>
T shift(T x, T y) {
	return x + y;
}

template<class T>
inline Graph<T>::~Graph()
{
	for (auto& vertex : this->vertices) {
		delete vertex;
	}
	vertices.clear();
}

template<class T>
inline void Graph<T>::addVertex(const T& data)
{
	if (findVertex(data) != nullptr) {
		std::cerr << "Vertex already exists!" << "\n";
		return;
	}

	Node<T>* temp = new Node<T>(data);
	this->vertices.push_back(temp);
}

template<class T>
inline void Graph<T>::addEdge(const T& source, const T& dest, double cost)
{
	Node<T>* sourceTemp = nullptr;
	Node<T>* destTemp = nullptr;

	for (auto& vertex : this->vertices) {
		if (vertex->data == source) {
			sourceTemp = vertex;
		}
		if (vertex->data == dest) {
			destTemp = vertex;
		}
		if (sourceTemp != nullptr && destTemp != nullptr) {
			break;
		}
	}

	if (sourceTemp == nullptr) {
		std::cerr << "Source vertex does not exists" << "\n";
		return;
	}

	if (destTemp == nullptr) {
		std::cerr << "Destination vertex does not exists" << "\n";
		return;
	}

	sourceTemp->addEdge(destTemp, cost);
	//destTemp->addEdge(sourceTemp, cost);
}

template<class T>
inline Node<T>* Graph<T>::findVertex(const T& data)
{
	for (auto& vertex : this->vertices) {
		if (vertex->data == data) {
			return vertex;
		}
	}
	return nullptr;
}

template<class T>
inline int Graph<T>::size()
{
	return this->vertices.size();
}

template<class T>
inline Graph<T>::Graph(const Maze& labirynt)
{
	for (auto& row : labirynt.map) {
		for (auto& element : row.second) {
			Cell temp = element.second;
			if (temp.getIfVertex()) {
				this->addVertex(temp);
			}
		}
	}

	Maze& map = const_cast<Maze&>(labirynt);

	for (auto& vertex : vertices) {
		Cell temp = vertex->data;
		findNeighbour(map, temp);
	}
}

template<class T>
inline void Graph<T>::findNeighbour(Maze& map, const Cell& vertex)
{
	int x = vertex.getX();
	int y = vertex.getY();

	findDiagonalNeigbour(x, y, map, vertex);

	findStraightNeighboursRec(map, vertex, vertex, 1, 0);
	findStraightNeighboursRec(map, vertex, vertex, -1, 0);
	findStraightNeighboursRec(map, vertex, vertex, 0, 1);
	findStraightNeighboursRec(map, vertex, vertex, 0, -1);
}

template<class T>
inline void Graph<T>::findDiagonalNeigbour(int x, int y, Maze& map, const Cell& vertex)
{
	for (int i = x - 1; i <= x + 1; i += 2) {
		for (int j = y - 1; j <= y + 1; j += 2) {
			Cell temp = map.map[i][j];
			if (temp.getIfVertex()) {
				double cost = vertex.calculateDistance(temp);
				this->addEdge(vertex, temp, cost);
			}
		}
	}
}

template<class T>
inline void Graph<T>::findStraightNeighboursRec(Maze& map, const Cell& origin, const Cell& vertex, int a, int b)
{
	if (!vertex) {
		return;
	}

	if (origin != vertex) {
		if (vertex.getIfVertex()) {
			double cost = origin.calculateDistance(vertex);
			this->addEdge(origin, vertex, cost);
			return;
		}
	}

	int x = vertex.getX();
	int y = vertex.getY();

	if (x <= 0 || y <= 0) {
		return;
	}

	findStraightNeighboursRec(map, origin, map.map[shift(x, a)][shift(y, b)], a, b);
}

template<class T>
inline Path<T> Graph<T>::dfs(T start, T finish)
{
	resetVisits();

	int counter = 0;

	Node<T>* startVertex = findVertex(start);

	Path<T> result;
	result.name = "DFS";

	if (startVertex == nullptr) {
		std::cerr << "Start vertex not found" << "\n";
		result.total_length = -1;
		result.steps = -1;
		return result;
	}

	std::stack<Node<T>*> stack;
	stack.push(startVertex);

	auto timeStart = std::chrono::high_resolution_clock::now();

	while (true) {
		Node<T>* vertex = stack.top();
		vertex->visited = true;

		if (vertex->data == finish) {
			do {
				result.route.push_back(vertex->data);
				result.total_length += vertex->cost_to_parent;
				result.steps++;
				vertex = vertex->parent;
			} while (vertex != startVertex);

			break;
		}

		int unvisited = 0;
		for (auto& edge : vertex->neighbours) {
			if (edge.dest->visited != true) {
				edge.dest->parent = vertex;
				edge.dest->cost_to_parent = edge.cost;
				stack.push(edge.dest);
				unvisited += 1;
				counter++;
			}
		}

		if (unvisited == 0) {
			stack.pop();
		}
	}

	auto stop = std::chrono::high_resolution_clock::now();

	unsigned int duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - timeStart).count();

	saveDuration(duration, counter, "DFS");

	if (result.route.size() == 0) {
		std::cerr << "Path not found\n";
		Cell error(-1, -1);
		result.route.push_back(error);
		result.steps = -1;
		result.total_length = -1;
		return result;
	}

	result.route.push_back(startVertex->data);

	std::reverse(result.route.begin(), result.route.end());

	return result;
}

template<class T>
inline Path<T> Graph<T>::dijkstra(T start, T finish)
{
	resetVisits();

	int counter = 0;

	Node<T>* startVertex = findVertex(start);

	Path<T> result;
	result.name = "Dijkstra";

	if (startVertex == nullptr) {
		std::cerr << "Start vertex not found" << "\n";
		result.total_length = -1;
		result.steps = -1;
		return result;
	}

	startVertex->cost_to_origin = 0;

	//TODO Optimize priority queue
	std::priority_queue<Node<T>*, std::vector<Node<T>*>, CmpNodePtrsForDijkstra<T>> path_queue;
	path_queue.push(startVertex);

	auto timeStart = std::chrono::high_resolution_clock::now();

	while (path_queue.empty() == 0) {
		Node<T>* vertex = path_queue.top();
		std::vector<Edge<T>> adjacent_edges = vertex->neighbours;
		path_queue.pop();

		vertex->visited = true;

		if (vertex->data == finish) {
			result.total_length += vertex->cost_to_origin;
			do {
				result.route.push_back(vertex->data);
				result.steps++;
				vertex = vertex->parent;
			} while (vertex != startVertex);

			break;
		}

		for (auto& adjacent_edge : adjacent_edges) {
			if (adjacent_edge.dest->visited != true) {
				float distance = adjacent_edge.cost + vertex->cost_to_origin;

				if (adjacent_edge.dest->cost_to_origin > distance) {
					adjacent_edge.dest->cost_to_origin = distance;
					adjacent_edge.dest->parent = vertex;
					path_queue.push(adjacent_edge.dest);
				}

				counter++;
			}
		}
	}

	auto stop = std::chrono::high_resolution_clock::now();

	unsigned int duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - timeStart).count();

	saveDuration(duration, counter, "Dijkstra");

	if (result.route.size() == 0) {
		std::cerr << "Path not found\n";
		Cell error(-1, -1);
		result.route.push_back(error);
		result.steps = -1;
		result.total_length = -1;
		return result;
	}

	result.route.push_back(startVertex->data);

	std::reverse(result.route.begin(), result.route.end());

	return result;
}

template<class T>
inline Path<T> Graph<T>::bfs(T start, T finish)
{
	resetVisits();

	int counter = 0;

	Node<T>* startVertex = findVertex(start);

	Path<T> result;
	result.name = "BFS";

	if (startVertex == nullptr) {
		std::cerr << "Start vertex not found" << "\n";
		result.total_length = -1;
		result.steps = -1;
		return result;
	}

	std::queue<Node<T>*> path_queue;
	path_queue.push(startVertex);

	auto timeStart = std::chrono::high_resolution_clock::now();

	while (path_queue.empty() == 0) {
		Node<T>* vertex = path_queue.front();
		std::vector<Edge<T>> adjacent_edges = vertex->neighbours;
		path_queue.pop();

		vertex->visited = true;

		if (vertex->data == finish) {
			do {
				result.route.push_back(vertex->data);
				result.steps++;
				result.total_length += vertex->cost_to_parent;
				vertex = vertex->parent;
			} while (vertex != startVertex);

			break;
		}

		for (auto& adjacent_edge : adjacent_edges) {
			if (adjacent_edge.dest->visited != true) {
				adjacent_edge.dest->parent = vertex;
				adjacent_edge.dest->cost_to_parent = adjacent_edge.cost;
				path_queue.push(adjacent_edge.dest);
				counter++;
			}
		}
	}

	auto stop = std::chrono::high_resolution_clock::now();

	unsigned int duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - timeStart).count();

	saveDuration(duration, counter, "BFS");

	if (result.route.size() == 0) {
		std::cerr << "Path not found\n";
		Cell error(-1, -1);
		result.route.push_back(error);
		result.steps = -1;
		result.total_length = -1;
		return result;
	}

	result.route.push_back(startVertex->data);

	std::reverse(result.route.begin(), result.route.end());

	return result;
}

template<class T>
inline Path<T> Graph<T>::Astar(T start, T finish, double (*predict_distance)(Cell&, Cell&))
{
	resetVisits();

	int counter = 0;

	Node<T>* startVertex = findVertex(start);

	Path<T> result;
	result.name = "A*";

	if (startVertex == nullptr) {
		std::cerr << "Start vertex not found" << "\n";
		result.total_length = -1;
		result.steps = -1;
		return result;
	}

	startVertex->cost_to_origin = 0;
	startVertex->predicted_cost = predict_distance(startVertex->data, finish);
	startVertex->total_cost = startVertex->cost_to_origin + startVertex->predicted_cost;

	std::priority_queue<Node<T>*, std::vector<Node<T>*>, CmpNodePtrsForAStar<T>> path_queue;
	path_queue.push(startVertex);

	auto timeStart = std::chrono::high_resolution_clock::now();

	while (path_queue.empty() == 0) {
		Node<T>* vertex = path_queue.top();
		std::vector<Edge<T>> adjacent_edges = vertex->neighbours;
		path_queue.pop();

		vertex->visited = true;

		if (vertex->data == finish) {
			result.total_length += vertex->cost_to_origin;
			do {
				result.route.push_back(vertex->data);
				result.steps++;
				vertex = vertex->parent;
			} while (vertex != startVertex);

			break;
		}

		for (auto& adjacent_edge : adjacent_edges) {
			if (adjacent_edge.dest->visited != true) {
				double distance_to_origin = adjacent_edge.cost + vertex->cost_to_origin;
				adjacent_edge.dest->predicted_cost = predict_distance(adjacent_edge.dest->data, finish);
				double total = distance_to_origin + adjacent_edge.dest->predicted_cost;

				if (adjacent_edge.dest->total_cost > total) {
					adjacent_edge.dest->cost_to_origin = distance_to_origin;
					adjacent_edge.dest->total_cost = total;
					adjacent_edge.dest->parent = vertex;
					path_queue.push(adjacent_edge.dest);
				}

				counter++;
			}
		}
	}

	auto stop = std::chrono::high_resolution_clock::now();

	unsigned int duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - timeStart).count();

	saveDuration(duration, counter, "A*");

	if (result.route.size() == 0) {
		std::cerr << "Path not found\n";
		Cell error(-1, -1);
		result.route.push_back(error);
		result.steps = -1;
		result.total_length = -1;
		return result;
	}

	result.route.push_back(startVertex->data);

	std::reverse(result.route.begin(), result.route.end());

	return result;
}

template<class T>
inline void Graph<T>::resetVisits()
{
	for (auto& vertex : this->vertices) {
		vertex->visited = false;
		vertex->parent = nullptr;
		vertex->cost_to_parent = 0;
		vertex->cost_to_origin = FLT_MAX;
		vertex->predicted_cost = 0;
		vertex->total_cost = FLT_MAX;
	}
}

template<class T>
inline void Graph<T>::saveDuration(unsigned int duration, int iterations, std::string algorithm_name)
{
	std::string fileName = "time.log";

	std::ofstream file;
	file.open(fileName, std::ios::app);

	if (!file.good()) {
		std::cout << "Nie udalo sie otworzyc pliku: " << fileName << std::endl;
		return;
	}

	file << algorithm_name << ": " << duration << " microseconds, iterations: " << iterations << ", on: " << RUN_TYPE << "\n";

	file.close();

	std::cout << algorithm_name << " done. Time saved to: " << fileName << "\n";
}

template<class T>
std::ostream& operator<<(std::ostream& os, const Graph<T>& g)
{
	for (auto& vertex : g.vertices) {
		os << "Vertex: " << vertex->data << "\n";
		os << "(Total cost, predicted cost, cost to origin)\n";
		os << "(" << (vertex->total_cost == FLT_MAX ? "INF" : std::to_string(vertex->total_cost)) << ", " << vertex->predicted_cost << ", " << (vertex->cost_to_origin == FLT_MAX ? "INF" : std::to_string(vertex->cost_to_origin)) << ")\n";
		os << "Edges:\n";
		os << "(Source, Destination, Cost)\n";
		for (auto& edge : vertex->neighbours) {
			os << "(" << vertex->data << ", " << edge.dest->data << ", " << edge.cost << ")\n";
		}
	}

	return os;
}
