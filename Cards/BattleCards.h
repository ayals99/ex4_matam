#ifndef EX4_MATAM_BATTLE_CARDS_H
#define EX4_MATAM_BATTLE_CARDS_H

#include "Card.h"


class BattleCard : public Card {
private:
    BattleCard(std::string name, int force, int hpReduction, int loot)
            : Card(std::move(name)), m_force(force), m_healthPointsReduction(hpReduction), m_loot(loot) {};

protected:
    int m_force;
    int m_healthPointsReduction;
    int m_loot;

public:


    BattleCard() = delete;
    BattleCard(BattleCard& other) = delete;
    virtual ~BattleCard() = default;

    void applyEncounter(Player& player) const override;

    std::ostream& stringToPrint(std::ostream& os) const override;
};


#endif //EX4_MATAM_BATTLE_CARDS_H
