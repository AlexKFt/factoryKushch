#include "utils.hpp"
#include "vector"

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


bool checkName(const CompressorStation& station, std::string name)
{
    return kmp(name, station.name);
}

bool checkStationWorkload(const CompressorStation& station, double percent)
{
    return station.getWorkload() <= percent;
}

bool checkPipeInRepair(const Pipe& pipe, bool status)
{
    return (pipe.isUnderRepair == status);
}

bool checkName(const Pipe& pipe, std::string name)
{
    return kmp(name, pipe.name);
}

std::vector<int> prefix_function_kmp(std::string& summary)
{
    int n = summary.length();
    std::vector<int> pi(n, 0);
    for (int i = 1; i < n; ++i) 
    {
        int k = pi[i-1];
        while (k > 0 and summary[i] != summary[k]) 
        {
            k = pi[k-1];
        }
        if (summary[i] == summary[k])
            k += 1;
        pi[i] = k;
    }
    return pi;
}

bool kmp(std::string sample, const std::string& line)
{
    std::string summary = sample + '#' + line;
    std::vector<int> pi = prefix_function_kmp(summary);
    
    for (auto x: pi) {
        if (x == sample.size())
            return true;
    }
    return false;
}