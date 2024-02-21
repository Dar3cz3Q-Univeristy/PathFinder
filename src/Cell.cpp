#include "pch.h"
#include "Cell.h"

Cell::Cell(char type, int x, int y) {
	this->isVertex = false;

	switch (type) {
	case 'A':
		this->type = Start;
		this->isVertex = true;
		break;
	case 'B':
		this->type = Finish;
		this->isVertex = true;
		break;
	case 'x':
		this->type = Wall;
		break;
	case ' ':
		this->type = Empty;
		break;
	default:
		this->type = Invalid;
		std::cout << "Niepoprawny znak" << "\n";
		break;
	}

	this->x = x;
	this->y = y;
}

Cell::Cell(CellType type, const Maze& map)
{
	this->type = type;
	this->isVertex = true;
	switch (type)
	{
	case Start:
		this->x = map.start[0];
		this->y = map.start[1];
		break;
	case Finish:
		this->x = map.finish[0];
		this->y = map.finish[1];
		break;
	default:
		this->x = -1;
		this->y = -1;
		this->isVertex = false;
		this->type = Invalid;
		break;
	}
}

void Cell::convertToVertex()
{
	if (!this->isVertex) {
		this->isVertex = true;
	}
}

void Cell::convertToPath()
{
	if (this->type != Start && this->type != Finish) {
		this->type = Route;
	}
}

void Cell::convertToEmpty()
{
	this->type = Empty;
}

void Cell::changeVertexApperance(bool status)
{
	if (status) {
		this->type = Vertex;
	}
	else {
		this->type = Empty;
	}
}

bool Cell::isStart() const
{
	return this->type == Start;
}

bool Cell::isFinish() const
{
	return this->type == Finish;
}

bool Cell::isPath() const
{
	return this->type == Route;
}

bool Cell::getIfVertex() const
{
	return isVertex;
}

double Cell::calculateDistance(const Cell& c) const
{
	double distance = sqrt(pow(this->x - c.x, 2) + pow(this->y - c.y, 2));
	return distance;
}

int Cell::getX() const
{
	return this->x;
}

int Cell::getY() const
{
	return this->y;
}

std::ostream& display(std::ostream& os, const Cell& c)
{
	os << (char)c.type;
	return os;
}

// Returns false if cell is a Wall, else returns true
Cell::operator bool() const
{
	return type != Wall;
}

std::ostream& operator<<(std::ostream& os, const Cell& c) {
	os << c.x << "." << c.y;
	return os;
}

bool operator==(const Cell& lc, const Cell& rc)
{
	return (lc.x == rc.x && lc.y == rc.y) && lc.isVertex == rc.isVertex;
}

bool operator!=(const Cell& lc, const Cell& rc)
{
	return !(lc == rc);
}
