#ifndef ADJACENCYLIST
#define ADJACENCYLIST

#include <iostream>
#include <vector>
#include <string>
#include "ScheduleTable.h"

using namespace std;


enum Filter
{
	BEST_PRICE,
	BEST_TIME
};

class AdjacencyMatrix
{
	friend class Graph;
private:
	//vector<vector<int>> listData;
	vector<string> stations;
	vector<vector<vector<Train*>>> listData;
	int countOfRibs; // колличество рёбер


public:
	AdjacencyMatrix(const ScheduleTable& st)
	{
		/*setStations(st);
		list.resize(stations.size());
		for (auto& i : list)
		{
			i.resize(stations.size());
		}

		for (size_t i = 0; i < stations.size(); i++)
		{
			for (size_t j = 0; j < stations.size(); j++)
			{
				for (const auto& k : st.getInfoAboutTrains())
				{
					if (stations[i] == k->getDepartureStation() && stations[j] == k->getArrivalStation())
					{
						list[i][j] = 1;
					}
				}
			}
		}*/

		setStations(st); // заповнюємо станції
		setSizeOfTableGraph(); // встановлюєм о вершини для розміру таблиці

		for (size_t i = 0; i < listData.size(); i++)
		{
			for (size_t j = 0; j < listData[i].size(); j++)
			{
				for (const auto& k : st.getInfoAboutTrains())
				{
					if (stations[i] == k->getDepartureStation() && stations[j] == k->getArrivalStation())
					{
						listData[i][j].push_back(k);
					}
				}
			}
		}
		for (size_t i = 0; i < listData.size(); i++)
		{
			for (size_t j = 0; j < listData.size(); j++)
			{
				if (listData[i][j].size() != 0) countOfRibs++;
			}
		}
	}

	//	for (size_t i = 0; i < listData.size(); i++)
	//	{
	//		for (size_t j = 0; j < listData[i].size(); j++)
	//		{
	//			for (const auto& k : st.getInfoAboutTrains())
	//			{
	//				if (stations[i] == k->getDepartureStation() && stations[j] == k->getArrivalStation())
	//				{
	//					listData[i][j] = 1;
	//				}
	//			}
	//		}
	//	}

	//	for (size_t i = 0; i < stations.size(); i++)
	//	{
	//		for (size_t j = 0; j < stations.size(); j++)
	//		{
	//			if (listData[i][j] != 1)listData[i][j] = 0;
	//		}
	//	}

	//	//// output
	//	for (size_t i = 0; i < stations.size(); i++)
	//	{
	//		for (size_t j = 0; j < stations.size(); j++)
	//		{
	//			cout << listData[i][j] << " ";
	//		}
	//		cout << endl;
	//	}
	//

	vector<vector<vector<Train*>>> getListData() { return listData; }


	vector<vector<double>> getAdjacencyMatrix(Filter filter)
	{
		vector<vector<double>> AdjacencyList;
		AdjacencyList.resize(stations.size());
		for (size_t i = 0; i < AdjacencyList.size(); i++)
		{
			AdjacencyList[i].resize(stations.size());
		}

		for (size_t i = 0; i < AdjacencyList.size(); i++)
		{
			for (size_t j = 0; j < AdjacencyList[i].size(); j++)
			{
				AdjacencyList[i][j] = getBestVariant(i, j, filter);
			}
		}
		return AdjacencyList;
	}

private:
	double getBestVariant(int row, int col, Filter filter)
	{
		if (listData[row][col].size() == 0) return 0;
		if (filter == BEST_PRICE)
		{
			Train* ticketWithBestPrice = listData[row][col][0]; 
			for (size_t i = 1; i < listData[row][col].size(); i++)
			{
				if (ticketWithBestPrice->getCostOfTicket() > listData[row][col][i]->getCostOfTicket())
				{
					ticketWithBestPrice = listData[row][col][i];
				}
			}
			return ticketWithBestPrice->getCostOfTicket();
		}
	}

	void setSizeOfTableGraph()
	{
		listData.resize(stations.size());
		for (size_t i = 0; i < listData.size(); i++)
		{
			listData[i].resize(stations.size());
		}
	}

	void setStations(const ScheduleTable& st)
	{
		string departureTimeEachTrain;
		for (size_t i = 0; i < st.getInfoAboutTrains().size(); i++)
		{
			departureTimeEachTrain = st[i]->getDepartureStation();
			if (notEqual(departureTimeEachTrain))
			{
				stations.push_back(departureTimeEachTrain);
			}
		}
	/*	cout << stations.size() << endl;
		for (auto& i : stations)
		{
			cout << i << '\n';
		}*/
	}
	bool notEqual(string a) // rename!
	{
		for (size_t i = 0; i < stations.size(); i++)
		{
			if (stations[i] == a) return false;
		}
		return true;
	}

};


#endif // !ADJACENCYLIST


