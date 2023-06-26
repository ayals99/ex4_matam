#include "Treasure.h"

void Treasure::applyEncounter(Player& player) const{
    player.addCoins(TREASURE_COIN_GAIN);
    printTreasureMessage();
}