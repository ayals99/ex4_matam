#ifndef EX4_MATAM_SCENARIOCARDS_H
#define EX4_MATAM_SCENARIOCARDS_H

#include "Card.h"

class ScenarioCard : public Card {
private:
    bool m_isMerchantCard;
    int m_damageUponEncounter;
    int m_healUponEncounter;
    int m_lootUponEncounter;

public:
    /**
     * C'tor of ScenarioCard class
     * @param name
     * return A new instance of ScenarioCard.
     */
    explicit ScenarioCard(const std::string& name);

    /**
     * Copy C'tor of ScenarioCard class
     * @param other
     * return A new instance of ScenarioCard.
     */
    ScenarioCard(const ScenarioCard& other) = default;

    /**
     * Deafult D'tor of ScenarioCard class
     */
    ~ScenarioCard() override = default;

    /**
    * Applies the card's effect on the player.
    *
    * @param player - The player to apply the card's effect on.
    * @return void
    */
    std::ostream& applyEncounter(std::ostream& os, Player& player) const override;

    /**
    * Printing operator for ScenarioCard class
    * @param os
    * @param BattleCard
    * @return
    */
    friend std::ostream& operator<<(std::ostream& os, const ScenarioCard& Card);
};



#endif //EX4_MATAM_SCENARIOCARDS_H
