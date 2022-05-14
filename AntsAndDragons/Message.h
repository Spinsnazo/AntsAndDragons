#ifndef Message_H
#define Message_H

#include <iostream>
#include <string>
#include <utility>


class Message
{
public:
    Message(int, int, const std::string&);
    bool operator==(const Message&);
    int GetX();
    int GetY();
    std::string GetMsg();
protected:

private:
    int x, y;
    std::string msg;
    friend std::ostream& operator<<(std::ostream&, Message&);
};

#endif // Message_H
