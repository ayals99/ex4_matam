#ifndef EX4_MATAM_BATTLECARDS_H
#define EX4_MATAM_BATTLECARDS_H

#include "Card.h"

class BattleCard : public Card {
private:
    int m_force;
    int m_loot;
    int m_damageUponLoss;

public:
    /**
     * C'tor of BattleCard class
     * @param name
     * return A new instance of BattleCard.
     */
    explicit BattleCard(const std::string& name);

    /**
     * Copy C'tor of BattleCard class
     * @param other
     * return A new instance of BattleCard.
     */
    BattleCard(const BattleCard& other) = default;

    /**
     * Deafult D'tor of BattleCard class
     */
    ~BattleCard() override = default;

    std::ostream& applyEncounter(std::ostream& os, Player& player) const override;

    /**
     * Prints the card's info.
     */
    void printCardInfo(std::ostream &os) const;

    /**
     * Printing operator for BattleCard class
     * @param os
     * @param BattleCard
     * @return
     */
    friend std::ostream& operator<<(std::ostream& os, const BattleCard& Card);
};

#endif //EX4_MATAM_BATTLECARDS_H
