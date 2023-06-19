#ifndef EX4_MATAM_WELL_H
#define EX4_MATAM_WELL_H

#include "Card.h"
#include "../Players/Ninja.h"

static const int WELL_HP_LOSS = 10;

class Well : public Card {
    Well(std::string name) : Card(name) {};

    Well() = delete;
    ~Well() = default;
    Well& operator=(const Well& other) = delete;
    Well(const Well& other) = delete;

    void applyEncounter(Player& player) const override{
        bool isNinja = dynamic_cast<Ninja*>(&player);
        if(!isNinja) {
            player.damage(WELL_HP_LOSS);
        }
        printWellMessage(isNinja);
    }
};

#endif //EX4_MATAM_WELL_H
