#ifndef EX4_MATAM_WITCH_H
#define EX4_MATAM_WITCH_H

#include <string>

static const std::string WITCH_NAME = "Witch";
static const int WITCH_FORCE = 11;
static const int WITCH_DAMAGE = 10;
static const int WITCH_LOOT = 2;

#include "BattleCards.h"
class Witch : public BattleCard {
    Witch() : BattleCard(WITCH_NAME, WITCH_FORCE, WITCH_DAMAGE, WITCH_LOOT) {};

    Witch& operator=(const Witch& other) = delete;
    Witch(Witch& other) = delete;

    void applyEncounter(Player& player) const override{
        if(player.playerIsStronger(m_force)){
            player.addCoins(m_loot);
        }
        else{
            player.damage(m_healthPointsReduction);
            player.loseOneForce();
        }
    }
};

#endif //EX4_MATAM_WITCH_H
