#ifndef EX4_MATAM_PLAYER_H
#define EX4_MATAM_PLAYER_H

#include <string>
#include "HealthPoints.h"

class Player{

private:
    std::string m_name;
    int m_level; // 1-10
    int force; // >=0
    HealthPoints m_health;
    int m_coins; // >=0
    std::string m_type;

public:
    Player();
    virtual ~Player() = 0;
    bool isInGame() const;
    bool dead() const;
    bool won() const;
};

bool Player::isInGame() const{
    return (!dead() || !won());
}

bool Player::dead() const {
    return m_health > MINIMAL_HEALTH; // defined in "HealthPoints.h" to be zero
}

bool Player::won() const {
    return m_level == 10;
}

#endif //EX4_MATAM_PLAYER_H
