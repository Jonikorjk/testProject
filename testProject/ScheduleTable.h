#ifndef SCHEDULETABLE
#define SCHEDULETABLE

#include <fstream>
#include <vector>
#include "Train.h"
#include <iomanip>

class ScheduleTable
{
private:
	vector<Train*> allTrains;

public: 
	ScheduleTable(const char* filepath);
	friend ostream& operator<<(ostream& out, ScheduleTable st)
	{
		for (auto& i : st.allTrains)
		{
			out << "����� ������: " << i->getNumberOfTrain() << "\t������� �����������: " << i->getDepartureStation() << 
				"\t������� ��������: " << i->getArrivalStation() << "\t���� ������: " << std::fixed << std::setprecision(2) << i->getCostOfTicket() <<
				"\t����� �����������: " << i->getDepartureTime() << "\t����� �������� : " << i->getArrivalTime() << endl;
		}
		return out;
	}
private:
	void removeSpacesFromString(string& str);
	void changeDotToComma(string& str);
};



#endif // !ScheduleTable


