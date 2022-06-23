#include <iostream>
#include "ScheduleTable.h"
#include "Train.h"
#include "Graph.h"

int main()
{
	setlocale(LC_ALL, "ru");
	ScheduleTable st("test_task_data.csv");
	Graph a;
	a.fillGraph(st);
}