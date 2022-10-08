#ifndef PIPE_H
#define PIPE_H


class Pipe
{
private:
    double lengthInMetres;
    double diameter;
    bool isUnderRepair;

    void defineLengthImMetres();

    void defineDiameter();

    void defineRepairCondition();

    friend std::ostream& operator<<(std::ostream& out, const Pipe& pipe);

    friend std::ofstream& operator<<(std::ofstream& out, const Pipe& pipe);

public:
    Pipe();

    Pipe(std::ifstream& in);

    void setRepairCondition(bool status);
};


#endif