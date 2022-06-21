#include "Train.h"

//setters
void Train::setNumberOfTrain(string str)
{
	numberOfTrain = str;
}

void Train::setDepartureStation(string str)
{
	departureStation = str;
}

void Train::setArrivalStation(string str)
{
	arrivalStation = str;
}

void Train::setDepartureTime(string str)
{
	departureTime = str;
}

void Train::setArrivalTime(string str)
{
	arrivalTime = str;
}

void Train::setCostOfTicket(string str)
{
	// Конвертуємо рядок до типу double
	string::size_type sz;
	costOfTicket = stod(str, &sz);
}
//getters

string Train::getNumberOfTrain()
{
	return numberOfTrain;
}

string Train::getDepartureStation()
{
	return departureStation;
}

string Train::getArrivalStation()
{
	return arrivalStation;
}

string Train::getDepartureTime()
{
	return departureTime;
}

string Train::getArrivalTime()
{
	return arrivalTime;
}

double Train::getCostOfTicket()
{
	return costOfTicket;
}

