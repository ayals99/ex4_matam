#include "Merchant.h"

static const int LEAVE = 0;
static const int BUY_HEALTH_POTION = 1;
static const int BUY_FORCE_BOOST = 2;
static const int ZERO = 0;
static const int INITIAL_INVALID_CHOICE = -1;

int getMerchantChoiceFromUser(Player& player);

void Merchant::applyEncounter(Player& player) const {
    int choice = getMerchantChoiceFromUser(player);
    int amountPayed = ZERO;
    int action = LEAVE;

    while (choice != LEAVE && action == LEAVE) {
        if (choice == BUY_HEALTH_POTION) {
            if (player.pay(HEALTH_POTION_COST)) {
                player.heal(HEALTH_ADDITION);
                amountPayed = HEALTH_POTION_COST;
                action = choice;
            }
            else {
                printMerchantInsufficientCoins(std::cout);
                choice = getMerchantChoiceFromUser(player);
            }
        }
        if (choice == BUY_FORCE_BOOST) {
            if (player.pay(FORCE_BOOST_COST)) {
                player.buff(FORCE_ADDITION);
                amountPayed = FORCE_BOOST_COST;
                action = choice;
            }
            else {
                printMerchantInsufficientCoins(std::cout);
                choice = getMerchantChoiceFromUser(player);
            }
        }
    }
    printMerchantSummary(std::cout, player.getName(), action, amountPayed);
}

bool validOption(int choice){
    return choice == LEAVE || choice == BUY_FORCE_BOOST || choice == BUY_HEALTH_POTION;
}

int getMerchantChoiceFromUser(Player& player){
    printMerchantInitialMessageForInteractiveEncounter(std::cout, player.getName(), player.getCoins());
    int choice = INITIAL_INVALID_CHOICE;
    while (!validOption(choice)){
        std::cin >> choice;
        if (!validOption(choice)){
            printInvalidInput();
        }
    }
    return choice;
}