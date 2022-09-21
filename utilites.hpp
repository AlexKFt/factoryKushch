#include <fstream>


void clearInputBuffer();


bool fileIsReadyForWriting(std::ofstream& fout);

bool fileIsReadyForReading(std::ifstream& fin);

std::string getFileName();