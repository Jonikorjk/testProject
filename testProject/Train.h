#ifndef TRAIN
#define TRAIN

#include <string>

class Train
{
private:
	std::string numberOfTrain;
	std::string departureStation, arrivalStation;
	int departureTime, arrivalTime;
	double costOfTicket; 

public:
	void setNumberOfTrain(std::string& str);
	void setDepartureStation(std::string& str);
	void setArrivalStation(std::string& str);
	void setDepartureTime(std::string& str);
	void setArrivalTime(std::string& str);
	void setCostOfTicket(std::string& str);

	std::string getNumberOfTrain() const;
	std::string getDepartureStation() const;
	std::string getArrivalStation() const;
	int getDepartureTime() const;
	int getArrivalTime() const;
	double getCostOfTicket() const;
};


#endif // !TRAIN



