#include "Train.h"

//setters
void Train::setNumberOfTrain(string& str)
{
	numberOfTrain = str;
}

void Train::setDepartureStation(string& str)
{
	departureStation = str;
}

void Train::setArrivalStation(string& str)
{
	arrivalStation = str;
}

void Train::setDepartureTime(string& str)
{
	departureTime = str;
}

void Train::setArrivalTime(string& str)
{
	arrivalTime = str;
}

void Train::setCostOfTicket(string& str)
{
	// Конвертуємо рядок до типу double
	string::size_type sz;
	costOfTicket = stod(str, &sz);
}
//getters

string Train::getNumberOfTrain() const
{
	return numberOfTrain;
}

string Train::getDepartureStation() const
{
	return departureStation;
}

string Train::getArrivalStation() const
{
	return arrivalStation;
}

string Train::getDepartureTime() const
{
	return departureTime;
}

string Train::getArrivalTime() const
{
	return arrivalTime;
}

double Train::getCostOfTicket() const
{
	return costOfTicket;
}

