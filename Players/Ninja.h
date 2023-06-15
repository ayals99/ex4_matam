#ifndef EX4_MATAM_NINJA_H
#define EX4_MATAM_NINJA_H

#include "Player.h"

class Ninja : public Player {
public:
    void addCoins(int coinsToAdd) override{
        m_coins += 2*coinsToAdd;
    }
    std::string getPlayerJob() const override{
        return "Ninja";
    }
};

#endif //EX4_MATAM_NINJA_H