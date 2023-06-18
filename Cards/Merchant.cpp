#include "Merchant.h"

void Merchant::applyEncounter(Player& player) const{
    printMerchantInitialMessageForInteractiveEncounter(std::cout, player.getName(), player.getCoins());

    int choice = getMerchantChoiceFromUser(std::cin);



}