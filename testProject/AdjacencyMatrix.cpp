#include "AdjacencyMatrix.h"

AdjacencyMatrix::AdjacencyMatrix(const ScheduleTable& st)
{
	setStations(st); // ��������� ��� ������� � �������
	setSizeOfAdjMatrix(); // ������������� ������ ������� ���������

	for (size_t i = 0; i < listData.size(); i++) // listData[i][j] - ���-�� ����� ��������� i � j. k - ������, ������� ����� ����� �������
	{
		for (size_t j = 0; j < listData[i].size(); j++)
		{
			for (const auto& k : st.getInfoAboutTrains())
			{
				if (stations[i] == k->getDepartureStation() && stations[j] == k->getArrivalStation())
				{
					listData[i][j].push_back(k);
				}
			}
		}
	}
}

std::vector<std::vector<double>> AdjacencyMatrix::getAdjacencyMatrix() // ��������� ���������� ������� ���������� - ������ �� ����
{
	std::vector<std::vector<double>> adjMatrix;
	adjMatrix.resize(stations.size());
	for (size_t i = 0; i < adjMatrix.size(); i++)
	{
		adjMatrix[i].resize(stations.size());
	}

	for (size_t i = 0; i < adjMatrix.size(); i++)
	{
		for (size_t j = 0; j < adjMatrix[i].size(); j++)
		{
			adjMatrix[i][j] = getBestPrice(i, j);
		}
	}
	return adjMatrix;
}

double AdjacencyMatrix::getBestPrice(int row, int col) // ������� ��� ���������� ������ ���� ������
{
	if (listData[row][col].size() == 0) return 0;
	Train* ticketWithBestPrice = listData[row][col][0];
	for (size_t i = 1; i < listData[row][col].size(); i++)
	{
		if (ticketWithBestPrice->getCostOfTicket() > listData[row][col][i]->getCostOfTicket())
		{
			ticketWithBestPrice = listData[row][col][i];
		}
	}
	return ticketWithBestPrice->getCostOfTicket();
}

void AdjacencyMatrix::setSizeOfAdjMatrix() // ������������� ����������� ������� ���������
{
	listData.resize(stations.size());
	for (size_t i = 0; i < listData.size(); i++)
	{
		listData[i].resize(stations.size());
	}
}

void AdjacencyMatrix::setStations(const ScheduleTable& st) // ��������� ���������� �������. ��� ����������
{
	std::string departureTimeEachTrain;
	for (size_t i = 0; i < st.getInfoAboutTrains().size(); i++)
	{
		departureTimeEachTrain = st[i]->getDepartureStation();
		if (notEqual(departureTimeEachTrain))
		{
			stations.push_back(departureTimeEachTrain);
		}
	}
}

bool AdjacencyMatrix::notEqual(std::string a) // ������� ������� ������� �� ���������� �������
{
	for (size_t i = 0; i < stations.size(); i++)
	{
		if (stations[i] == a) return false;
	}
	return true;
}