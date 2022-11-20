#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <limits>
#include <unordered_map>
#include <unordered_set>
#include "CompressorStation.hpp"
#include "Pipe.hpp"


template<typename T>
class Interval
{
private:
    T lowerBound;
    T upperBound;
    bool bordersIncluded;

public:
    Interval(T _lowerBound, T _upperBound, bool _bordersIncluded)
        : lowerBound(_lowerBound), upperBound(_upperBound), bordersIncluded(_bordersIncluded)
    {}

    T getLowerBound() {return lowerBound;}

    T getUpperBound() {return upperBound;}

    bool bordersAreIncluded() {return bordersIncluded;}
};

void printIDs(const std::unordered_set<int>& indexes);

void clearInputBuffer();


bool fileIsReadyForWriting(std::ofstream& fout);


bool fileIsReadyForReading(std::ifstream& fin);


std::string getFileName();


template<typename T>
T getAppropriateNumberIn(Interval<T> interval)
{
    T input;

    for(;;)
    {
        std::cout << ">> ";
        
        if ((std::cin >> input).good() && inputBelongsInterval(input, interval))
        {
            clearInputBuffer();
            return input;
        }
        else if (std::cin.fail())
        {
            clearInputBuffer();
            std::cout << "Error. There should be a number!\n";
        }   
        else if (interval.bordersAreIncluded())
        {
            printClosedInterval(interval);
        }
        else
        {
            printOpenedInterval(interval);
        }
    }
}


template<typename T>
bool inputBelongsInterval(T input, Interval<T> interval)
{
    if (interval.bordersAreIncluded())
    {
        return (input >= interval.getLowerBound()) && (input <= interval.getUpperBound());
    }
    else if (!interval.bordersAreIncluded())
    {
        return (input > interval.getLowerBound()) && (input < interval.getUpperBound());
    }
    return false;
}   


template<typename T>

void printOpenedInterval(Interval<T> interval)
{
    std::cout << "Enter number in range between "
              << interval.getLowerBound() << " and " 
              << interval.getUpperBound() << std::endl;
} 


template<typename T>
void printClosedInterval(Interval<T> interval)
{
    std::cout << "Enter number in range from "
              << interval.getLowerBound() << " to " 
              << interval.getUpperBound() << std::endl;
} 


template<typename T>
using StationFilter = bool(*)(const CompressorStation& station, T parametr);


template<typename T>
std::unordered_set<int> findCompressorStationByFilter(const std::unordered_map<int, CompressorStation>& stations,
                                                      StationFilter<T> filter, 
                                                      T parametr)
{
    std::unordered_set<int> indexes;

    for (auto& [id, station]: stations)
    {
        if (filter(station, parametr))
            indexes.insert(id);
    }
    return indexes;
}


template<typename T>
using PipeFilter = bool(*)(const Pipe& pipe, T parametr);


template<typename T>
std::unordered_set<int> findPipeByFilter(const std::unordered_map<int, Pipe>& pipes, 
                                         PipeFilter<T> filter, T parametr)
{
    std::unordered_set<int> indexes;

    for(auto& [id, pipe]: pipes)
    {
        if (filter(pipe, parametr))
            indexes.insert(id);
    }
    return indexes;
}



bool checkName(const CompressorStation& station, std::string name);

bool checkName(const Pipe& pipe, std::string name);

bool checkPipeInRepair(const Pipe& pipe, bool status);

bool checkPipeDiameter(const Pipe& pipe, double diameter);

bool checkStationWorkload(const CompressorStation& station, double percent);

bool kmp(std::string sample, const std::string& line);

void updateMaxId(int& currentMaxId, int newElementId);

#endif 