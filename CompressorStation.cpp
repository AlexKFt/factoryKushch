#include <fstream>
#include <string>
#include <sstream>
#include "CompressorStation.hpp"
#include <limits>
#include <iostream>
#include "utilites.hpp"


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

    int input;
    for(;;)
    {
        if ((std::cin >> input).good() && (input > 0))  
        {
            station.numberOfWorkshops = input;
            clearInputBuffer();
            break;
        }
            
        else if (std::cin.fail())
        {
            clearInputBuffer();
            std::cout << "Error. There should be a number!\n";
        }else
        {
            std::cout << "Enter positive value\n";
        }  
    }
}


void fillActiveWorkshopsNumberFor(CompressorStation& station)
{
    std::cout << "Enter number of active workshops: ";

    int input;
    for(;;)
    {
        if ((std::cin >> input).good() && (input >= 0) && (input <= station.numberOfWorkshops))  
        {
            station.numberOfActiveWorkshops = input;
            clearInputBuffer();
            break;
        }       
        else if (std::cin.fail())
        {
            clearInputBuffer();
            std::cout << "Error. There should be a number!\n";
        }else if(input < 0)
        {
            std::cout << "Enter positive value\n";
        }
        else
        {
            std::cout << "Max number - " <<station.numberOfWorkshops << std::endl;
        }
    }    
}

void setEfficiencyTo(CompressorStation& station)
{
    std::cout << "Enter station's rate: ";

    int input;
    for(;;)
    {
        if ((std::cin >> input).good() && (input >= 0) && (input <= 100))  
        {
            station.perfomRateZeroToHundred = input;
            clearInputBuffer();
            break;
        }
        else if (std::cin.fail())
        {
            std::cin.clear();
            std::cout << "Ошибка ввода. Введите число!\n";
        }else
        {
            std::cout << " Введите значение из интервала от 0 до 100\n";
        } 
    }
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
        std::cout << "There is no object yet!\n";
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
        fout << station.name << '\n' 
             << station.numberOfWorkshops << ' ' 
             << station.numberOfActiveWorkshops << ' ' 
             << station.perfomRateZeroToHundred << '\n';
    }
}

void readFromFileIn(std::ifstream& fin, CompressorStation& station)
{
    std::string content;
    std::stringstream buffer;

    getline(fin, station.name);
    getline(fin, content); 

    buffer << content; 
    buffer >> station.numberOfWorkshops 
           >> station.numberOfActiveWorkshops 
           >> station.perfomRateZeroToHundred;

    station.wasDefined = true;
}
