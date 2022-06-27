#ifndef ADJACENCYMATRIX
#define ADJACENCYMATRIX

#include <vector>
#include <string>
#include "ScheduleTable.h"

class AdjacencyMatrix
{
	friend class Graph;
private:
	std::vector<std::string> stations;
	std::vector<std::vector<std::vector<Train*>>> listData;

public:
	AdjacencyMatrix(const ScheduleTable& st);
	std::vector<std::vector<double>> getAdjacencyMatrix();

private:
	double getBestPrice(int row, int col);
	void setSizeOfAdjMatrix();
	void setStations(const ScheduleTable& st);
	bool notEqual(std::string a);
};
#endif // !ADJACENCYMATRIX


