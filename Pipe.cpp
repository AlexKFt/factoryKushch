#include <sstream>
#include "Pipe.hpp"
#include "utils.hpp"



const double MAX_PIPE_LENGTH = 100000;
const double MAX_PIPE_DIAMETER = 1500.0;

int Pipe::maxPipeId = 1;

Pipe::Pipe()
{
    setPipeName();
    defineLengthImMetres();
    defineDiameter();
    defineRepairCondition();
    id = maxPipeId++;
}

Pipe::Pipe(std::ifstream& in)
{
    getline(in>>std::ws, name);
    in >> id;
    in >> lengthInMetres;
    in >> diameter;
    in >> isUnderRepair;

    updateMaxId(maxPipeId, id);
}

void Pipe::setPipeName()
{
    std::cout << "Enter pipe name: ";
    std::cin >> std::ws;
    getline(std::cin, name);
}


void Pipe::defineLengthImMetres() 
{
    std::cout << "Enter length of pipe in metres: " << std::endl;
    lengthInMetres = getAppropriateNumberIn(Interval(0.0, MAX_PIPE_LENGTH, false));
}


void Pipe::defineDiameter()
{
    std::cout << "Enter diameter of pipe in millimetres: " << std::endl;
    diameter = getAppropriateNumberIn(Interval(0.0, MAX_PIPE_DIAMETER, false));
}


void Pipe::defineRepairCondition()
{
    std::cout << "Is pipe undere repair?\n Enter 0 if no\n Enter 1 if yes" << std::endl;
    std::cin >> isUnderRepair;
    clearInputBuffer();
}


void Pipe::edit(bool status)
{
    this->setRepairCondition(status);
}


int Pipe::getId() const
{
    return id;
}


void Pipe::setRepairCondition(bool status)
{
    isUnderRepair = status;
}

std::ostream& operator<<(std::ostream& out, const Pipe& pipe)
{
    out << "Id: " << pipe.id << std::endl;
    out << "Pipe name: " << pipe.name << std::endl;
    out << "Length of pipe: " << pipe.lengthInMetres << std::endl;
    out << "Diameter of pipe: " << pipe.diameter << std::endl;
    out << "Is under repair: " << std::boolalpha << pipe.isUnderRepair << std::endl;

    return out;
}


std::ofstream& operator<<(std::ofstream& out, const Pipe& pipe)
{
    out << pipe.name << '\n'
        << pipe.id << '\n'
        << pipe.lengthInMetres << '\n' 
        << pipe.diameter << '\n' 
        << pipe.isUnderRepair << '\n';

    return out;
}


