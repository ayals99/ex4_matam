#ifndef EX4_MATAM_MANA_H
#define EX4_MATAM_MANA_H

#include "Card.h"

#include "../Players/Healer.h"

static const int MANA_HP_GAIN = 10;
static const std::string MANA_NAME = "Mana";

class Mana : public Card {
public:
    explicit Mana() : Card(MANA_NAME) {};
    Mana& operator=(const Mana& other) = delete;
    Mana(const Mana& other) = delete;
    ~Mana() override = default;


    void applyEncounter(Player& player) const override{
        bool isHealer = dynamic_cast<Healer*>(&player);
        if(isHealer){
            player.heal(MANA_HP_GAIN);
        }
        printManaMessage(isHealer);
    }
};

#endif //EX4_MATAM_MANA_H
