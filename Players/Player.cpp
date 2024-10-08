#include "Player.h"
#include "../utilities.h"

/** Constructors: */
Player::Player(std::string& name) : m_name(name),
                                    m_level(INITIAL_LEVEL),
                                    m_force(INITIAL_FORCE),
                                    m_health(DEFAULT_MAXIMAL_HEALTH),
                                    m_coins(INITIAL_COINS) {}

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
    return (!dead() && !won());
}

bool Player::dead() const {
    return m_health == MINIMAL_HEALTH; // defined in "HealthPoints.h" to be zero
}

bool Player::won() const {
    return m_level == MAXIMAL_LEVEL;
}

bool Player::playerIsStronger(int opponentForce) const{
    return ( (m_force + m_level) >= opponentForce );
}

/** Setters: */

/**
 * @param coinsToAdd - The amount of coins to add to the player.
 * @return void
 */
void Player::addCoins(int coinsToAdd){
    if(coinsToAdd > 0) {
        this->m_coins += coinsToAdd;
    }
}

/**
 * Increases the players level by 1. If the player's level is MAX_LEVEL (10), does nothing.
 * @param none
 * @return void
 */
void Player::levelUp(){
    if (m_level < MAXIMAL_LEVEL)
    {
        m_level++;
    }
}

/**
 * @param hpToAdd - The amount of HP to add to the player.
 * @return void
 */
void Player::heal(int hpToAdd){
    if(hpToAdd > 0) {
        m_health += hpToAdd;
    }
}

/**
 * Reduces the player's HP by the given amount. If the damage is 0 or less, does nothing.
 * Only reduces the player's HP to 0, not below.
 * @param hpToReduce - The amount of HP to reduce from the player.
 * @return void
 */
void Player::damage(int hpToReduce){
    if (hpToReduce > 0){
        m_health -= hpToReduce;
    }
}

/**
 * @param forceToAdd - The amount of force to add to the player.
 * @return void
 */
void Player::buff(int forceToAdd){
    if(forceToAdd > 0) {
        this->m_force += forceToAdd;
    }
}

/**
 * @param coinsToPay - The amount of coins to pay.
 * @return void
 */
bool Player::pay(int coinsToPay){
    if (this->m_coins >= coinsToPay)
    {
        this->m_coins -= coinsToPay;
        return true;
    }

    return false;
}

/**
 * @param none - removes one unit of force when the player loses to a Witch
 * @return void
 */
void Player::loseOneForce(){
    if (m_force > MINIMUM_FORCE) {
        m_force--;
    }
}

/** Operators: */
std::ostream& operator<<(std::ostream& os, const Player& player){
    int health = player.getHealth().getHealthInteger();
    printPlayerDetails(os, player.getName(),
                       player.getPlayerJob(),
                       player.getLevel(),
                       player.getForce(),
                       health,
                       player.getCoins());
    return os;
}