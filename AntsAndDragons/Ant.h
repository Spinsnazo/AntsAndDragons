#ifndef Ant_H
#define Ant_H

#include "Message.h"
#include "Creature.h"
#include <algorithm>
#include <vector>

class Ant : public Creature
{
public:
    Ant(int, int);
    void Move();
    void Eat(int);
    void InformOthers(char[][WIDTH]);
    static void PrintNotifications(int n);   // n - how many last messages should be printed
private:
    static std::vector<Message> Notifications;
};

#endif // Ant_H
