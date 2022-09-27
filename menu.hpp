#ifndef MENU_H
#define MENU_H

#include "CompressorStation.hpp"
#include "Pipe.hpp"


void showActions();

int inputForMenu();

void pickCommand(int commandIndex, CompressorStation& station, Pipe& pipe);

void addPipe(Pipe& pipe);

void addCompressorStation(CompressorStation& station);

void showObjectsList(const CompressorStation& station, const Pipe& pipe);

void editPipe(Pipe& pipe);

void editCompressorStation(CompressorStation& station);

void saveConfiguration(const CompressorStation& station, const Pipe& pipe);

void uploadChanges(CompressorStation& station, Pipe& pipe);

void askForStorage(const CompressorStation& station,const Pipe& pipe);



#endif