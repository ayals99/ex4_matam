#ifndef EX4_MATAM_WITCH_H
#define EX4_MATAM_WITCH_H

#include <string>

static const std::string WITCH_NAME = "Witch";
static const int WITCH_FORCE = 11;
static const int WITCH_DAMAGE = 10;
static const int WITCH_LOOT = 2;

#include "BattleCards.h"
class Witch : public BattleCard {
public:
    explicit Witch() : BattleCard(WITCH_NAME, WITCH_FORCE, WITCH_DAMAGE, WITCH_LOOT) {};

    Witch& operator=(const Witch& other) = delete;
    Witch(Witch& other) = delete;
    ~Witch() override = default;

    void applyEncounter(Player& player) const override{
        if(player.playerIsStronger(m_force)){
            player.addCoins(m_loot);
            player.levelUp();
            printWinBattle(player.getName(), this->m_name);
        }
        else{
            player.damage(m_healthPointsReduction);
            player.loseOneForce();
            printLossBattle(player.getName(), this->m_name);
        }
    }
};

#endif //EX4_MATAM_WITCH_H
