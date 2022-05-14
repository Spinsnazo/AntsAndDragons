#ifndef Creature_H
#define Creature_H

#define WIDTH 30
#define LENGTH 15

#include <stdlib.h>
#include <time.h>
#include <math.h>


class Creature         // An abstract class, "Ant" and "Dragon" inherit from it
{
public:
    virtual void Move() = 0;
    virtual void Eat(int) = 0;
    virtual void InformOthers(char[][WIDTH]) = 0;
    int GetNutritionLevel();
    int GetX();
    int GetY();
protected:
    int x, y;
    int nutrition_level;
};

#endif // Creature_H
