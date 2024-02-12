#include "Maze.h"
#include "Graph.h"

static double euclideanDistance(Cell& c1, Cell& c2) {
	return sqrt(pow(c1.getX() - c2.getX(), 2) + pow(c1.getY() - c2.getY(), 2));
}

static double manhattanDistance(Cell& c1, Cell& c2) {
	return abs(c2.getX() - c1.getX()) + abs(c2.getY() - c1.getY());
}

static double taxiDistance(Cell& c1, Cell& c2) {
	return abs(c1.getX() - c1.getY()) + abs(c2.getX() - c2.getY());
}

int main(int argc, char** argv)
{
	std::string fileName;
	int metricsID = 0;

	double (*metrics[3])(Cell&, Cell&) = { &euclideanDistance, &manhattanDistance, &taxiDistance };

	std::cout << "Provide a file name: ";

	std::cin >> fileName;

	std::cout << "Choose a metric up to A*\n";
	std::cout << "1. Euclidean distance\n";
	std::cout << "2. Manhattan distance\n";
	std::cout << "3. Taxi distance\n";
	std::cout << "Choice: ";

	std::cin >> metricsID;

	if (metricsID != 1 && metricsID != 2 && metricsID != 3) {
		std::cout << "Metrics ID not valid\n";
		return -1;
	}

	std::string resultFileName = "resolved." + fileName;

	std::cout << "Initializing maze\n";

	Maze labirynt;
	labirynt.initializeFromFile(fileName);

	std::cout << "Maze initialized\n";
	std::cout << labirynt << "\n";
	std::cout << "Analyzing maze\n";

	labirynt.analyzeMaze();

	std::cout << "Vertexes added\n";
	std::cout << labirynt << "\n";
	std::cout << "Finding path\n";

	std::ofstream file;
	file.open(resultFileName);

	if (!file.good()) {
		std::cout << "Nie udalo sie otworzyc pliku: " << resultFileName << std::endl;
		return -1;
	}

	Graph<Cell> labirynt_graf = labirynt;
	Cell start(Start, labirynt);
	Cell finish(Finish, labirynt);

	Path<Cell> droga_bfs = labirynt_graf.bfs(start, finish);

	file << droga_bfs;

	labirynt.visualizePath(droga_bfs);

	file << labirynt;

	Path<Cell> droga_dijkstra = labirynt_graf.dijkstra(start, finish);

	file << droga_dijkstra;

	labirynt.visualizePath(droga_dijkstra);

	file << labirynt;

	Path<Cell> droga_Astar = labirynt_graf.Astar(start, finish, metrics[metricsID - 1]);

	file << droga_Astar;

	labirynt.visualizePath(droga_Astar);

	file << labirynt;

	Path<Cell> droga_dfs = labirynt_graf.dfs(start, finish);

	file << droga_dfs;

	labirynt.visualizePath(droga_dfs);

	file << labirynt;

	file.close();

	std::cout << "Results saved to: " << resultFileName;

	return 0;
}
