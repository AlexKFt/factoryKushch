#include "utilites.hpp"
#include <iostream>
#include <limits>

void clearInputBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void OpenFileForWriting(std::ofstream& fout)
{
    std::string fileName;

    while (!fout.is_open())
    {
        fileName = getFileName();
        fout.open(fileName, std::ios::out);
    }
}


void OpenFileForReading(std::ifstream& fin)
{
    std::string fileName;

    while (!fin.is_open())
    {
        fileName = getFileName();
        fin.open(fileName, std::ios::in);
    }
}


std::string getFileName()
{
    std::string fileName;

    std::cout << "Enter the name of file: ";
    std::cin >> fileName;
    clearInputBuffer();

    return fileName;
}

