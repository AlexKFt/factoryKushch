#include <iostream>
#include <fstream>
#include <sstream>
#include "Pipe.hpp"
#include <limits>
#include "utils.hpp"
#include "const.hpp"


void InitializePipe(Pipe& pipe)
{
    defineLengthImMetresFor(pipe);
    defineDiameterFor(pipe);
    defineRepairConditionFor(pipe);
    pipe.wasDefined = true;
}

void defineLengthImMetresFor(Pipe& pipe)
{
    std::cout << "Enter length of pipe in metres: ";
    pipe.lengthInMetres = getAppropriateNumberInLimits(Interval(0.0, MAX_PIPE_LENGTH, false));
}

void defineDiameterFor(Pipe& pipe)
{
    std::cout << "Enter diameter of pipe in millimetres: ";
    pipe.diameter = getAppropriateNumberInLimits(Interval(0.0, MAX_PIPE_DIAMETER, false));
}


void defineRepairConditionFor(Pipe& pipe)
{
    std::cout << "Is pipe undere repair?\n Enter 0 if no\n Enter 1 if yes\n ";
    std::cin >> pipe.isUnderRepair;
    clearInputBuffer();
}

void print(const Pipe& pipe)
{
    if (!pipe.wasDefined)
    {
        std::cout << "There is no pipe yet!\n";
    }
    else
    {
        std::cout << pipe;
    }
}

std::ostream& operator<<(std::ostream& out, const Pipe& pipe)
{
    out << "Length of pipe: " << pipe.lengthInMetres << std::endl;
    out << "Diameter of pipe: " << pipe.diameter << std::endl;
    out << "Is under repair: " << std::boolalpha << pipe.isUnderRepair << std::endl;

    return out;
}

void setRepairConditionTo(Pipe& pipe, bool status)
{
    pipe.isUnderRepair = status;
}

void writeInFile(std::ofstream& fout, const Pipe& pipe)
{   
    if (!pipe.wasDefined)
    {
        std::cout << "Pipe should be initialized!\n";
    }
    else
    {
        fout << pipe;
    }
    
}

std::ofstream& operator<<(std::ofstream& out, const Pipe& pipe)
{
    out  << pipe.lengthInMetres << '\n' 
         << pipe.diameter << '\n' 
         << pipe.isUnderRepair << '\n';

    return out;
}

void readFromFileIn(std::ifstream& fin, Pipe& pipe)
{
    fin >> pipe;
    pipe.wasDefined = true;
}

std::ifstream& operator>>(std::ifstream& in, Pipe& pipe)
{
    in >> pipe.lengthInMetres;
    in >> pipe.diameter;
    in >> pipe.isUnderRepair;

    return in;
}