#include "ScheduleTable.h"

ScheduleTable::ScheduleTable(const char* filepath)
{
	string temp; // ��� ����� ���� ����������� ���������� ����� � ����. ��� ��������� ������ ����� ����� ������ �������� ���������� �� temp
	string scanner; // ������� ���� ������� ����� �� ;
	ifstream in(filepath);

	while (getline(in, temp))
	{
		removeSpacesFromString(temp); // ��������� spaces � �����
		changeDotToComma(temp); // �������� ������ �� ����, �� ��� ���� �� ����������� ������� (�������, �� ��������, ������ ����)
		temp += ";"; // ��������� (� ���� ������� ����� ���� ';', ���� �������� ����)
		Train* ptr = new Train();
		allTrains.push_back(ptr);

		int counter = 1;  // ��� ������������ ����� ��� ������� �����
		
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
