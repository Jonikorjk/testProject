#ifndef TRAIN
#define TRAIN

#include <string>
using namespace std;

class Train
{
private:
	string numberOfTrain;
	string departureStation, arrivalStation;
	int departureTime, arrivalTime;
	double costOfTicket; 

public:
	void setNumberOfTrain(string& str);
	void setDepartureStation(string& str);
	void setArrivalStation(string& str);
	void setDepartureTime(string& str);
	void setArrivalTime(string& str);
	void setCostOfTicket(string& str);

	string getNumberOfTrain() const;
	string getDepartureStation() const;
	string getArrivalStation() const;
	int getDepartureTime() const;
	int getArrivalTime() const;
	double getCostOfTicket() const;
};


#endif // !TRAIN



