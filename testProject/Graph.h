#ifndef GRAPH
#define GRAPH

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "AdjacencyList.h"
#include <set>
#include <list>
#include <algorithm>
#include <map>
using namespace std;


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
	vector<vector<int>> graph;
	vector<pair<int, int>> allVariants;
	std::vector<std::list<int>> routs; // все найденные пути между заданной парой вершин
	std::list<int> path; // найденный путь
	std::set<std::set<int>> ribs; // рёбра
	vector<vector<double>> adjMatrix;
	AdjacencyMatrix& obj;
public:

	Graph(AdjacencyMatrix& obj1) : obj(obj1)
	{
	}

	void fillGraph(AdjacencyMatrix& list, Filter filter)
	{
		adjMatrix = list.getAdjacencyMatrix(filter);
		graph.resize(adjMatrix.size());
		for (int i = 0; i < adjMatrix.size(); ++i) 
		{
			for (int j = 0; j < adjMatrix.size(); ++j) 
			{
				if (adjMatrix[i][j]) graph[i].push_back(j+1);
			}
		}
		for (size_t i = 1, j = 1; i <= graph.size(); j++)
		{
			if (i != j && j <= graph.size())
			{
				allVariants.push_back(make_pair(i, j));
			}
			if (j > graph.size())
			{
				i++; j = 0;   
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

	void findAllWays()
	{
		cout << "Please Wait..." << endl;
		for (const auto& i : allVariants)
		{
			dfs(i.first, i.second);
		}
	}



	void dfs(int const& nodeCur, int const& nodeLast)
	{
		path.emplace_back(nodeCur);

		if (nodeCur == nodeLast)
		{
			routs.push_back(path);
			path.pop_back();
			return;
		}

		for (auto const& val : graph.at(nodeCur - 1))
		{
			std::set<int> rib = { nodeCur, val};
			if (ribs.find(rib) == ribs.end())
			{
				ribs.emplace(rib);
				dfs(val, nodeLast);
				ribs.erase(ribs.find(rib));
			}
		}
		path.pop_back();
	}
	void deleteExcessiveWays() // отбираем нужные
	{
		vector<list<int>> temp;
		for (size_t i = 0; i < routs.size(); i++)
		{
			bool out = false;
			if (routs[i].size() == 6)
			{
				for (auto it = routs[i].begin(); it != routs[i].end(); it++)
				{
					int similar = 0;
					for (auto it2 = routs[i].begin(); it2 != routs[i].end(); it2++)
					{
						if (*it == *it2) similar++;
						if (similar >= 2)
						{
							out = true;
							break;
						}
					}
					if (out) break;
				}

				if (!out) temp.push_back(routs[i]);
			}
		}
		routs = temp;
	}
	// для реализации поиска наименьшого времени был использован жадный алгоритм. Он не самый точный, однако банальный перебор займёт уж слишком много памяти у компьютера, 
	// поэтому придётся пожертвовать точностью
	void bestTimeForEachWay(int countVariants)
	{
		vector<int> vectorOfTime;
		vector<WayAndInfo<int>*> time_path;
		for (size_t i = 0; i < routs.size(); i++) // все пути (144)
		{
			int previousIndexOfBestTrain; // для подсчёта ожидания следущего поезда нужно хранить время прибытия предыдущего 
			int time = 0;
			for (auto it1 = routs[i].cbegin(), it2 = ++routs[i].cbegin(); it2 != routs[i].cend(); ++it1, ++it2) // передвижение между станциями
			{
				if (it1 == routs[i].begin())
				{
					previousIndexOfBestTrain = bestTimeTrain(*it1-1, *it2-1); // в 1 вершине отбираем поезд с наименьшим временем поездки
					time += obj.listData[*it1 - 1][*it2 - 1][previousIndexOfBestTrain]->getArrivalTime() - obj.listData[*it1 - 1][*it2 - 1][previousIndexOfBestTrain]->getDepartureTime();
					if (time <= 0)  // здесь не может время равнятся нулю, ибо тогда фактически поезд приезжает не начиная движения. Вместо этого мы будем говорить что поезд ехал сутки.
					{
						time += 24 * 3600;
					}
				}
				else
				{
					vector<int> allTimesBetweenStations; // здесь сохраняются последующие время пути. Только здесь уже будет учитываться время ожидания.
					for (auto& s : obj.listData[*it1-1][*it2-1])
					{
						int timeBetweenLastTrainAndNext = s->getDepartureTime() - obj.listData[*--it1 - 1][*--it2 - 1][previousIndexOfBestTrain]->getArrivalTime(); 
						if (s->getDepartureTime() - obj.listData[*it1 - 1][*it2 - 1][previousIndexOfBestTrain]->getArrivalTime() < 0) // здесь результат вычитания может равняться нулю, что будет говорить о моментальной посадке на следущий поезд
						{
							timeBetweenLastTrainAndNext += 24 * 3600;
						}
						int travelTime = s->getArrivalTime() - s->getDepartureTime();
						if (s->getArrivalTime() - s->getDepartureTime() <= 0) // результат вычитания может быть нулевым, что означает, что поезд был в пути сутки
						{
							 travelTime += 24 * 3600;
						}
						
						it1++; it2++; // чтобы взять значение предыдущего элемента мы откатывали итератор на 1 позицию назад, поэтому возвращаем их в нормальную позицию
						allTimesBetweenStations.push_back(timeBetweenLastTrainAndNext + travelTime);
					}

					std::sort(allTimesBetweenStations.begin(), allTimesBetweenStations.end()); // от меньшего к большему
					time += allTimesBetweenStations[0]; // добавляем ко времени наименьший результат
					previousIndexOfBestTrain = 0;
					/*else
					{
						min = obj.listData[*--it1][*--it2][previousIndexOfBestTrain]->getArrivalTime() - obj.listData[*++it1][*++it2][0]->getDepartureTime();
					}
					for (auto& i : obj.listData[*it1][*it2])
					{
						if (obj.listData[*it1][*it2][previousIndexOfBestTrain]);
					}*/
				}	

			}
			time_path.push_back(new WayAndInfo<int>(routs[i], time));
		}

		bool isSort = false;
		do
		{
			isSort = false;
			for (size_t i = 0; i < time_path.size() - 1; i++)
			{
				if (time_path[i]->value > time_path[i + 1]->value)
				{
					std::swap(time_path[i], time_path[i + 1]);
					isSort = true;
				}
			}
		} while (isSort);

		for (size_t i = 0; i < countVariants; i++)
		{
			std::string temp;
			for (auto it = time_path[i]->list.begin(); it != time_path[i]->list.end(); it++)
			{
				temp += std::to_string(*it);
				temp += "->";
			}
			temp.pop_back();
			temp.pop_back();
			cout << temp << endl;
			cout << time_path[i]->value << endl;
			cout << "----------------------------------------------------------" << endl;
		}
		cout << "The time in seconds" << endl;

	}



	void outPutBestPrice(int countVariants)
	{
		vector<WayAndInfo<double>*> bestVariants;
		for (size_t i = 0; i < routs.size(); i++)
		{
			double bestVariant = 0;
			for (auto it1 = routs[i].begin(), it2 = ++routs[i].begin(); it2 != routs[i].end(); it1++, it2++)
			{
				bestVariant += adjMatrix[*it1 - 1][*it2 - 1];
			}
			bestVariants.push_back(new WayAndInfo<double>(routs[i], bestVariant));
		}

		//sorting
		bool isSort = false;
		do
		{
			isSort = false;
			for (size_t i = 0; i < bestVariants.size() - 1; i++)
			{
				if (bestVariants[i]->value > bestVariants[i + 1]->value)
				{
					std::swap(bestVariants[i], bestVariants[i + 1]);
					isSort = true;
				}
			}
		} while (isSort);

		//output
		for (size_t i = 0; i < countVariants; i++) 
		{
			std::string temp;
			for (auto it = bestVariants[i]->list.begin(); it != bestVariants[i]->list.end(); it++)
			{
				temp += std::to_string(*it);
				temp += "->";
			}
			temp.pop_back();
			temp.pop_back();
			cout << temp << endl;
			cout << bestVariants[i]->value << endl;
			cout << "----------------------------------------------------------" << endl;
		}

		for (auto& i : bestVariants)
		{
			delete i;
		}
	}

private:
	size_t bestTimeTrain(int row, int col)
	{
		vector<int> timeBetweenStations;
		for (size_t i = 0; i < obj.listData[row][col].size(); i++)
		{
			timeBetweenStations.push_back(obj.listData[row][col][i]->getArrivalTime() - obj.listData[row][col][i]->getDepartureTime());
			if (timeBetweenStations[i] <= 0)
			{
				timeBetweenStations[i] += 24 * 3600;
			}
		}
		size_t minIndex = 0;
		for (size_t i = 0; i < timeBetweenStations.size(); i++)
		{
			if (timeBetweenStations[minIndex] > timeBetweenStations[i])
				minIndex = i;
		}
		return minIndex;

	}
};


#endif // !GRAPH
