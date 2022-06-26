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
	string temp;
	str += ':';
	int k[3]{ 3600, 60, 1 };
	for (size_t i = 0, counter = 0; i < str.length(); i++)
	{
		if (str[i] == ':')
		{
			departureTime += stoi(temp) * k[counter];
			counter++;
			temp = "";
		}
		else temp += str[i];
	}
}

void Train::setArrivalTime(string& str)
{
	string temp;
	str += ':';
	int k[3]{ 3600, 60, 1 };
	for (size_t i = 0, counter = 0; i < str.length(); i++)
	{
		if (str[i] == ':')
		{
			arrivalTime += stoi(temp) * k[counter];
			counter++;
			temp = "";
		}
		else temp += str[i];
	}
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

int Train::getDepartureTime() const
{
	return departureTime;
}

int Train::getArrivalTime() const
{
	return arrivalTime;
}

double Train::getCostOfTicket() const
{
	return costOfTicket;
}

