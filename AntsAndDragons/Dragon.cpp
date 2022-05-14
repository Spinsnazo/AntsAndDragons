#include "Dragon.h"

std::vector<Message> Dragon::Notifications = {};

Dragon::Dragon(int a, int b)
{
    x = a;
    y = b;
    nutrition_level = 15;
    Notifications.push_back(Message(x, y, "Here I am"));
}

void Dragon::Move()
{
    --nutrition_level;

    std::vector<std::pair<std::pair<int, int>, double>>follow;

    int dx = 0, dy = 0;
    double distance = 0;
    std::pair<std::pair<int, int>, double>closest_ant;

    for (unsigned int i = 0; i < Notifications.size(); i++)
    {
        if (Notifications[i].GetMsg() == "I see an ant!")
        {
            dx = x - Notifications[i].GetX();
            dy = y - Notifications[i].GetY();
            distance = sqrt(dx * dx + dy * dy);
            follow.push_back(std::make_pair(std::make_pair(Notifications[i].GetX(), Notifications[i].GetY()), distance));
        }
    }

    // Find the closest food

    if (!follow.empty())
    {
        

        closest_ant = follow[0];
        for (unsigned int i = 1; i < follow.size(); i++)
            if (follow[i].second < closest_ant.second)
                closest_ant = follow[i];

        if (std::get<0>(std::get<0>(closest_ant)) > x)
        {
            dx = 2;
        }
        else if (std::get<0>(std::get<0>(closest_ant)) < x)
        {
            dx = -2;
        }

        else dx = 0;

        if (std::get<1>(std::get<0>(closest_ant)) > y)
        {
            dy = 2;
        }
        else if (std::get<1>(std::get<0>(closest_ant)) < y)
        {
            dy = -2;
        }

        else dy = 0;

    }

    else
    {
        dx = (rand() % 5) - 2;
        dy = (rand() % 5) - 2;
    }

    for (unsigned int i = 0; i < Notifications.size(); i++)
    {
        if (Notifications[i] == Message(x, y, "Here I am"))
        {
            Notifications.erase(Notifications.begin() + i);
        }
    }

    x += dx;
    if (x >= WIDTH|| x < 0) x %= WIDTH;
    x = abs(x);
    y += dy;
    if (y >= LENGTH|| y < 0) y %= LENGTH;
    y = abs(y);

    //std::cout<<"\ndx = "<<dx<<" dy = "<<dy<<"\n";

    if (nutrition_level > 0) Notifications.push_back(Message(x, y, "Here I am"));
}

void Dragon::Eat(int n)
{
    nutrition_level += n;
}

void Dragon::InformOthers(char Map[][WIDTH])
{
    if (nutrition_level <= 0)
        return;

    // A dragon seeks ants among 24 fields around itself

    int a = ((y - 2) + LENGTH) % LENGTH, A;
    int b = ((x - 2) + WIDTH) % WIDTH, B;

    for (int i = 0; i < 5; i++)
    {
        A = a + i;
        if (A < 0 || A >= LENGTH) A %= LENGTH;
        for (int j = 0; j < 5; j++)
        {
            B = b + j;
            if (B < 0 || B >= WIDTH) B %= WIDTH;

            if (Map[A][B] == 'A')

            {
                Notifications.push_back(Message(B, A, "I see an ant!"));
            }

            for (unsigned int k = 0; k < Notifications.size(); k++)
            {
                if (Notifications[k] == Message(B, A, "I see an ant!") && Map[A][B] != 'A')
                {
                    Notifications.erase(Notifications.begin() + k);
                }
            }

        }
    }
}

void Dragon::PrintNotifications(int n)
{
    unsigned int i;
    if ((unsigned)n > Notifications.size())
        i = 0;
    else i = Notifications.size() - n;

    for (; i < Notifications.size(); i++)
    {
        std::cout << Notifications[i] << "      ";
        if (((i + 1) % 2 == 0) && i != Notifications.size() - 1) std::cout << "\n";
    }
    std::cout << "\n";
}
