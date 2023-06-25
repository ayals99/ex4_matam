#ifndef EX4_MATAM_WARRIOR_H
#define EX4_MATAM_WARRIOR_H

#include "Player.h"

class Warrior : public Player {
private:
    std::string m_job = "Warrior";

public:
    explicit Warrior(std::string name) : Player(name){}

    bool playerIsStronger(int opponentForce) const override{
        return ( (2*m_force + m_level) >= opponentForce );
    }

    const std::string& getPlayerJob() const override{
        return m_job;
    }
};
#endif //EX4_MATAM_WARRIOR_H