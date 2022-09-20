#include <iostream>
#include <fstream>
#include <sstream>
#include "Pipe.hpp"
#include <limits>
#include "utilites.hpp"



void InitializePipe(Pipe& pipe)
{
    defineLengthImMetresFor(pipe);
    defineDiameterInMetresFor(pipe);
    defineRepairConditionFor(pipe);
    pipe.wasDefined = true;
}

void defineLengthImMetresFor(Pipe& pipe)
{
    std::cout << "Enter length of pipe in metres: ";
    pipe.lengthInMetres = positiveFloatInput();
}

void defineDiameterInMetresFor(Pipe& pipe)
{
    std::cout << "Enter diameter of pipe in metres: ";
    pipe.diameterInMetres = positiveFloatInput();
}

float positiveFloatInput()
{
    float input;
    for(;;)
    {
        if ((std::cin >> input).good() && (input > 0))  
        {
            clearInputBuffer();
            return input;
        }            
        else if (std::cin.fail())
        {
            clearInputBuffer();
            std::cout << "Error. There should be a number!\n";
        }
        else
        {
            std::cout << "Enter positive value\n";
        }
    }
}


void defineRepairConditionFor(Pipe& pipe)
{
    std::cout << "Is pipe undere repair? ";
    std::cin >> pipe.isUnderRepair;
    clearInputBuffer();
}

void print(const Pipe& pipe)
{
    if (!pipe.wasDefined)
    {
        std::cout << "There is no object yet!\n";
    }
    else
    {
        std::cout << pipe;
    }
}

std::ostream& operator<<(std::ostream& out, const Pipe& pipe)
{
    out << "Length of pipe: " << pipe.lengthInMetres << std::endl;
    out << "Diameter of pipe: " << pipe.diameterInMetres << std::endl;
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
        fout << pipe.lengthInMetres << ' ' 
             << pipe.diameterInMetres << ' ' 
             << pipe.isUnderRepair << '\n';
    }
    
}

void readFromFileIn(std::ifstream& fin, Pipe& pipe)
{
    std::string content;
    std::stringstream buffer;

    getline(fin, content);
    buffer << content;
    buffer >> pipe.lengthInMetres >> pipe.diameterInMetres >> pipe.isUnderRepair;
    pipe.wasDefined = true;
}