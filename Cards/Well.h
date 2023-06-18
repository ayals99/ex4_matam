#ifndef EX4_MATAM_WELL_H
#define EX4_MATAM_WELL_H

#include "Card.h"
#include "../Players/Ninja.h"

static const int WELL_HP_LOSS = 10;

class Well : public Card {
    Well(std::string name) : Card(name) {};

    Well() = delete;
    virtual ~Well() = default;
    Well& operator=(const Well& other) = delete;
    Well(const Well& other) = delete;

    virtual void applyEncounter(Player& player) const override{
        if(dynamic_cast<Ninja*>(&player) == nullptr) {
            player.damage(WELL_HP_LOSS);
        }
    }
};

#endif //EX4_MATAM_WELL_H
