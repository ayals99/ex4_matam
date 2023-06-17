#ifndef EX4_MATAM_BATTLECARDS_H
#define EX4_MATAM_BATTLECARDS_H

#include "Card.h"
class BattleCard : public Card {
protected:
    int m_force;
    int m_loot;

public:
    BattleCard() : Card() {};
    virtual void commenceBattle(Player& player) const = 0;
};

#endif //EX4_MATAM_BATTLECARDS_H
