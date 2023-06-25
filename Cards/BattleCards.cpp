#include "BattleCards.h"

std::ostream& BattleCard::stringToPrint(std::ostream& os) const{
    bool isDragon = m_name == "Dragon";
    printCardDetails(os, m_name);
    printMonsterDetails(os, m_force, m_healthPointsReduction, m_loot, isDragon);
    printEndOfCardDetails(os);
    return os;
}

void BattleCard::applyEncounter(Player &player) const {
    if (player.playerIsStronger(m_force)) {
        player.addCoins(m_loot);
        player.levelUp();
        printWinBattle(player.getName(), this->m_name);
    } else {
        if (this->m_name == "Dragon") {
            player.damage(m_healthPointsReduction);
        } else {
            if (this->m_name == "Witch") {
                player.loseOneForce();
            }
            player.damage(m_healthPointsReduction);
        }
        printLossBattle(player.getName(), this->m_name);
    }
}

