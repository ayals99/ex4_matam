#include "Well.h"

void Well::applyEncounter(Player& player) const{
    bool isNinja = dynamic_cast<Ninja*>(&player);
    if(!isNinja) {
        player.damage(WELL_HP_LOSS);
    }
    printWellMessage(isNinja);
}