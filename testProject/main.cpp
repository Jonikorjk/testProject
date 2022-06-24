#include <iostream>
#include "ScheduleTable.h"
#include "Train.h"
#include "Graph.h"
#include "AdjacencyList.h"

int main()
 {
	setlocale(LC_ALL, "ru");
	ScheduleTable st("test_task_data.csv");
	AdjacencyMatrix list(st);
	Graph graph;
	graph.fillGraph(list, BEST_PRICE);
	graph.printAdjacencyList();
}