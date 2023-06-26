#include "Healer.h"

void Healer::heal(int healthToAdd){
    if(healthToAdd > 0) {
        m_health += HP_MULTIPLIER * healthToAdd;
    }
}

const std::string& Healer::getPlayerJob() const{
    return m_job;
}