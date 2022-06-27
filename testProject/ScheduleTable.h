#ifndef SCHEDULETABLE
#define SCHEDULETABLE

#include <vector>
#include "Train.h"
#include <fstream>
#include <iostream>
#include <iomanip>

class ScheduleTable
{
private:
	std::vector<Train*> allTrains;

public: 
	ScheduleTable(const char* filepath);
	~ScheduleTable();
	friend std::ostream& operator<<(std::ostream& out, const ScheduleTable& st)
	{
		for (const auto& i : st.allTrains)
		{
			out << "����� ������: " << i->getNumberOfTrain() << "\t������� �����������: " << i->getDepartureStation() << 
				"\t������� ��������: " << i->getArrivalStation() << "\t���� ������: " << std::fixed << std::setprecision(2) << i->getCostOfTicket() <<
				"\t����� �����������: " << i->getDepartureTime() << "\t����� �������� : " << i->getArrivalTime() << std::endl;
		}
		return out;
	}
	std::vector<Train*> getInfoAboutTrains() const;
	Train* operator[](int index) const;

private:
	void removeSpacesFromString(std::string& str);
	void changeDotToComma(std::string& str);
};
#endif // !ScheduleTable


