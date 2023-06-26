#include "Ninja.h"

void Ninja::addCoins(int coinsToAdd){
    m_coins += COINS_MULTIPLIER * coinsToAdd;
}

const std::string& Ninja::getPlayerJob() const{
    return m_job;
}
