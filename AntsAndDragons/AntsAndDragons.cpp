#include <iostream>
#include "Board.h"


int main()
{
    srand(time(NULL));

    Board B;

    char ch;

    while (true)
    {
        B.ClearMap();
        B.Update();
        B.Print();
        B.PrintLog();
        if (B.IsFinished())
        {
            if (B.NoAnts())
                std::cout << "Dragons have won!\n";
            else if (B.NoDragons())
                std::cout << "Ants have won!\n";
            else
                std::cout << "An indecisive fight!\n";
            break;
        }
        std::cout << "x - terminate the program, enter antoher key to continue...\n";
        std::cin >> ch;
        if (ch == 'x') break;
        std::cout << "\n\n\n\n\n\n\n\n\n\n"; // Put 10 newlines to 'clear' the screen
    }
    std::cin >> ch;
    return 0;
}
