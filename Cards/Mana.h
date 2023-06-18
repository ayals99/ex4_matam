#ifndef EX4_MATAM_MANA_H
#define EX4_MATAM_MANA_H

#include "Card.h"

#include "../Players/Healer.h"

static const int MANA_HP_GAIN = 10;

class Mana : public Card {
public:
    Mana(std::string name, int ) : Card(name) {};
    Mana() = delete;
    virtual ~Mana() = default;
    Mana& operator=(const Mana& other) = delete;
    Mana(const Mana& other) = delete;

    virtual void applyEncounter(Player& player) const override{
        if(dynamic_cast<Healer*>(&player)){
            player.heal(MANA_HP_GAIN);
        }
    }
};

#endif //EX4_MATAM_MANA_H
