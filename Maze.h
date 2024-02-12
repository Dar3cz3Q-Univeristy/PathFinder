#pragma once
#include "Cell.h"
#include "Path.h"

template<class T> class Graph;
class Cell;

class Maze
{
	std::map<int, std::map<int, Cell>> map;
	int rows, columns;
	bool vertexesShown;
	int start[2];
	int finish[2];
public:
	Maze();
	void initializeFromFile(std::string);
	void analyzeMaze();
	void visualizePath(Path<Cell>);
	void changeVertexesApperance(bool);
	void resetPath();

	friend std::ostream& operator<<(std::ostream& os, const Maze& m);
	friend class Cell;
	friend class Graph<Cell>;
private:
	int getRows() const;
	int getCols() const;
	bool isCorner(int, int);
	bool isIntersection(int, int);
};

