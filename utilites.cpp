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
        std::cout << "Enter the name of file: ";
        std::cin >> fileName;
        clearInputBuffer();
        fout.open(fileName, std::ios::app); // !!! FIX ME - I should know is this file new one 
                                            // or there is some data inside 
    }
}

void OpenFileForReading(std::ifstream& fin)
{
    std::string fileName;

    while (!fin.is_open())
    {
        std::cout << "Enter the name of file: ";
        std::cin >> fileName;
        clearInputBuffer();
        fin.open(fileName, std::ios::app); /// !!! FIX ME - append is not appropriate method for reading the file
    }
}

