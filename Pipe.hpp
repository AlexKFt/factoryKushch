#ifndef PIPE_H
#define PIPE_H

#include <string>

class Pipe
{
private:
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

public:
    Pipe();

    Pipe(std::ifstream& in);

    void edit(bool status);
    
};


#endif