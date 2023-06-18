#ifndef EX4_MATAM_MERCHANT_H
#define EX4_MATAM_MERCHANT_H


#include "Card.h"

static const int FORCE_BOOST_COST = 10;
static const int HEALTH_POTION_COST = 5;
static const int HEALTH_ADDITION = 1;
static const int FORCE_ADDITION = 1;

class Merchant : public Card {

private:
    std::string m_name;
    int m_forceBoostCost = FORCE_BOOST_COST;
    int m_healthPotionCost = HEALTH_POTION_COST;
    int m_healthAddition = HEALTH_ADDITION;
    int m_forceAddition = FORCE_ADDITION;

public:
    explicit Merchant(std::string name) : Card(name), m_forceBoostCost(FORCE_BOOST_COST), m_healthPotionCost(HEALTH_POTION_COST),
                                m_healthAddition(HEALTH_ADDITION), m_forceAddition(FORCE_ADDITION) {};

    virtual ~Merchant() = default;
    Merchant() = delete;
    Merchant(const Merchant&) = delete;
    Merchant& operator=(const Merchant&) = delete;

    void applyEncounter(Player& player) const override;
};

#endif //EX4_MATAM_MERCHANT_H
