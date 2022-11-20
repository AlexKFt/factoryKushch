#ifndef LINK_H
#define LINK_H

class Link
{
private:
    friend std::ifstream& operator>>(std::ifstream& in, Link& link);

    friend std::ostream& operator<<(std::ostream& out, const Link& link);

    friend std::ofstream& operator<<(std::ofstream& out, const Link& link);
public:
    int pipeID;
    int startStationId;
    int finishStationId;

    bool containsStation(int id);

};


#endif