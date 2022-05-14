#ifndef Board_H
#define Board_H

#include "Message.h"
#include "Ant.h"
#include "Dragon.h"
#include <stdlib.h>
#include <time.h>
#include <utility>


class Board
{
public:
    Board();
    void Update();
    void Print();
    void ClearMap();
    void PrintLog();
    void AddFood();
    bool NoAnts();
    bool NoDragons();
    bool IsFinished();
private:
    char Map[LENGTH][WIDTH]; // LENGTH * WIDTH cells
    int numOfAnts;
    int numOfFood;
    int numOfDragons;
    std::vector<Ant>Ants;
    std::vector<Dragon>Dragons;
    std::vector<std::pair<int, int>> Food;

};

#endif // Board_H


