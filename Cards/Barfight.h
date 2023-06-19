#ifndef EX4_MATAM_BARFIGHT_H
#define EX4_MATAM_BARFIGHT_H

#include "Card.h"
#include "../Players/Warrior.h"

static const std::string BARFIGHT_NAME = "Barfight";
static const int BARFIGHT_HP_LOSS = 8;

class Barfight : public Card {
public:
    Barfight() : Card(BARFIGHT_NAME) {};
    ~Barfight() = default;
    Barfight& operator=(const Barfight& other) = delete;
    Barfight(const Barfight& other) = delete;

    void applyEncounter(Player& player) const override{
        bool isWarrior = dynamic_cast<Warrior*>(&player);
        if(!isWarrior){
            player.damage(BARFIGHT_HP_LOSS);
        }
        printBarfightMessage(isWarrior);
    }
};


#endif //EX4_MATAM_BARFIGHT_H
