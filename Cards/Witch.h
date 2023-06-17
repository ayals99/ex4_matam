#ifndef EX4_MATAM_WITCH_H
#define EX4_MATAM_WITCH_H

#include <string>

static const std::string WITCH_NAME = "Witch";
static const int WITCH_DAMAGE = 10;

#include "BattleCards.h"
class Witch : public BattleCard {
    int m_healthPointsDamage;
    Witch() : BattleCard(WITCH_NAME, ), m_healthPointsDamage(){};

    void applyEncounter(Player& player) const override{
        if(player.playerIsStronger(m_force)){
            player.addCoins(m_loot);
        }
        else{
            player.damage(m_healthPointsDamage);
            player.loseOneForce();
        }
    }
};

#endif //EX4_MATAM_WITCH_H
