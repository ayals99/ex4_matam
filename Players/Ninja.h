#ifndef EX4_MATAM_NINJA_H
#define EX4_MATAM_NINJA_H

#include "Player.h"


const int COINS_MULTIPLIER = 2;


class Ninja : public Player {
private:
    std::string m_job = "Ninja";
public:
    explicit Ninja(std::string name) : Player(name) {}

    void addCoins(int coinsToAdd) override;

    const std::string& getPlayerJob() const override;
};

#endif //EX4_MATAM_NINJA_H