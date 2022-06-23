#include "ScheduleTable.h"

ScheduleTable::ScheduleTable(const char* filepath) // У конструкторі беремо шлях до файлу та записуємо дані до масиву вказивників на тип Train
{
	string line; // цей рядок буде збережувати інформацію рядка у файлі. При зчитуванні нового рядка файла будемо додавати інформацію до temp
	string scanner; // збережує лише проміжок рядку до символу ";"
	ifstream in(filepath);

	while (getline(in, line))
	{
		removeSpacesFromString(line); // Видаляємо spaces в рядку
		changeDotToComma(line); // замінюємо крапку на кому, бо без коми не враховується залишок (функція, що конвертує, відкидує його)
		line += ";"; // (в кінці кожного рядка немає ';', тому добавимо його)
		Train* ptr = new Train();
		allTrains.push_back(ptr);

		int counter = 1;  // Для встановлення даних про маршрут поїзда
		
		for (const auto& i : line)
		{
			if (i == ';') // посимвольно додаємо букви до scanner, коли зустрічаємо ";" відправляємо ці дані до одного з пунктів та очищуємо scanner
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
			else scanner += i;
		}
	}
}

ScheduleTable::~ScheduleTable()
{
	for (auto& i : allTrains)
	{
		delete i;
		i = nullptr;
	}
}

vector<Train*> ScheduleTable::getInfoAboutTrains() const
{
	return allTrains;
}

Train* ScheduleTable::operator[](int index) const
{
	return allTrains[index];
}

void ScheduleTable::removeSpacesFromString(string& str)
{
	size_t length = str.length();
	for (int i = 0; i < length; i++) 
	{
		if (str[i] == ' ') str.erase(i, 1);
	}
}

void ScheduleTable::changeDotToComma(string& str)
{
	size_t length = str.length();
	for (int i = 0; i < length; i++)
	{
		if (str[i] == '.') str[i] = ',';
	}
}
