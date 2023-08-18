#include "CompressorStation.hpp"
#include "utils.hpp"


const int MAX_NUMBER_OF_WORKSHOPS = 10000;

int CompressorStation::maxStationId = 1;

CompressorStation::CompressorStation()
{
    CompressorStation::setStationName();
    CompressorStation::setWorkshopsNumber();
    CompressorStation::setActiveWorkshopsNumber();
    CompressorStation::setEfficiency();
    id = maxStationId++;
}


CompressorStation::CompressorStation(std::ifstream& in)
{
    getline(in, name);
    in >> id;
    in >> numberOfWorkshops;
    in >> numberOfActiveWorkshops;
    in >> perfomRateZeroToHundred;

    updateMaxId(maxStationId, id);
}


void CompressorStation::setStationName()
{
    std::cout << "Enter station name: ";
    std::cin>>std::ws;
    getline(std::cin, name);
}


void CompressorStation::setWorkshopsNumber() 
{
    std::cout << "Enter number of workshops: " << std::endl;
    numberOfWorkshops = getAppropriateNumberIn(Interval(1, MAX_NUMBER_OF_WORKSHOPS, true));
}


void CompressorStation::setActiveWorkshopsNumber()
{
    std::cout << "Enter number of active workshops: " << std::endl;
    numberOfActiveWorkshops = getAppropriateNumberIn(Interval(0, numberOfWorkshops, true));
}


void CompressorStation::setEfficiency()
{
    std::cout << "Enter station's rate: " << std::endl;
    perfomRateZeroToHundred = getAppropriateNumberIn(Interval(0, 100, true));
}


void CompressorStation::activateWorkshop()
{   
    if (freeWorkshopExist())
        numberOfActiveWorkshops++;
}


bool CompressorStation::freeWorkshopExist() const
{
    return numberOfWorkshops > numberOfActiveWorkshops;
}


void CompressorStation::stopWorkshop()
{
    if (activeWorkshopLeft())
        numberOfActiveWorkshops--;
}


bool CompressorStation::activeWorkshopLeft() const
{
    return numberOfActiveWorkshops > 0;
}

int CompressorStation::getNumberOfWorkshops() const
{
    return numberOfWorkshops;
}


double CompressorStation::getWorkload() const
{
    return ((double)numberOfActiveWorkshops / numberOfWorkshops);
}


void CompressorStation::edit(double stationWorkload)
{
    if(this->getWorkload() <= stationWorkload)
    {
        while(this->getWorkload() <= stationWorkload)
        {   
            this->activateWorkshop();
            if(this->getWorkload() == 100 && stationWorkload == 100)
                break;
        }
    }
    else
    {
        while(this->getWorkload() > stationWorkload) 
            this->stopWorkshop();
    
    }
}


int CompressorStation::getId() const
{
    return id;
}


std::ostream& operator<<(std::ostream& out, const CompressorStation& station)
{
    out << "Id: " << station.id << std::endl;
    out << "name: " << station.name << std::endl;
    out << "number of workshops: "<< station.numberOfWorkshops << std::endl;
    out << "number of active workshops: " << station.numberOfActiveWorkshops << std::endl;
    out << "station efficiency: " << station.perfomRateZeroToHundred << std::endl;

    return out;
}


std::ofstream& operator<<(std::ofstream& out, const CompressorStation& station)
{
    out << station.name << '\n' 
        << station.id << '\n'
        << station.numberOfWorkshops << '\n' 
        << station.numberOfActiveWorkshops << '\n' 
        << station.perfomRateZeroToHundred << '\n';

    return out;
}


