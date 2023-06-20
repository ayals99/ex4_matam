#ifndef EX4_MATAM_DRAGON_H
#define EX4_MATAM_DRAGON_H
#include <string>
#include "BattleCards.h"

static const std::string DRAGON_NAME = "Dragon";
static const int DRAGON_FORCE = 25;
static const int DRAGON_DAMAGE = MAX_HP;
static const int DRAGON_LOOT = 1000;

class Dragon : public BattleCard {
public:
    Dragon() : BattleCard(DRAGON_NAME, DRAGON_FORCE, DRAGON_DAMAGE, DRAGON_LOOT) {};

    Dragon& operator=(const Dragon& other) = delete;
    Dragon(Dragon& other) = delete;
    ~Dragon() override = default;

    void applyEncounter(Player& player) const override{
        if(player.playerIsStronger(m_force)){
            player.addCoins(m_loot);
            player.levelUp();
            printWinBattle(player.getName(), this->m_name);
        }
        else{
            player.setDead();
            printLossBattle(player.getName(), this->m_name);
        }
    }

    std::ostream& stringToPrint(std::ostream& os) const override{
        printCardDetails(os, m_name);
        printMonsterDetails(os, m_force, m_healthPointsReduction, m_loot, true);
        printEndOfCardDetails(os);
        return os;
    }
};

#endif //EX4_MATAM_DRAGON_H
