#ifndef GRAPH
#define GRAPH

#include <iostream>
#include <string>
#include <vector>
#include "Train.h"
#include "ScheduleTable.h"
#include <queue>
#include "AdjacencyList.h"

using namespace std;

//enum Filter
//{
//	BEST_PRICE,
//	BEST_TIME
//};

class Graph
{
private:

	vector<vector<double>> graph;
	//vector<string> stations;
	//vector<vector<vector<Train*>>> listData;
	//vector<vector<int>> spisokSmezhnosti;
	//int countOfRibs; // колличество рёбер
	//vector<bool> used;
public:
	Graph() {}

	void fillGraph(AdjacencyMatrix& list, Filter filter)
	{
		vector<vector<double>> adjMatrix = list.getAdjacencyList(filter);
		graph.resize(adjMatrix.size());
		for (int i = 0; i < adjMatrix.size(); ++i) 
		{
			for (int j = 0; j < adjMatrix.size(); ++j) 
			{
				if (adjMatrix[i][j]) graph[i].push_back(j);
			}
		}
	}

	void printAdjacencyList()
	{
		for (size_t i = 0; i < graph.size(); i++)
		{
			for (size_t j = 0; j < graph[i].size(); j++)
			{
				cout << graph[i][j] << " ";
			}
			cout << endl;
		}
	}
	//Graph(const AdjacencyList& list)
	//{
	//	graph.resize(list.getAdjacencyList(BEST_PRICE));
	//	for (int i = 0; i < graph.size(); ++i)
	//	{
	//		for (int j = 0; j < graph.size(); ++j)
	//		{
	//			if (list.getAdjacencyList()[i][j]) graph[i].push_back(j);
	//		}
	//	}
	//}
	
	//void fillGraph(const ScheduleTable& st)
	//{
	//	setStations(st); // заповнюємо станції
	//	setSizeOfTableGraph(); // встановлюєм о вершини для розміру таблиці
	//	
	//	for (size_t i = 0; i < stations.size(); i++)
	//	{
	//		for (size_t j = 0; j < stations.size(); j++)
	//		{
	//			for (const auto& k : st.getInfoAboutTrains())
	//			{
	//				if (stations[i] == k->getDepartureStation() && stations[j] == k->getArrivalStation())
	//				{
	//					listData[i][j].push_back(k);
	//				}
	//			}
	//		}
	//	}
	//	for (size_t i = 0; i < listData.size(); i++)
	//	{
	//		for (size_t j = 0; j < listData.size(); j++)
	//		{
	//			if (listData[i][j].size() != 0) countOfRibs++;
	//		}
	//	}
	//	cout << 132;
	//}
private:
	/*Train* getBestVariant(int row ,int col ,Filter filter)
	{
		if (filter == BEST_PRICE)
		{
			Train* bestPrice = listData[row][col][0];
			for (size_t i = 1; i < listData[row][col].size(); i++)
			{
				if (bestPrice->getCostOfTicket() > listData[row][col][i]->getCostOfTicket())
				{
					bestPrice = listData[row][col][i];
				}
			}
			return bestPrice;
		}
		else if (filter == BEST_TIME)
		{

		}
	}*/
	//void setSizeOfTableGraph()
	//{
	//	listData.resize(stations.size()); // Вершини - станції
	//	for (size_t i = 0; i < listData.size(); i++)
	//	{
	//		listData[i].resize(stations.size());
	//	}
	//}
	//void setStations(const ScheduleTable& st)
	//{
	//	string departureTimeEachTrain;
	//	for (size_t i = 0; i < st.getInfoAboutTrains().size(); i++)
	//	{
	//		departureTimeEachTrain = st[i]->getDepartureStation();
	//		if (notEqual(departureTimeEachTrain))
	//		{
	//			stations.push_back(departureTimeEachTrain);
	//		}
	//	}
	//	cout << stations.size() << endl;
	//	for (auto& i : stations)
	//	{
	//		cout << i << '\n';
	//	}
	//}
	//bool notEqual(string a) // rename!
	//{
	//	for (size_t i = 0; i < stations.size(); i++)
	//	{
	//		if (stations[i] == a) return false;
	//	}
	//	return true;
	//}
};


#endif // !GRAPH
