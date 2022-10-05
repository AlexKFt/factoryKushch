#ifndef COMPRESSOR_STATION_H
#define COMPRESSOR_STATION_H
#include <string>

struct CompressorStation
{
    std::string name;
    int numberOfWorkshops;
    int numberOfActiveWorkshops;
    int perfomRateZeroToHundred;

    bool wasDefined = false;
};

void InitializeCompressorStation(CompressorStation& station);

void fillStationNameFor(CompressorStation& station);

void fillWorkshopsNumberFor(CompressorStation& station);

void fillActiveWorkshopsNumberFor(CompressorStation& station);

void setEfficiencyTo(CompressorStation& station);

bool activeWorkshopLeftAt(CompressorStation& station);

bool freeWorkshopExistAt(CompressorStation& station);

void activateWorkshopAt(CompressorStation& station);

void StopWorkshopAt(CompressorStation& station);

void print(const CompressorStation& station);

void writeInFile(std::ofstream& fout,const CompressorStation& station);

void readFromFileIn(std::ifstream& fin, CompressorStation& station);

std::ostream& operator<<(std::ostream& out, const CompressorStation& station);

std::ifstream& operator>>(std::ifstream& in, CompressorStation& station);

std::ofstream& operator<<(std::ofstream& out, const CompressorStation& station);


#endif