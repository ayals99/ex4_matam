#include "Barfight.h"

void Barfight::applyEncounter(Player& player) const{
    bool isWarrior = dynamic_cast<Warrior*>(&player);
    if(!isWarrior){
        player.damage(BARFIGHT_HP_LOSS);
    }
    printBarfightMessage(isWarrior);
}