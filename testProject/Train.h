#ifndef TRAIN
#define TRAIN

#include <string>
using namespace std;

class Train
{
private:
	string numberOfTrain;
	string departureStation, arrivalStation;
	string departureTime, arrivalTime;
	double costOfTicket; 

public:
	void setNumberOfTrain(string str);
	void setDepartureStation(string str);
	void setArrivalStation(string str);
	void setDepartureTime(string str);
	void setArrivalTime(string str);
	void setCostOfTicket(string str);

	string getNumberOfTrain();
	string getDepartureStation();
	string getArrivalStation();
	string getDepartureTime();
	string getArrivalTime();
	double getCostOfTicket();
};


#endif // !TRAIN



