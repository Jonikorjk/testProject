#include "Graph.h"

Graph::Graph(AdjacencyMatrix& obj1) : obj(obj1)
{
}

void Graph::fillGraph(AdjacencyMatrix& list)
{
	// заполнение списка смежности
	adjMatrix = list.getAdjacencyMatrix();
	graph.resize(adjMatrix.size());
	for (int i = 0; i < adjMatrix.size(); ++i)
	{
		for (int j = 0; j < adjMatrix.size(); ++j)
		{
			if (adjMatrix[i][j]) graph[i].push_back(j + 1);
		}
	}

	// ¬севозможные пары из n дл€ обхода через dfs
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

void Graph::printAdjacencyList() // вывод списка смежности
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

void Graph::findAllWays() // функци€ котора€ перебирает всевозможные пути
{
	std::cout << "Please Wait..." << std::endl;
	for (const auto& i : allVariants)
	{
		dfs(i.first, i.second);
	}
}

void Graph::deleteExcessiveWays() // отбираем нужные пути (неповтор€ющиес€ станции, причЄм путь равен переездам между 6 станци€ми)
{
	std::vector<std::list<int>> temp; // сохран€ем нужные пути сюда
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

// дл€ реализации поиска наименьшого времени был использован жадный алгоритм. ќн не самый точный, однако банальный перебор займЄт уж слишком много пам€ти у компьютера, 
// поэтому придЄтс€ пожертвовать точностью
void Graph::outPutBestTime(int countVariants)
{
	std::vector<int> vectorOfTime;
	std::vector<WayAndInfo<int>*> time_path;
	for (size_t i = 0; i < routs.size(); i++) // все пути (144)
	{
		int previousIndexOfBestTrain; // дл€ подсчЄта ожидани€ следущего поезда нужно хранить врем€ прибыти€ предыдущего 
		int time = 0;
		for (auto it1 = routs[i].cbegin(), it2 = ++routs[i].cbegin(); it2 != routs[i].cend(); ++it1, ++it2) // передвижение между станци€ми
		{
			if (it1 == routs[i].begin())
			{
				previousIndexOfBestTrain = bestTimeTrain(*it1 - 1, *it2 - 1); // в 1 вершине отбираем поезд с наименьшим временем поездки
				time += obj.listData[*it1 - 1][*it2 - 1][previousIndexOfBestTrain]->getArrivalTime() - obj.listData[*it1 - 1][*it2 - 1][previousIndexOfBestTrain]->getDepartureTime();
				if (time <= 0)  // здесь не может врем€ равн€тс€ нулю, ибо тогда фактически поезд приезжает не начина€ движени€. ¬место этого мы будем говорить что поезд ехал сутки.
				{
					time += 24 * 3600;
				}
			}
			else
			{
				std::vector<int> allTimesBetweenStations; // здесь сохран€ютс€ последующие врем€ пути. “олько здесь уже будет учитыватьс€ врем€ ожидани€.
				for (auto& s : obj.listData[*it1 - 1][*it2 - 1])
				{
					int timeBetweenLastTrainAndNext = s->getDepartureTime() - obj.listData[*--it1 - 1][*--it2 - 1][previousIndexOfBestTrain]->getArrivalTime();
					if (s->getDepartureTime() - obj.listData[*it1 - 1][*it2 - 1][previousIndexOfBestTrain]->getArrivalTime() < 0) // здесь результат вычитани€ может равн€тьс€ нулю, что будет говорить о моментальной посадке на следущий поезд
					{
						timeBetweenLastTrainAndNext += 24 * 3600;
					}
					int travelTime = s->getArrivalTime() - s->getDepartureTime();
					if (s->getArrivalTime() - s->getDepartureTime() <= 0) // результат вычитани€ может быть нулевым, что означает, что поезд был в пути сутки
					{
						travelTime += 24 * 3600;
					}

					it1++; it2++; // чтобы вз€ть значение предыдущего элемента мы откатывали итератор на 1 позицию назад, поэтому возвращаем их в нормальную позицию
					allTimesBetweenStations.push_back(timeBetweenLastTrainAndNext + travelTime);
				}

				std::sort(allTimesBetweenStations.begin(), allTimesBetweenStations.end()); // от меньшего к большему
				time += allTimesBetweenStations[0]; // добавл€ем ко времени наименьший результат
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

void Graph::dfs(int const& nodeCur, int const& nodeLast) // поиск в глубину
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