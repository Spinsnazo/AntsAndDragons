#include "Ant.h"

std::vector<Message> Ant::Notifications = {};

Ant::Ant(int a, int b)
{
    x = a;
    y = b;
    nutrition_level = 15;
    Notifications.push_back(Message(x, y, "Here I am"));
}

void Ant::Move()
{
    --nutrition_level;

    std::vector<std::pair<std::pair<int, int>, double>>avoid;
    std::vector<std::pair<std::pair<int, int>, double>>follow;

    int dx = 0, dy = 0; // Used for calculating distance and then for the ant's movements 

    double distance = 0;
    std::pair<std::pair<int, int>, double>closest_food;
    std::pair<std::pair<int, int>, double>closest_threat;

    for (unsigned int i = 0; i < Notifications.size(); i++)
    {
        if (Notifications[i].GetMsg() == "I see food!")
        {
            dx = x - Notifications[i].GetX();
            dy = y - Notifications[i].GetY();
            distance = sqrt(dx * dx + dy * dy);
            follow.push_back(std::make_pair(std::make_pair(Notifications[i].GetX(), Notifications[i].GetY()), distance));
        }

        if (Notifications[i].GetMsg() == "I'm dead!" || Notifications[i].GetMsg() == "There is a dragon!")
        {
            dx = x - Notifications[i].GetX();
            dy = y - Notifications[i].GetY();
            distance = sqrt(dx * dx + dy * dy);
            avoid.push_back(std::make_pair(std::make_pair(Notifications[i].GetX(), Notifications[i].GetY()), distance));
        }
    }

    // Find the closest food

    if (!follow.empty())
    {
        closest_food = follow[0];
        for (unsigned int i = 1; i < follow.size(); i++)
            if (follow[i].second < closest_food.second)
                closest_food = follow[i];
    }

    // Find the closest threat

    if (!avoid.empty())
    {
        closest_threat = avoid[0];
        for (unsigned int i = 1; i < avoid.size(); i++)
            if (avoid[i].second < closest_threat.second)
                closest_threat = avoid[i];
    }

    dx = 0, dy = 0;

    // Determine the direction of the movement

    bool pick_food = false;
    bool random_move = false;

    if (!follow.empty() && !avoid.empty())
    {
        pick_food = (closest_food.second < closest_threat.second ? true : false);
    }
    else if (follow.empty() && !avoid.empty())
    {
        pick_food = false;
    }
    else if (!follow.empty() && avoid.empty())
    {
        pick_food = true;
    }
    else random_move = true;


    if (!random_move)
    {

        // Determine the direction of following the nearest food

        if (pick_food)
        {
            if (std::get<0>(std::get<0>(closest_food)) > x) dx = 1;
            else if (std::get<0>(std::get<0>(closest_food)) < x) dx = -1;
            else dx = 0;
            if (std::get<1>(std::get<0>(closest_food)) > y) dy = 1;
            else if (std::get<1>(std::get<0>(closest_food)) < y) dy = -1;
            else dy = 0;
        }

        // Determine the direction of escaping from a dragon

        else
        {
            if (std::get<0>(std::get<0>(closest_threat)) > x) dx = -1;
            else if (std::get<0>(std::get<0>(closest_threat)) < x) dx = 1;
            else dx = 0;
            if (std::get<1>(std::get<0>(closest_threat)) > y) dy = -1;
            else if (std::get<1>(std::get<0>(closest_threat)) < y) dy = 1;
            else dy = 0;
        }
    }

    else
    {
        dx = (rand() % 3) - 1;
        dy = (rand() % 3) - 1;
    }

    for (unsigned int i = 0; i < Notifications.size(); i++)
    {
        if (Notifications[i] == Message(x, y, "Here I am"))
        {
            Notifications.erase(Notifications.begin() + i);
        }
    }

    x += dx;
    if (x >= WIDTH || x < 0) x %= WIDTH;
    x = abs(x);
    y += dy;
    if (y >= LENGTH || y < 0) y %= LENGTH;
    y = abs(y);
    if (nutrition_level > 0) Notifications.push_back(Message(x, y, "Here I am"));

}

void Ant::Eat(int)
{
    nutrition_level += 10;
}

void Ant::InformOthers(char Map[][WIDTH])
{
    if (Map[y][x] == 'D' || nutrition_level <= 0)
    {
        Notifications.push_back(Message(x, y, "I'm dead!"));
        return;
    }

    // Cancel messages about food

    for (unsigned int i = 0; i < Notifications.size(); i++)
    {
        if (Notifications[i] == Message(x, y, "I see food!"))
        {
            Notifications.erase(Notifications.begin() + i);
        }
    }

    // An ant seeks dragons/food among 8 fields around itself

    int a = ((y - 1) + LENGTH) % LENGTH, A;
    int b = ((x - 1) + WIDTH) % WIDTH, B;

    for (int i = 0; i < 3; i++)
    {
        A = a + i;

        if (A < 0 || A >= LENGTH) A %= LENGTH;

        for (int j = 0; j < 3; j++)
        {
            B = b + j;

            if (B < 0 || B >= WIDTH) B %= WIDTH;

            if (Map[A][B] == 'F')
            {
                Notifications.push_back(Message(B, A, "I see food!"));
            }
            if (Map[A][B] == 'D')
            {
                Notifications.push_back(Message(B, A, "There is a dragon!"));
            }
        }
    }
}

void Ant::PrintNotifications(int n)
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

