#include "Warrior.h"

bool Warrior::playerIsStronger(int opponentForce) const{
    return ( (FORCE_MULTIPLIER*m_force + m_level) >= opponentForce );
}

const std::string& Warrior::getPlayerJob() const{
    return m_job;
}