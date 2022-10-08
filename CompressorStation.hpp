#ifndef COMPRESSOR_STATION_H
#define COMPRESSOR_STATION_H
#include <string>

class CompressorStation
{
private:
    std::string name;
    int numberOfWorkshops;
    int numberOfActiveWorkshops;
    int perfomRateZeroToHundred;

    void setStationName();

    void setWorkshopsNumber();

    void setActiveWorkshopsNumber();

    void setEfficiency();

    bool freeWorkshopExist() const;

    bool activeWorkshopLeft() const;

    friend std::ostream& operator<<(std::ostream& out, const CompressorStation& station);

    friend std::ofstream& operator<<(std::ofstream& out, const CompressorStation& station);

public:
    CompressorStation();

    CompressorStation(std::ifstream& in);

    void activateWorkshop();

    void stopWorkshop();

};





#endif