/*
Game - Treausre Hunter
*/
#include <iostream>
#include "game.h"


int main() {
    std::cout << "\033[?25l"; //get outta here cursor
    Game Game{};
    Game.run();
    std::cout << "\n\n";
}
