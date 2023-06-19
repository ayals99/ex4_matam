#include "Merchant.h"

static const char LEAVE = '0';
static const char BUY_HEALTH_POTION = '1';
static const char BUY_FORCE_BOOST = '2';
static const char ZERO = '0';
static const char INITIAL_INVALID_CHOICE = '~';

int getMerchantChoiceFromUser(const Player& player);

void Merchant::applyEncounter(Player& player) const {
    int choice = getMerchantChoiceFromUser(player);
    int amountPayed = ZERO;
    int action = LEAVE;

    if (choice == BUY_HEALTH_POTION) {
        if (player.pay(HEALTH_POTION_COST)) {
            player.heal(HEALTH_ADDITION);
            amountPayed = HEALTH_POTION_COST;
            action = choice;
        }
        else {
            printMerchantInsufficientCoins(std::cout);
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
        }
    }

    printMerchantSummary(std::cout, player.getName(), action, amountPayed);
}

bool validOption(int choice){
    return choice == LEAVE || choice == BUY_FORCE_BOOST || choice == BUY_HEALTH_POTION;
}

int getMerchantChoiceFromUser(const Player& player){
    printMerchantInitialMessageForInteractiveEncounter(std::cout, player.getName(), player.getCoins());
    char choice = INITIAL_INVALID_CHOICE;
    while (!validOption(choice)){
        std::cin >> choice;
        if (!validOption(choice)){
            printInvalidInput();
        }
    }
    int choiceAsInt = choice - ZERO;
    return choiceAsInt;
}