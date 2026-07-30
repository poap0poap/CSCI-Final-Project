#ifndef PLAYER_INFO_H
#define PLAYER_INFO_H
#include <string>

class playerInfo {
    public:
    std::string firstName;
    std::string lastName;
    struct stats{
        int age;
        int strength;
        int stamina;
        int wisdom;
        int points;
    };
};

#endif
