#include "Merchant.h"

static const char ZERO = '0';
static const char INITIAL_INVALID_CHOICE = '~';

static const char LEAVE = '0';
static const char BUY_HEALTH_POTION = '1';
static const char BUY_FORCE_BOOST = '2';
static int BOUGHT_HEALTH_POTION = 1;
static int BOUGHT_FORCE_BOOST = 2;

static const int DID_NOT_PAY = 0;

int getMerchantChoiceFromUser(const Player& player);

void Merchant::applyEncounter(Player& player) const {
    int choice = getMerchantChoiceFromUser(player);
    int amountPayed = DID_NOT_PAY;

    if (choice == BOUGHT_HEALTH_POTION) {
        if (player.pay(HEALTH_POTION_COST)) {
            player.heal(HEALTH_ADDITION);
            amountPayed = HEALTH_POTION_COST;
        }
        else {
            printMerchantInsufficientCoins(std::cout);
        }
    }
    if (choice == BOUGHT_FORCE_BOOST) {
        if (player.pay(FORCE_BOOST_COST)) {
            player.buff(FORCE_ADDITION);
            amountPayed = FORCE_BOOST_COST;
        }
        else {
            printMerchantInsufficientCoins(std::cout);
        }
    }

    printMerchantSummary(std::cout, player.getName(), choice, amountPayed);
}

bool validOption(int choice){
    return choice == LEAVE || choice == BUY_FORCE_BOOST || choice == BUY_HEALTH_POTION;
}

int convertChoiceToInt(char choice){
    return choice - ZERO;
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
    return convertChoiceToInt(choice);
}