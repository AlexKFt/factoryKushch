#ifndef PIPE_H
#define PIPE_H


struct Pipe
{
    float lengthInMetres;
    float diameterInMetres;
    bool isUnderRepair;

    bool wasDefined = false;
};


void InitializePipe(Pipe& pipe);

void defineLengthImMetresFor(Pipe& pipe);

void defineDiameterInMetresFor(Pipe& pipe);

void defineRepairConditionFor(Pipe& pipe);

void print(const Pipe& pipe);

void setRepairConditionTo(Pipe& pipe, bool status);

float positiveFloatInput();

void writeInFile(std::ofstream& fout, const Pipe& pipe);

void readFromFileIn(std::ifstream& fin, Pipe& pipe);

std::ostream& operator<<(std::ostream& out, const Pipe& pipe);


#endif