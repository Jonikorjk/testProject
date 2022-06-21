#include "ScheduleTable.h"

ScheduleTable::ScheduleTable(const char* filepath)
{
	string temp; // цей рядок буде збережувати інформацію рядка у файлі. При зчитуванні нового рядка файла будемо додавати інформацію до temp
	string scanner; // збережує лише проміжок рядку до ;
	ifstream in(filepath);

	while (getline(in, temp))
	{
		removeSpacesFromString(temp); // Видаляємо spaces в рядку
		changeDotToComma(temp); // замінюємо крапку на кому, бо без коми не враховується залишок (функція, що конвертує, відкидує його)
		temp += ";"; // Разделить (в кінці кожного рядка немає ';', тому добавимо його)
		Train* ptr = new Train();
		allTrains.push_back(ptr);

		int counter = 1;  // Для встановлення даних про маршрут поїзда
		
		for (const auto& i : temp)
		{
			if (i == ';')
			{
				switch (counter)
				{
				case 1:
					ptr->setNumberOfTrain(scanner);
					break;
				case 2:
					ptr->setDepartureStation(scanner);
					break;
				case 3:
					ptr->setArrivalStation(scanner);
					break;
				case 4:
					ptr->setCostOfTicket(scanner);
					break;
				case 5:
					ptr->setDepartureTime(scanner);
					break;
				case 6:
					ptr->setArrivalTime(scanner);
					break;
				}
				counter++;
				scanner.clear();
			}
			else scanner.push_back(i);

		}
	}
}

void ScheduleTable::removeSpacesFromString(string& str)
{
	int length = str.length();
	for (int i = 0; i < length; i++) 
	{
		if (str[i] == ' ') str.erase(i, 1);
	}
}

void ScheduleTable::changeDotToComma(string& str)
{
	int length = str.length();
	for (int i = 0; i < length; i++)
	{
		if (str[i] == '.') str[i] = ',';
	}
}
