#ifndef EX4_MATAM_BARFIGHT_H
#define EX4_MATAM_BARFIGHT_H

#include "Card.h"
#include "../Players/Warrior.h"

static const std::string BARFIGHT_NAME = "Barfight";
static const int BARFIGHT_HP_LOSS = 10;

class Barfight : public Card {
public:
    Barfight() : Card(BARFIGHT_NAME) {};
    ~Barfight() override = default;
    Barfight& operator=(const Barfight& other) = delete;
    Barfight(const Barfight& other) = delete;

    void applyEncounter(Player& player) const override;
};
#endif //EX4_MATAM_BARFIGHT_H
