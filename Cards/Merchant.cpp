#include "Merchant.h"

static const int LEAVE = 0;
static const int BUY_HEALTH_POTION = 1;
static const int BUY_FORCE_BOOST = 2;
static const int ZERO = 0;
static const int INITIAL_INVALID_CHOICE = -1;

int getMerchantChoiceFromUser();

void Merchant::applyEncounter(Player& player) const{
    printMerchantInitialMessageForInteractiveEncounter(std::cout, player.getName(), player.getCoins());

    int choice = getMerchantChoiceFromUser();

    if (choice == BUY_HEALTH_POTION){
        if(player.pay(HEALTH_POTION_COST)){
            player.heal(HEALTH_ADDITION);
            printMerchantSummary(std::cout, player.getName(), BUY_HEALTH_POTION, HEALTH_ADDITION);
        }
        else{
            printMerchantInsufficientCoins(std::cout);
        }
    }
    else if (choice == BUY_FORCE_BOOST){
        if(player.pay(FORCE_BOOST_COST)){
            player.buff(FORCE_ADDITION);
            printMerchantSummary(std::cout, player.getName(), BUY_FORCE_BOOST, FORCE_ADDITION);
        }
        else{
            printMerchantInsufficientCoins(std::cout);
        }
    }
    else{ // choice == LEAVE
        printMerchantSummary(std::cout, player.getName(), LEAVE, ZERO);
    }

}


bool validOption(int choice){
    return choice == LEAVE || choice == BUY_FORCE_BOOST || choice == BUY_HEALTH_POTION;
}

int getMerchantChoiceFromUser(){
    int choice = INITIAL_INVALID_CHOICE;
    while (!validOption(choice)){
        std::cin >> choice;
        if (!validOption(choice)){
            printInvalidInput();
        }
    }
    return choice;
}