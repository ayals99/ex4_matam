#ifndef EX4_MATAM_WARRIOR_H
#define EX4_MATAM_WARRIOR_H

#include "Player.h"

const int FORCE_MULTIPLIER = 2;

class Warrior : public Player {
private:
    std::string m_job = "Warrior";

public:
    explicit Warrior(std::string name) : Player(name){}

    bool playerIsStronger(int opponentForce) const override;

    const std::string& getPlayerJob() const override;
};
#endif //EX4_MATAM_WARRIOR_H