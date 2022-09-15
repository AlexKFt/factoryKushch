#ifndef PIPE_H
#define PIPE_H


struct Pipe
{
    float lengthInMetres;
    float diameterInMetres;
    bool isUnderRepair;
};

void createPipe(Pipe& pipe);

void defineLengthImMetresFor(Pipe& pipe);

void defineDiameterInMetresFor(Pipe& pipe);

void defineRepairConditionFor(Pipe& pipe);

void print(Pipe& pipe);

void setRepairConditionTo(Pipe& pipe, bool status);

float positiveFloatInput();

void writeInFile(Pipe& pipe);

void readFromFileIn(Pipe& pipe);


#endif