#ifndef EX4_MATAM_MANA_H
#define EX4_MATAM_MANA_H

#include "Card.h"

#include "../Players/Healer.h"

static const int MANA_HP_GAIN = 10;

class Mana : public Card {
public:
    explicit Mana(std::string name, int ) : Card(name) {};
    Mana() = delete;
    Mana& operator=(const Mana& other) = delete;
    Mana(const Mana& other) = delete;
    ~Mana() = default;


    void applyEncounter(Player& player) const override{
        bool isHealer = dynamic_cast<Healer*>(&player);
        if(isHealer){
            player.heal(MANA_HP_GAIN);
        }
        printManaMessage(isHealer);
    }
};

#endif //EX4_MATAM_MANA_H
