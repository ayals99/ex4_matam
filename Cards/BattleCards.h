#ifndef EX4_MATAM_BATTLE_CARDS_H
#define EX4_MATAM_BATTLE_CARDS_H

#include "Card.h"


class BattleCard : public Card {
protected:
    int m_force;
    int m_healthPointsReduction;
    int m_loot;

public:
    BattleCard(std::string name, int force, int hpReduction, int loot)
    : Card(name), m_force(force), m_healthPointsReduction(hpReduction), m_loot(loot) {};

    BattleCard() = delete;
    BattleCard(BattleCard& other) = delete;
    virtual ~BattleCard() = default;

    std::ostream& stringToPrint(std::ostream& os) const override{
        printCardDetails(os, m_name);
        printMonsterDetails(os, m_force, m_healthPointsReduction, m_loot, false);
        printEndOfCardDetails(os);
        return os;
    }
};


#endif //EX4_MATAM_BATTLE_CARDS_H
