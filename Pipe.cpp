#include <iostream>
#include <fstream>
#include <sstream>
#include "Pipe.hpp"
#include <limits>
#include "utils.hpp"
#include "const.hpp"


Pipe::Pipe()
{
    defineLengthImMetres();
    defineDiameter();
    defineRepairCondition();
}


Pipe::Pipe(std::ifstream& in)
{
    in >> lengthInMetres;
    in >> diameter;
    in >> isUnderRepair;
}


void Pipe::defineLengthImMetres()
{
    std::cout << "Enter length of pipe in metres: ";
    lengthInMetres = getAppropriateNumberIn(Interval(0.0, MAX_PIPE_LENGTH, false));
}


void Pipe::defineDiameter()
{
    std::cout << "Enter diameter of pipe in millimetres: ";
    diameter = getAppropriateNumberIn(Interval(0.0, MAX_PIPE_DIAMETER, false));
}


void Pipe::defineRepairCondition()
{
    std::cout << "Is pipe undere repair?\n Enter 0 if no\n Enter 1 if yes\n ";
    std::cin >> isUnderRepair;
    clearInputBuffer();
}


std::ostream& operator<<(std::ostream& out, const Pipe& pipe)
{
    out << "Length of pipe: " << pipe.lengthInMetres << std::endl;
    out << "Diameter of pipe: " << pipe.diameter << std::endl;
    out << "Is under repair: " << std::boolalpha << pipe.isUnderRepair << std::endl;

    return out;
}


void Pipe::setRepairCondition(bool status)
{
    isUnderRepair = status;
}


std::ofstream& operator<<(std::ofstream& out, const Pipe& pipe)
{
    out  << pipe.lengthInMetres << '\n' 
         << pipe.diameter << '\n' 
         << pipe.isUnderRepair << '\n';

    return out;
}

