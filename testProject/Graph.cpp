#include "Graph.h"

Graph::Graph(AdjacencyMatrix& obj1) : obj(obj1)
{
}

void Graph::fillGraph(AdjacencyMatrix& list)
{
	// ���������� ������ ���������
	adjMatrix = list.getAdjacencyMatrix();
	graph.resize(adjMatrix.size());
	for (int i = 0; i < adjMatrix.size(); ++i)
	{
		for (int j = 0; j < adjMatrix.size(); ++j)
		{
			if (adjMatrix[i][j]) graph[i].push_back(j + 1);
		}
	}

	// ������������ ���� �� n ��� ������ ����� dfs
	for (size_t i = 1, j = 1; i <= graph.size(); j++)
	{
		if (i != j && j <= graph.size())
		{
			allVariants.push_back(std::make_pair(i, j));
		}
		if (j > graph.size())
		{
			i++; j = 0;
		}
	}
}

void Graph::printAdjacencyList() // ����� ������ ���������
{
	for (size_t i = 0; i < graph.size(); i++)
	{
		for (size_t j = 0; j < graph[i].size(); j++)
		{
			std::cout << graph[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void Graph::findAllWays() // ������� ������� ���������� ������������ ����
{
	std::cout << "Please Wait..." << std::endl;
	for (const auto& i : allVariants)
	{
		dfs(i.first, i.second);
	}
}

void Graph::deleteExcessiveWays() // �������� ������ ���� (��������������� �������, ������ ���� ����� ��������� ����� 6 ���������)
{
	std::vector<std::list<int>> temp; // ��������� ������ ���� ����
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

// ��� ���������� ������ ����������� ������� ��� ����������� ������ ��������. �� �� ����� ������, ������ ��������� ������� ����� �� ������� ����� ������ � ����������, 
// ������� ������� ������������ ���������
void Graph::outPutBestTime(int countVariants)
{
	std::vector<int> vectorOfTime;
	std::vector<WayAndInfo<int>*> time_path;
	for (size_t i = 0; i < routs.size(); i++) // ��� ���� (144)
	{
		int previousIndexOfBestTrain; // ��� �������� �������� ��������� ������ ����� ������� ����� �������� ����������� 
		int time = 0;
		for (auto it1 = routs[i].cbegin(), it2 = ++routs[i].cbegin(); it2 != routs[i].cend(); ++it1, ++it2) // ������������ ����� ���������
		{
			if (it1 == routs[i].begin())
			{
				previousIndexOfBestTrain = bestTimeTrain(*it1 - 1, *it2 - 1); // � 1 ������� �������� ����� � ���������� �������� �������
				time += obj.listData[*it1 - 1][*it2 - 1][previousIndexOfBestTrain]->getArrivalTime() - obj.listData[*it1 - 1][*it2 - 1][previousIndexOfBestTrain]->getDepartureTime();
				if (time <= 0)  // ����� �� ����� ����� �������� ����, ��� ����� ���������� ����� ��������� �� ������� ��������. ������ ����� �� ����� �������� ��� ����� ���� �����.
				{
					time += 24 * 3600;
				}
			}
			else
			{
				std::vector<int> allTimesBetweenStations; // ����� ����������� ����������� ����� ����. ������ ����� ��� ����� ����������� ����� ��������.
				for (auto& s : obj.listData[*it1 - 1][*it2 - 1])
				{
					int timeBetweenLastTrainAndNext = s->getDepartureTime() - obj.listData[*--it1 - 1][*--it2 - 1][previousIndexOfBestTrain]->getArrivalTime();
					if (s->getDepartureTime() - obj.listData[*it1 - 1][*it2 - 1][previousIndexOfBestTrain]->getArrivalTime() < 0) // ����� ��������� ��������� ����� ��������� ����, ��� ����� �������� � ������������ ������� �� �������� �����
					{
						timeBetweenLastTrainAndNext += 24 * 3600;
					}
					int travelTime = s->getArrivalTime() - s->getDepartureTime();
					if (s->getArrivalTime() - s->getDepartureTime() <= 0) // ��������� ��������� ����� ���� �������, ��� ��������, ��� ����� ��� � ���� �����
					{
						travelTime += 24 * 3600;
					}

					it1++; it2++; // ����� ����� �������� ����������� �������� �� ���������� �������� �� 1 ������� �����, ������� ���������� �� � ���������� �������
					allTimesBetweenStations.push_back(timeBetweenLastTrainAndNext + travelTime);
				}

				std::sort(allTimesBetweenStations.begin(), allTimesBetweenStations.end()); // �� �������� � ��������
				time += allTimesBetweenStations[0]; // ��������� �� ������� ���������� ���������
				previousIndexOfBestTrain = 0;
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
		std::cout << temp << std::endl;
		std::cout << time_path[i]->value << std::endl;
		std::cout << "----------------------------------------------------------" << std::endl;
	}
	std::cout << "The time in seconds" << std::endl;

	for (auto& i : time_path)
	{
		delete i;
	}
}

void Graph::outPutBestPrice(int countVariants)
{
	std::vector<WayAndInfo<double>*> bestVariants;
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
		std::cout << temp << std::endl;
		std::cout << bestVariants[i]->value << std::endl;
		std::cout << "----------------------------------------------------------" << std::endl;
	}

	for (auto& i : bestVariants)
	{
		delete i;
	}
}

void Graph::dfs(int const& nodeCur, int const& nodeLast) // ����� � �������
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
		std::set<int> rib = { nodeCur, val };
		if (ribs.find(rib) == ribs.end())
		{
			ribs.emplace(rib);
			dfs(val, nodeLast);
			ribs.erase(ribs.find(rib));
		}
	}
	path.pop_back();
}

size_t Graph::bestTimeTrain(int row, int col)
{
	std::vector<int> timeBetweenStations;
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