#ifndef EX4_MATAM_TREASURE_H
#define EX4_MATAM_TREASURE_H

#include "Card.h"
static const int TREASURE_COIN_GAIN = 10;

class Treasure : public Card {
public:
    Treasure(std::string name) : Card(name) {};

    Treasure() = delete;
    virtual ~Treasure() = default;
    Treasure& operator=(const Treasure& other) = delete;
    Treasure(const Treasure& other) = delete;

    virtual void applyEncounter(Player& player) const override{
        player.addCoins(TREASURE_COIN_GAIN);
    }
};

#endif //EX4_MATAM_TREASURE_H
