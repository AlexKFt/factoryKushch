#ifndef Pipe_H
#define Pipe_H

#include <string>

class Pipe
{   
public:
    static int maxPipeId;
private:
    int id;
    std::string name;
    double lengthInMetres;
    double diameter;
    bool isUnderRepair;

    void setPipeName();

    void setRepairCondition(bool status);

    void defineLengthImMetres();

    void defineDiameter();

    void defineRepairCondition();

    friend std::ostream& operator<<(std::ostream& out, const Pipe& pipe);

    friend std::ofstream& operator<<(std::ofstream& out, const Pipe& pipe);

    friend bool checkPipeInRepair(const Pipe& pipe, bool status);

    friend bool checkName(const Pipe& pipe, std::string name);

    friend bool checkPipeDiameter(const Pipe& pipe, double diameter);

public:
    Pipe();

    Pipe(std::ifstream& in);

    void edit(bool status);

    int getId() const;

    double getLength() const;

    double getCapacity() const;

};


#endif