#include <fstream>
#include "const.hpp"
#include "CompressorStation.hpp"
#include <limits>
#include <iostream>
#include "utils.hpp"


void InitializeCompressorStation(CompressorStation& station)
{
    fillStationNameFor(station);
    fillWorkshopsNumberFor(station);
    fillActiveWorkshopsNumberFor(station);
    setEfficiencyTo(station);
    station.wasDefined = true;
}

void fillStationNameFor(CompressorStation& station)
{
    std::cout << "Enter station name: ";
    getline(std::cin, station.name);
}

void fillWorkshopsNumberFor(CompressorStation& station) 
{
    std::cout << "Enter number of workshops: ";
    station.numberOfWorkshops = getAppropriateNumberInLimits(Interval(1, MAX_NUMBER_OF_WORKSHOPS, true));
}


void fillActiveWorkshopsNumberFor(CompressorStation& station)
{
    std::cout << "Enter number of active workshops: ";
    station.numberOfActiveWorkshops = getAppropriateNumberInLimits(Interval(0, station.numberOfWorkshops, true));
}

void setEfficiencyTo(CompressorStation& station)
{
    std::cout << "Enter station's rate: ";
    station.perfomRateZeroToHundred = getAppropriateNumberInLimits(Interval(0, 100, true));
}


void activateWorkshopAt(CompressorStation& station)
{   
    if (freeWorkshopExistAt(station))
        station.numberOfActiveWorkshops++;
}

bool freeWorkshopExistAt(CompressorStation& station)
{
    return station.numberOfWorkshops > station.numberOfActiveWorkshops;
}

void StopWorkshopAt(CompressorStation& station)
{
    if (activeWorkshopLeftAt(station))
        station.numberOfActiveWorkshops--;
}

bool activeWorkshopLeftAt(CompressorStation& station)
{
    return station.numberOfActiveWorkshops > 0;
}


void print(const CompressorStation& station)
{
    if (!station.wasDefined)
    {
        std::cout << "There is no station yet!\n";
    }
    else
        std::cout << station;
}

std::ostream& operator<<(std::ostream& out, const CompressorStation& station)
{
    out << "name: " << station.name << std::endl;
    out << "number of workshops: "<< station.numberOfWorkshops << std::endl;
    out << "number of active workshops: " << station.numberOfActiveWorkshops << std::endl;
    out << "station efficiency: " << station.perfomRateZeroToHundred << std::endl;

    return out;
}

void writeInFile(std::ofstream& fout, const CompressorStation& station)
{   
    if (!station.wasDefined)
    {
        std::cout << "The station should be initialized! \n";
    }
    else
    {
        fout << station;
    }
}

std::ofstream& operator<<(std::ofstream& out, const CompressorStation& station)
{
    out << station.name << '\n' 
        << station.numberOfWorkshops << '\n' 
        << station.numberOfActiveWorkshops << '\n' 
        << station.perfomRateZeroToHundred << '\n';

    return out;
}

void readFromFileIn(std::ifstream& fin, CompressorStation& station)
{
    fin >> station;
    station.wasDefined = true;
}

std::ifstream& operator>>(std::ifstream& in, CompressorStation& station)
{
    getline(in, station.name);
    
    in >> station.numberOfWorkshops;
    in >> station.numberOfActiveWorkshops;
    in >> station.perfomRateZeroToHundred;

    return in;
}