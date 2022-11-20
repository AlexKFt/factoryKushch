#ifndef NETWORK_H
#define NETWORK_h

#include <vector>
#include "utils.hpp"
#include "Graph.hpp"
#include "Link.hpp"


extern const int MIN_ID_VALUE;
extern const int MAX_ID_VALUE;


std::ostream& operator<<(std::ostream& out, const Link& l);

class Network
{
private:
    Graph graph;///!!!!!!!!!!!!
    std::vector<double> standartDiametrValues {500, 700, 1400};
    std::unordered_map<int, Link> Links;
    std::unordered_map<int, CompressorStation> stations;
    std::unordered_map<int, Pipe> pipes;

    template<typename T>
    std::unordered_set<int> selectIDs(T& container)
    {
        std::unordered_set<int> IDs;
        int element = -1;
        std::cout << "Enter indexes of elements, to exit enter 0" << std::endl;
        
        while(true)
        {
            element = getAppropriateNumberIn(Interval(MIN_ID_VALUE, MAX_ID_VALUE, true));
            
            if(!element)
                break;
            if(container.find(element) != container.end())
                IDs.insert(element);
            else
                std::cout << "There is no element with such id" << std::endl;
            
        }
        return IDs;
    }

    int choosePipe();

    int chooseStation();


    bool PipeHasLinks(int id);
    bool CSHasLinks(int id);

    int getCSNumberOfLinks(int id);

    bool IsPipeAvailable(int id);
    bool IsCSAvailable(int id);


    void editAllElements(std::unordered_map<int, CompressorStation>& stations,
                     std::unordered_set<int>& selection);

    void editAllElements(std::unordered_map<int, Pipe>& pipes,
                     std::unordered_set<int>& selection);

    friend std::ostream& operator<<(std::ostream& out, const std::vector<double> values);


    void deleteAllElements(std::unordered_map<int, Pipe>& container, const std::unordered_set<int>& selection);
    

    void deleteAllElements(std::unordered_map<int, CompressorStation>& container, const std::unordered_set<int>& selection);
 

    template<typename T>
    void deleteElementsIn(std::unordered_map<int, T>& container, std::unordered_set<int> selection)
    {
        int commandIndex;

        if(selection.size() == 1)
        {
            deleteAllElements(container, selection);
            return;
        }
        printIDs(selection);

        std::cout << "Enter 0 to delete all selected elements" << std::endl
                << "Enter 1 to delete some of these elements" << std::endl;

        commandIndex = getAppropriateNumberIn(Interval(0, 1, true));

        if (commandIndex==1)
            selection = selectIDs(selection);

        deleteAllElements(container, selection);
        
    }

    template<typename T>
    void chooseElemensForEditing(std::unordered_map<int, T>& container, std::unordered_set<int> selection)
    {
        int commandIndex;
   

        if(selection.size() == 1)
        { 
            editAllElements(container, selection);
            return;
        }

        std::cout << "Enter 0 to edit all selected elements" << std::endl
                << "Enter 1 to edit some of these elements" << std::endl;

        commandIndex = getAppropriateNumberIn(Interval(0, 1, true));

        printIDs(selection); 

        if (!commandIndex)
        {
            editAllElements(container, selection);
        }
        else
        {
            std::unordered_set<int> indexIntersection = selectIDs(selection);
            editAllElements(container, indexIntersection);
        }
    }   

    template<typename T>
    void chooseEditOrDelete(std::unordered_map<int, T>& container, std::unordered_set<int> indexes)
    {

        std::cout << "Enter 0 to start deleting " << std::endl
                << "Enter 1 to start editing" << std::endl;

        int commandIndex;

        commandIndex = getAppropriateNumberIn(Interval(0, 1, true));
        
        if (commandIndex == 0)
        {
            deleteElementsIn(container, indexes);
        }
        else if (commandIndex == 1)
        {
            chooseElemensForEditing(container, indexes);
        }
    }

public:

    void addLink();

    void deleteLink(int id = -1);

    void unmountStation(int id = -1);

    void showLinks();

    void showObjectsList();

    void showStationsList();
    
    void showPipesList();

    void addPipe(Pipe&& pipe);

    void addCompressorStation(CompressorStation&& station);

    void showOperationsWithStations();

    void showOperationsWithPipes();

    void loadConfiguration();

    void saveConfiguration() const;
};

std::ostream& operator<<(std::ostream& out, const std::vector<double> values);




#endif