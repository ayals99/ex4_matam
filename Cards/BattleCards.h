#ifndef EX4_MATAM_BATTLE_CARDS_H
#define EX4_MATAM_BATTLE_CARDS_H

#include "Card.h"
#include <memory>

class BattleCardStats {
public:
    explicit BattleCardStats(int force, int healthPointsReduction, int loot) :
            m_force(force), m_healthPointsReduction(healthPointsReduction), m_loot(loot) {};

    int m_force;
    int m_healthPointsReduction;
    int m_loot;
    BattleCardStats(BattleCardStats& other) = delete;
    ~BattleCardStats(){
        delete this;
    }
};

class BattleCard : public Card {
protected:
    std::unique_ptr<BattleCardStats> m_stats;

public:
    BattleCard(std::string name, int force, int hpReduction, int loot)
    :Card(name), m_stats(new BattleCardStats(force, hpReduction, loot)) {};

    BattleCard() = delete;
    BattleCard(BattleCard& other) = delete;
    virtual ~BattleCard() = default;
};

#endif //EX4_MATAM_BATTLE_CARDS_H
