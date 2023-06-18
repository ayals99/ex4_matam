#include "ScenarioCards.h"

const std::string TREASURE_CARD = "Treasure";
const std::string WELL_CARD = "Well";
const std::string BARFIGHT_CARD = "Barfight";
const std::string MANA_CARD = "Mana";
const std::string MERCHANT_CARD = "Merchant";
const int TREASURE_CARD_LOOT = 10;
const int WELL_CARD_DAMAGE = 10;
const int BARFIGHT_DAMAGE = 8;
const int MANA_CARD_HEAL = 10;
const int HEALTH_POTION_COST = 5;
const int FORCE_BOOST_COST = 10;
const int HEALT_POTION_HEAL = 1;
const int FORCE_BOOST = 1;
const int ZERO = '0';
const int ONE = '1';
const int TWO = '2';


void applyMerchantEncounter(Player& player);
void applyMerchantEncounterAUX(Player& player, int input);
char getInputForMerchantEncounter();



ScenarioCard::ScenarioCard(const std::string &name) : Card(name) {
    m_isMerchantCard = false;
    m_damageUponEncounter = 0;
    m_healUponEncounter = 0;
    m_lootUponEncounter = 0;

    if (name == TREASURE_CARD) {
        m_lootUponEncounter = TREASURE_CARD_LOOT;
    } else if (name == WELL_CARD) {
        m_damageUponEncounter = WELL_CARD_DAMAGE;
    } else if (name == BARFIGHT_CARD) {
        m_damageUponEncounter = BARFIGHT_DAMAGE;
    } else if (name == MANA_CARD) {
        m_healUponEncounter = MANA_CARD_HEAL;
    } else if (name == MERCHANT_CARD) {
        m_isMerchantCard = true;
    } else {
        throw invalidArgument();
    }
}

void ScenarioCard::applyEncounter(Player& player) const {
    if (m_isMerchantCard) {
        applyMerchantEncounter(player);
    } else if (m_name == TREASURE_CARD) {
        player.addCoins(m_lootUponEncounter);
        printTreasureMessage();
    } else if (m_name == WELL_CARD) {
        bool isNinja = player.getPlayerJob() == "Ninja";
        if (!isNinja) {
            player.damage(m_damageUponEncounter);
        }
        printWellMessage(isNinja);
    } else if (m_name == BARFIGHT_CARD) {
        bool isWarrior = player.getPlayerJob() == "Warrior";
        if (!isWarrior) {
            player.damage(m_damageUponEncounter);
        }
        printBarfightMessage(isWarrior);
    } else if (m_name == MANA_CARD) {
        bool isHealer = player.getPlayerJob() == "Healer";
        if (isHealer) {
            player.heal(m_healUponEncounter);
        }
        printManaMessage(isHealer);
    } else {
        throw invalidArgument();
    }
}

void applyMerchantEncounter(Player& player) {
    printMerchantInitialMessageForInteractiveEncounter(std::cout,
                                                       player.getName(),
                                                       player.getCoins());
    char input = getInputForMerchantEncounter();
    int inputAsInt = input - ZERO;
    applyMerchantEncounterAUX(player, inputAsInt);
}

void applyMerchantEncounterAUX(Player& player, int input) {
    int cost = 0;
    if (input == 1) {
        if (player.getCoins() < HEALTH_POTION_COST) {
            printMerchantInsufficientCoins(std::cout);
            cost = 0;
        } else {
            player.heal(HEALT_POTION_HEAL);
            player.pay(HEALTH_POTION_COST);
            cost = HEALTH_POTION_COST;
        }
    } else if (input == 2) {
        if (player.getCoins() < FORCE_BOOST_COST) {
            printMerchantInsufficientCoins(std::cout);
            cost = 0;
        } else {
            player.buff(FORCE_BOOST);
            player.pay(FORCE_BOOST_COST);
            cost = FORCE_BOOST_COST;
        }
    }
    printMerchantSummary(std::cout, player.getName(), input, cost);
}

char getInputForMerchantEncounter() {
    char input;
    std::cin >> input;
    while(input != ZERO && input != ONE && input != TWO) {
        printInvalidInput();
        std::cin >> input;
    }
    return input;
}

std::ostream& operator<<(std::ostream& os, const ScenarioCard& Card)
{
    printCardDetails(os, Card.getName());
    return os;
}
