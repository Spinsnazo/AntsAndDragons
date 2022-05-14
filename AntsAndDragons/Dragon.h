#ifndef Dragon_H
#define Dragon_H

#include <vector>
#include "Creature.h"
#include "Message.h"


class Dragon : public Creature
{
public:
    Dragon(int, int);
    void Move();
    void Eat(int);
    void InformOthers(char[][WIDTH]);
    static void PrintNotifications(int n);
private:
    static std::vector<Message> Notifications;
};

#endif // Dragon_H
