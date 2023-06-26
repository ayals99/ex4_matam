#include "Mana.h"

void Mana::applyEncounter(Player& player) const{
    bool isHealer = dynamic_cast<Healer*>(&player);
    if(isHealer){
        player.heal(MANA_HP_GAIN);
    }
    printManaMessage(isHealer);
}