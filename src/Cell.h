#pragma once
#include "Maze.h"

class Maze;

enum CellType {
	Invalid,
	Empty = ' ',
	Wall = 'x',
	Start = 'A',
	Finish = 'B',
	Vertex = '.',
	Route = '#'
};

class Cell
{
	CellType type;
	bool isVertex;
	int x;
	int y;
public:
	Cell() : type(Invalid), isVertex(false), x(-1), y(-1) {};
	Cell(int x, int y) : type(Invalid), isVertex(false), x(x), y(y) {};
	Cell(char, int, int);
	Cell(CellType, const Maze&);
	void convertToVertex();
	void convertToPath();
	void convertToEmpty();
	void changeVertexApperance(bool);
	bool isStart() const;
	bool isFinish() const;
	bool isPath() const;
	bool getIfVertex() const;
	double calculateDistance(const Cell&) const;
	int getX() const;
	int getY() const;

	friend std::ostream& operator<<(std::ostream& os, const Cell& c);
	friend std::ostream& display(std::ostream& os, const Cell& c);
	operator bool() const;
	friend bool operator==(const Cell&, const Cell&);
	friend bool operator!=(const Cell&, const Cell&);
};

