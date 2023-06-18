#ifndef EX4_MATAM_DRAGON_H
#define EX4_MATAM_DRAGON_H
#include <string>
#include "BattleCards.h"

static const std::string DRAGON_NAME = "DRAGON";
static const int DRAGON_FORCE = 25;
static const int DRAGON_DAMAGE = MAX_HP;
static const int DRAGON_LOOT = 1000;

class Dragon : public BattleCard {

    Dragon() : BattleCard(DRAGON_NAME, DRAGON_FORCE, DRAGON_DAMAGE, DRAGON_LOOT) {};

    Dragon& operator=(const Dragon& other) = delete;
    Dragon(Dragon& other) = delete;
    ~Dragon() = default;

    void applyEncounter(Player& player) const override{
        if(player.playerIsStronger(m_stats->m_force))){
            player.addCoins(m_stats->m_loot);
        }
        else{
            player.setDead();
        }
    }

};

#endif //EX4_MATAM_DRAGON_H
