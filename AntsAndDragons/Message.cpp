#include "Message.h"

Message::Message(int a, int b, const std::string& Msg)
{
    x = a;
    y = b;
    msg = Msg;
    importance = 5;
}

bool Message::operator==(const Message& sec) {
    return((x == sec.x) && (y == sec.y) && (msg == sec.msg));
}

int Message::GetX()
{
    return x;
}

int Message::GetY()
{
    return y;
}

int Message::GetImportance()
{
    return importance;
}

void Message::LowerImportance()
{
    if (importance > 0) importance--;
}

std::string Message::GetMsg() {
    return msg;
}

std::ostream& operator<<(std::ostream& co, Message& K)
{
    return co << "(" << K.x << "," << K.y << ") - " << K.msg;
}