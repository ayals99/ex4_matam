#ifndef EX4_MATAM_WELL_H
#define EX4_MATAM_WELL_H

#include "Card.h"
#include "../Players/Ninja.h"

static const int WELL_HP_LOSS = 10;
static const std::string WELL_NAME = "Well";

class Well : public Card {
public:
    Well() : Card(WELL_NAME) {};
    ~Well() override = default;
    Well& operator=(const Well& other) = delete;
    Well(const Well& other) = delete;

    void applyEncounter(Player& player) const override;
};

#endif //EX4_MATAM_WELL_H
