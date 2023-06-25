#include "Merchant.h"

static const int INITIAL_INVALID_CHOICE = -1;
static const int LEAVE = 0;
static const int BUY_HEALTH_POTION = 1;
static const int BUY_FORCE_BOOST = 2;
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

int getMerchantChoiceFromUser(const Player& player){
    printMerchantInitialMessageForInteractiveEncounter(std::cout, player.getName(), player.getCoins());
    std::string choice;
    int choiceInt = INITIAL_INVALID_CHOICE;

    while (!validOption(choiceInt)){
        std::getline(std::cin, choice);
        if (choice.length() != 1){
            printInvalidInput();
            continue;
        }
        try{
            choiceInt = std::stoi(choice);
        }catch (std::invalid_argument& e){
            printInvalidInput();
            continue;
        }
        if (!validOption(choiceInt)){
            printInvalidInput();
        }
    }
    return choiceInt;
}