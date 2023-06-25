#ifndef EX4_MATAM_NINJA_H
#define EX4_MATAM_NINJA_H

#include "Player.h"


const int COINS_MULTIPLIER = 2;


class Ninja : public Player {
private:
    std::string m_job = "Ninja";
public:
    explicit Ninja(std::string name) : Player(name) {}

    void addCoins(int coinsToAdd) override{
        m_coins += COINS_MULTIPLIER * coinsToAdd;
    }

    const std::string& getPlayerJob() const override{
        return m_job;
    }
};

#endif //EX4_MATAM_NINJA_H