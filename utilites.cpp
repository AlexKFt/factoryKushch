#include "utilites.hpp"
#include <iostream>
#include <limits>

void clearInputBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool fileIsReadyForWriting(std::ofstream& fout)
{
    std::string fileName;

    if (!fout.is_open())
    {
        fileName = getFileName();
        fout.open(fileName, std::ios::out);
    }
    return fout.is_open();
}


bool fileIsReadyForReading(std::ifstream& fin)
{
    std::string fileName;

    if (!fin.is_open())
    {
        fileName = getFileName();
        fin.open(fileName, std::ios::in);
    }
    return fin.is_open();
}


std::string getFileName()
{
    std::string fileName;

    std::cout << "Enter the name of file: ";
    getline(std::cin, fileName);

    return fileName;
}

