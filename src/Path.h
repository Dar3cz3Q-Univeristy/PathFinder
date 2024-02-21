#pragma once
template<class T> class Graph;

template<class T>
class Path
{
	std::string name;
	std::vector<T> route;
	double total_length;
	int steps;
public:
	friend class Graph<T>;
	friend class Maze;
	template<class T> friend std::ostream& operator<<(std::ostream& os, const Path<T>& p);
};

template<class T>
inline std::ostream& operator<<(std::ostream& os, const Path<T>& p)
{
	os << "Path found by: " << p.name << " algorithm.\n";
	auto n = p.route.size();
	int i = 0;
	for (auto& element : p.route) {
		os << element;
		i++;
		if (n != i) {
			os << " -> ";
		}
	}
	os << "\n";
	os << "Total length: " << p.total_length << "\n";
	os << "Total steps: " << p.steps << "\n";
	return os;
}
