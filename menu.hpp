#ifndef MENU_H
#define MENU_H

#include "Network.hpp"
#include "utils.hpp"


void showActions();


int inputForMenu();


void pickCommand(int commandIndex, Network& net);


void askForStorage(Network& net);



#endif