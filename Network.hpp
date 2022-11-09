#ifndef NETWORK_H
#define NETWORK_h

#include <vector>
#include "utils.hpp"


extern const int MIN_ID_VALUE;
extern const int MAX_ID_VALUE;


struct Link
{
    int pipeID;
    std::unordered_set<int> stationsIDs;
};



class Network
{
private:
    std::vector<double> standartDiametrValues;
    std::vector<CompressorStation> networkNumeration;
    std::vector<Link> currentLinks;

    int choosePipe();

    std::unordered_set<int> chooseStations();

    void printIDs(const std::unordered_set<int>& indexes);


    void editAllElements(std::unordered_map<int, CompressorStation>& stations,
                     std::unordered_set<int>& selection);

    void editAllElements(std::unordered_map<int, Pipe>& pipes,
                     std::unordered_set<int>& selection);

    friend std::ostream& operator<<(std::ostream& out, const std::vector<double> values);

public:

    std::unordered_map<int, CompressorStation> stations;
    std::unordered_map<int, Pipe> pipes;

    void addLink();

    void showObjectsList();

    void addPipe(Pipe&& pipe);

    void addCompressorStation(CompressorStation&& station);

    void showOperationsWithStations();

    void showOperationsWithPipes();

    void uploadChanges();

    void saveConfiguration() const;


    template<typename T>
    void deleteAllElements(std::unordered_map<int, T>& container, const std::unordered_set<int>& selection)
    {
        for(int id: selection)
        {
            container.erase(id);
            std::cout << "[" << id << "] was deleted" << std::endl;
        }
    }

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
        printIDs(IDs);

        return IDs;
    }



    template<typename T>
    void deleteElementsIn(std::unordered_map<int, T>& container, std::unordered_set<int> selection)
    {
        int commandIndex;

        if(selection.size() == 1)
        {
            deleteAllElements(container, selection);
            return;
        }

        std::cout << "Enter 0 to delete all selected elements" << std::endl
                << "Enter 1 to delete some of these elements" << std::endl;

        commandIndex = getAppropriateNumberIn(Interval(0, 1, true));

        printIDs(selection);

        if (!commandIndex)
        {
            deleteAllElements(container, selection);
        }
        if (commandIndex)
        {
            printIDs(selection);
            std::unordered_set<int> indexIntersection = selectIDs(selection);
            deleteAllElements(container ,indexIntersection);
        }    

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
};


std::ostream& operator<<(std::ostream& out, const std::vector<double> values);




// сделать словарь смежности: в качестве ключей хранить станции, в качестве значений множество труб, приходящих в эти станции
// можно одновременно создать обратный словарь, где ключами являются трубы(словари можно вынести в отдельный класс с математическим описанием, содержимое которого не будет демонстрироваться
// пользователю, записываться в файл, быть доступным вне методов класса Network)
// при выводе собирать в множество существующие соединения (возможно имеет смысл создать класс троек), направление одностороннее
// тогда нстоит охранить количество труб между узлами, если при создании нового соединения обнаруживается тройка с теми же станциями
// топологическая сортировка в этом случае будет выполняться с помощью двух словарей, результаты будут записываться в вектор, в котором индекс будет соответствовать номеру станции - 1, а
// значение по индексу - конкретная станция, вектор должен быть полем network и быть доступным для взаимодействия (например выбор действия с двумя станциями: добавить или удалить трубу) 
// принцип - выбираем две станции, задаём определённый стандартный вариант ширины трубы и ищем среди труб с данным диаметром (написать фильтр по величине диаметра) __поправка__ в этом
// случае не стоит вводить счётчик труб между станциями
// класс должен предоставлять интерфейс: добавление определённой трубы между станциями - проверка на существования свободных цехов, станции должны быть разными, труба не должна быть использована
// удаление связи - проверка, что связь существует, добавлени трубы в свободные, то есть обновление всех словарей (потенциально излишняя сложность)
// топологическая сортировка - получает на вход начальную точку (либо)
// вывод в консоль (вид station1 --(diametr)--> station2) направление задаётся топологической сортировкой, запись в файл (запись троек)
// считывание из файла (должно быть на основе существующих функций)


#endif