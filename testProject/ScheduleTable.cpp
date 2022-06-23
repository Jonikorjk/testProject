#include "ScheduleTable.h"

ScheduleTable::ScheduleTable(const char* filepath) // � ����������� ������ ���� �� ����� �� �������� ��� �� ������ ���������� �� ��� Train
{
	string line; // ��� ����� ���� ����������� ���������� ����� � ����. ��� ��������� ������ ����� ����� ������ �������� ���������� �� temp
	string scanner; // ������� ���� ������� ����� �� ������� ";"
	ifstream in(filepath);

	while (getline(in, line))
	{
		removeSpacesFromString(line); // ��������� spaces � �����
		changeDotToComma(line); // �������� ������ �� ����, �� ��� ���� �� ����������� ������� (�������, �� ��������, ������ ����)
		line += ";"; // (� ���� ������� ����� ���� ';', ���� �������� ����)
		Train* ptr = new Train();
		allTrains.push_back(ptr);

		int counter = 1;  // ��� ������������ ����� ��� ������� �����
		
		for (const auto& i : line)
		{
			if (i == ';') // ����������� ������ ����� �� scanner, ���� ��������� ";" ����������� �� ��� �� ������ � ������ �� ������� scanner
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
