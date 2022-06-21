#include <iostream>
#include "ScheduleTable.h"
#include "Train.h"

int main()
{
	setlocale(LC_ALL, "ru");
	ScheduleTable st("test_task_data.csv");
	cout << st << endl;
}