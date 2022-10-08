#include <iostream>
#include <fstream>
#include <limits>


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
