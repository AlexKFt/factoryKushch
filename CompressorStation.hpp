#ifndef COMPRESSOR_STATION_H
#define COMPRESSOR_STATION_H
#include <string>

class CompressorStation
{
public:
    static int maxStationId;
private:
    int id;
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

    friend bool checkName(const CompressorStation& station, std::string name);

public:
    CompressorStation();

    CompressorStation(std::ifstream& in);

    double getWorkload() const;

    int getNumberOfWorkshops() const;

    void edit(double stationWorkload);

    void activateWorkshop();

    void stopWorkshop();

    int getId() const;

};





#endif