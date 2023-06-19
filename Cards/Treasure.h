#ifndef EX4_MATAM_TREASURE_H
#define EX4_MATAM_TREASURE_H

#include "Card.h"
static const int TREASURE_COIN_GAIN = 10;
static const std::string TREASURE_NAME = "Treasure";

class Treasure : public Card {
public:
    Treasure() : Card(TREASURE_NAME) {};
    Treasure& operator=(const Treasure& other) = delete;
    Treasure(const Treasure& other) = delete;
    ~Treasure() override = default;

    void applyEncounter(Player& player) const override{
        player.addCoins(TREASURE_COIN_GAIN);
        printTreasureMessage();
    }
};

#endif //EX4_MATAM_TREASURE_H
