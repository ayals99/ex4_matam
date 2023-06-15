#ifndef EX4_MATAM_NINJA_H
#define EX4_MATAM_NINJA_H

#include "Player.h"

class Ninja : public Player {
private:
    std::string m_job = "Ninja";
public:
    explicit Ninja(std::string name) : Player(name) {}

    void addCoins(int coinsToAdd) override{
        m_coins += 2*coinsToAdd;
    }

    const std::string& getPlayerJob() const override{
        return m_job;
    }
};

#endif //EX4_MATAM_NINJA_H