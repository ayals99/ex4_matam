#ifndef EX4_MATAM_BARFIGHT_H
#define EX4_MATAM_BARFIGHT_H

#include "Card.h"
#include "../Players/Warrior.h"

static const int BARFIGHT_HP_LOSS = 8;

class Barfight : public Card {
public:
    Barfight(std::string name) : Card(name) {};
    Barfight() = delete;
    virtual ~Barfight() = default;
    Barfight& operator=(const Barfight& other) = delete;
    Barfight(const Barfight& other) = delete;

    virtual void applyEncounter(Player& player) const override{
        if(dynamic_cast<Warrior*>(&player) == nullptr) {
            player.damage(BARFIGHT_HP_LOSS);
        }
    }
};

#endif //EX4_MATAM_BARFIGHT_H
