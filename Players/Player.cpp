#include "Player.h"

/** Constructors: */

Player::Player() : m_level(INITIAL_LEVEL), m_force(INITIAL_FORCE),  m_coins(INITIAL_COINS), m_health(MAX_HP){
    // TODO: assign player a name
}

/** Getters:*/
std::string Player::getName() const{
    return m_name;
}

int Player::getLevel() const{
    return m_level;
}

int Player::getForce() const{
    return m_force;
}

HealthPoints Player::getHealth() const{
    return m_health;
}

int Player::getCoins() const{
    return m_coins;
}

bool Player::isInGame() const{
    return (!dead() || !won());
}

bool Player::dead() const {
    return m_health > MINIMAL_HEALTH; // defined in "HealthPoints.h" to be zero
}

bool Player::won() const {
    return m_level == MAXIMAL_LEVEL;
}

bool Player::playerIsStronger(int opponentForce) const{
    return ( (m_force + m_level) >= opponentForce );
}

/** Setters: */

void Player::levelUp(){
//    if(m_level >= MAXIMAL_LEVEL){
//        throw PlayerReachedMaxLevel();
//    }
    m_level++;
}

void Player::addHealth(int healthToAdd){
    m_health += healthToAdd;
}

void Player::reduceHealthPoints(int healthToReduce){
    m_health -= healthToReduce;
}

void Player::addCoins(int coinsToAdd){
    m_coins += coinsToAdd;
}

void Player::setDead(){
    m_health = MINIMAL_HEALTH;
}

void Player::loseOneForce(){
    if (m_force > 0) {
        m_force--;
    }
}

/** Operators: */
std::ostream& operator<<(std::ostream& os, const Player& player){
    int health = player.getHealth().getHealthInteger();
    printPlayerDetails(os,player.m_name,player.getPlayerJob(),player.m_level,player.m_force,health,player.m_coins);
    return os;
}