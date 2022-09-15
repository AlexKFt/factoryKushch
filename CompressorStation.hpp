#ifndef COMPRESSOR_STATION_H
#define COMPRESSOR_STATION_H
#include <string>

struct CompressorStation
{
    std::string name;
    int numberOfWorkshops;
    int numberOfActiveWorkshops;
    int perfomRateZeroToHundred;
};

void createCompressorStation(CompressorStation& station);

void fillStationNameFor(CompressorStation& station);

void fillWorkshopsNumberFor(CompressorStation& station);

void fillActiveWorkshopsNumberFor(CompressorStation& station);

void setEfficiencyTo(CompressorStation& station);

bool activeWorkshopLeftAt(CompressorStation& station);

bool freeWorkshopExistAt(CompressorStation& station);

void activateWorkshopAt(CompressorStation& station);

void StopWorkshopAt(CompressorStation& station);

void print(CompressorStation& station);

void writeInFile(CompressorStation& station);

void readFromFileIn(CompressorStation& station);


#endif