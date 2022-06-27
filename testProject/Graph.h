#ifndef GRAPH
#define GRAPH

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <algorithm>
#include "AdjacencyMatrix.h"

template<class T>
struct WayAndInfo
{
	WayAndInfo(std::list<int> list, double value)
	{
		this->list = list;
		this->value = value;
	}
	std::list<int> list;
	T value;
};

class Graph
{
private:
	std::vector<std::vector<int>> graph; // здесь хранится список смежности
	std::vector<std::pair<int, int>> allVariants; // всевозможны варианты пар из числа n 
	std::vector<std::list<int>> routs; // все найденные пути между заданной парой вершин
	std::list<int> path; // найденный путь
	std::set<std::set<int>> ribs; // рёбра
	std::vector<std::vector<double>> adjMatrix; // матрица смежности которая хранит билеты лучшие по цене
	AdjacencyMatrix& obj; // ссылка на объект AdjacencyMatrix для упрощенной работы с данными
public:
	Graph(AdjacencyMatrix& obj1);
	void fillGraph(AdjacencyMatrix& list);
	void printAdjacencyList();
	void findAllWays();
	void deleteExcessiveWays();
	void outPutBestTime(int countVariants);
	void outPutBestPrice(int countVariants);

private:
	void dfs(int const& nodeCur, int const& nodeLast);
	size_t bestTimeTrain(int row, int col);
};


#endif // !GRAPH
