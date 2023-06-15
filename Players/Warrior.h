#ifndef EX4_MATAM_WARRIOR_H
#define EX4_MATAM_WARRIOR_H

#include "Player.h"

class Warrior : public Player {
public:
    bool playerIsStronger(int opponentForce) const override{
        return ( (2*m_force + m_level) >= opponentForce );
    }
    std::string getPlayerJob() const override{
        return "Warrior";
    }
};

#endif //EX4_MATAM_WARRIOR_H