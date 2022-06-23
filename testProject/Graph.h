#ifndef GRAPH
#define GRAPH

//#include <iostream>
#include <string>
#include <vector>
#include "Train.h"
#include "ScheduleTable.h"
using namespace std;



class Graph
{
private:
	vector<string> stations; 
	vector<vector<Train*>> graphCells;
public:
	Graph() {}
	void fillGraph(const ScheduleTable& st)
	{
		setStations(st); // заповнюємо станції
		setSizeOfTableGraph(); // встановлюємо вершини для розміру таблиці
		
		for (size_t i = 0; i < stations.size(); i++)
		{
			for (size_t j = 0; j < stations.size(); j++)
			{
				for (const auto& k : st.getInfoAboutTrains())
				{
					if (stations[i] == k->getDepartureStation() && stations[j] == k->getArrivalStation())
					{
						graphCells[i][j] = k;
					}
				}
			}
		}
		//cout << 132;
	}
private:
	void setSizeOfTableGraph()
	{
		graphCells.resize(stations.size()); // Вершини - станції
		for (size_t i = 0; i < graphCells.size(); i++)
		{
			graphCells[i].resize(stations.size());
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
		/*cout << stations.size() << endl;
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


#endif // !GRAPH
