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
			out << "Номер поезда: " << i->getNumberOfTrain() << "\tСтанция отправления: " << i->getDepartureStation() << 
				"\tСтанция прибытия: " << i->getArrivalStation() << "\tЦена билета: " << std::fixed << std::setprecision(2) << i->getCostOfTicket() <<
				"\tВремя отправления: " << i->getDepartureTime() << "\tВремя прибытия : " << i->getArrivalTime() << std::endl;
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


