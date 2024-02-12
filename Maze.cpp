#include "pch.h"
#include "Maze.h"

Maze::Maze()
{
	this->rows = 0;
	this->columns = 0;
	this->vertexesShown = false;
	this->start[0] = -1;
	this->start[1] = -1;
	this->finish[0] = -1;
	this->finish[1] = -1;
}

void Maze::initializeFromFile(std::string fileName)
{
	std::ifstream file;
	file.open(fileName);

	if (!file.good()) {
		std::cout << "Nie udalo sie otworzyc pliku: " << fileName << std::endl;
		return;
	}

	std::string line;
	int i = 0;

	while (getline(file, line)) {
		int j = 0;
		for (auto& letter : line) {
			Cell temp(letter, i, j);
			this->map[i][j] = temp;
			if (temp.isStart()) {
				this->start[0] = i;
				this->start[1] = j;
			}
			if (temp.isFinish()) {
				this->finish[0] = i;
				this->finish[1] = j;
			}
			j++;
		}
		i++;
	}

	this->rows = static_cast<int>(this->map.size());
	this->columns = static_cast<int>(this->map[0].size());

	//std::cout << this->rows << " " << this->columns << std::endl;

	file.close();
}

void Maze::analyzeMaze()
{
	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->columns; j++) {
			Cell current = this->map[i][j];

			if (!current) {
				continue;
			}

			if (!isCorner(i, j) && !isIntersection(i, j)) {
				continue;
			}

			this->map[i][j].convertToVertex();
		}
	}

	changeVertexesApperance(true);
}

int Maze::getRows() const
{
	return this->rows;
}

int Maze::getCols() const
{
	return this->columns;
}

void Maze::visualizePath(Path<Cell> path)
{
	changeVertexesApperance(false);
	resetPath();

	int n = static_cast<int>(path.route.size()) - 1;

	for (int i = 0; i < n; i++) {
		int x = path.route[i].getX();
		int y = path.route[i].getY();

		int next_x = path.route[static_cast<std::vector<Cell, std::allocator<Cell>>::size_type>(i) + 1].getX();
		int next_y = path.route[static_cast<std::vector<Cell, std::allocator<Cell>>::size_type>(i) + 1].getY();

		if (x != next_x && y != next_y) {
			continue;
		}

		int a = (x == next_x) ? y : x;
		int next_a = (x == next_x) ? next_y : next_x;

		for (int j = ((a > next_a) ? next_a : a); j <= ((a > next_a) ? a : next_a); j++) {
			this->map[(x == next_x) ? x : j][(x == next_x) ? j : y].convertToPath();
		}
	}
}

bool Maze::isCorner(int x, int y)
{
	if (!this->map[x][y + 1]) {
		if (!this->map[x - 1][y]) {
			return true;
		}
		if (!this->map[x + 1][y]) {
			return true;
		}
	}

	if (!this->map[x][y - 1]) {
		if (!this->map[x - 1][y]) {
			return true;
		}
		if (!this->map[x + 1][y]) {
			return true;
		}
	}

	return false;
}

bool Maze::isIntersection(int x, int y)
{
	int counter = 0;

	if (map[x][y - 1]) {
		counter++;
	}

	if (map[x][y + 1]) {
		counter++;
	}

	if (map[x - 1][y]) {
		counter++;
	}

	if (map[x + 1][y]) {
		counter++;
	}

	return counter >= 3;
}

void Maze::changeVertexesApperance(bool status)
{
	if (this->vertexesShown == status) {
		return;
	}

	this->vertexesShown = status;

	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->columns; j++) {
			Cell current = this->map[i][j];

			if (current.getIfVertex() && !current.isFinish() && !current.isStart()) {
				this->map[i][j].changeVertexApperance(status);
			}
		}
	}
}

void Maze::resetPath()
{
	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->columns; j++) {
			Cell current = this->map[i][j];

			if (current.isPath()) {
				this->map[i][j].convertToEmpty();
			}
		}
	}
}

std::ostream& operator<<(std::ostream& os, const Maze& m)
{
	for (auto& row : m.map) {
		for (auto& element : row.second) {
			display(os, element.second);
		}
		os << "\n";
	}
	return os;
}
