#ifndef EX4_MATAM_EXCEPTION_H
#define EX4_MATAM_EXCEPTION_H

#include <stdexcept>

class invalidPlay : std::exception {
public:
    const char* what() const noexcept override{
        return "Mtmchkin playing error: Invalid play was attempted. Game is over";
    }

};

class noPlayersInGame : std::exception {
public:
    const char* what() const noexcept override{
        return "Mtmchkin playing error: No players in the game";
    }
};
#endif //EX4_MATAM_EXCEPTION_H