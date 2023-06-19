#include "Players/Player.h"
#include "Cards/Card.h"

#include "Cards/Witch.h"
#include "Cards/Barfight.h"
#include "Cards/Dragon.h"
#include "Cards/Mana.h"
#include "Cards/Gremlin.h"
#include "Cards/Merchant.h"
#include "Cards/Well.h"
#include "Cards/Treasure.h"



void run_test(std::function<bool()> test, std::string test_name){
    if(!test()){
        std::cout<< test_name <<" FAILED."<<std::endl;
        std::cout << std::endl;
        return;
    }
    std::cout<<test_name<<" SUCCEEDED."<<std::endl;
    std::cout << std::endl;

}

bool cardConstructorTest()
{
    Gremlin gremlinCard;
    Witch witchCard;
    Dragon dragonCard;
    Treasure treasureCard;
    Well wellCard;
    Barfight barfightCard;
    Mana manaCard;
    Merchant merchantCard;
    if(dynamic_cast<Gremlin*>(&gremlinCard) == nullptr){
        return false;
    }
    if(dynamic_cast<Witch*>(&witchCard) == nullptr){
        return false;
    }
    if(dynamic_cast<Dragon*>(&dragonCard) == nullptr){
        return false;
    }
    if(dynamic_cast<Treasure*>(&treasureCard) == nullptr){
        return false;
    }
    if(dynamic_cast<Well*>(&wellCard) == nullptr){
        return false;
    }
    if(dynamic_cast<Barfight*>(&barfightCard) == nullptr){
        return false;
    }
    if(dynamic_cast<Mana*>(&manaCard) == nullptr){
        return false;
    }
    if(dynamic_cast<Merchant*>(&merchantCard) == nullptr){
        return false;
    }
    return true;
}

bool cardPrintsTest()
{
    Gremlin gremlinCard;
    Witch witchCard;
    Dragon dragonCard;

    Treasure treasureCard;
    Well wellCard;
    Barfight barfightCard;
    Mana manaCard;
    Merchant merchantCard;

    std::cout << gremlinCard << std::endl;
    std::cout << witchCard << std::endl;
    std::cout << dragonCard << std::endl;

    std::cout << treasureCard << std::endl;
    std::cout << wellCard << std::endl;
    std::cout << barfightCard << std::endl;
    std::cout << manaCard << std::endl;

    return true;
}

bool applyBattleEncounterTest()
{
    Ninja ninja("purpleHaze");
    Healer healer("voodooChild");
    Warrior warrior("theWatchtower");

    Gremlin gremlinCard;
    Witch witchCard;
    Dragon dragonCard;

    gremlinCard.applyEncounter(ninja);
    if(ninja.getHealth() != 100)
    {
        return false;
    }
    gremlinCard.applyEncounter(healer);
    if(healer.getHealth() != 100)
    {
        return false;
    }
    gremlinCard.applyEncounter(warrior);
    if(warrior.getHealth() != 100 && warrior.getLevel() != 2)
    {
        return false;
    }
    witchCard.applyEncounter(ninja);
    if(ninja.getHealth() != 89 && ninja.getForce() == 1)
    {
        return false;
    }
    witchCard.applyEncounter(healer);
    if(healer.getHealth() != 89 && healer.getForce() == 1)
    {
        return false;
    }
    witchCard.applyEncounter(warrior);
    if(warrior.getHealth() != 100)
    {
        return false;
    }
    dragonCard.applyEncounter(ninja);
    if(ninja.getHealth() != 0)
    {
        return false;
    }
    dragonCard.applyEncounter(healer);
    if(healer.getHealth() != 0)
    {
        return false;
    }
    dragonCard.applyEncounter(warrior);
    if(warrior.getHealth() != 0)
    {
        return false;
    }
    return true;
}

bool applyScenarioEncounterTests()
{
    Ninja ninja("purpleHaze");
    Healer healer("voodooChild");
    Warrior warrior("theWatchtower");

    Gremlin gremlinCard;
    Witch witchCard;
    Dragon dragonCard;

    Treasure treasureCard;
    Well wellCard;
    Barfight barfightCard;
    Mana manaCard;
    Merchant merchantCard;

    treasureCard.applyEncounter(ninja);
    if(ninja.getCoins() != 30)
    {
        return false;
    }
    treasureCard.applyEncounter(healer);
    if(healer.getCoins() != 20)
    {
        return false;
    }
    treasureCard.applyEncounter(warrior);
    if(warrior.getCoins() != 20)
    {
        return false;
    }
    wellCard.applyEncounter(ninja);
    if(ninja.getHealth() != 100)
    {
        return false;
    }
    wellCard.applyEncounter(healer);
    if(healer.getHealth() != 90)
    {
        return false;
    }
    wellCard.applyEncounter(warrior);
    if(warrior.getHealth() != 90)
    {
        return false;
    }
    barfightCard.applyEncounter(ninja);
    if(ninja.getHealth() != 92)
    {
        return false;
    }
    barfightCard.applyEncounter(healer);
    if(healer.getHealth() != 82)
    {
        return false;
    }
    barfightCard.applyEncounter(warrior);
    if(warrior.getHealth() != 90)
    {
        return false;
    }
    manaCard.applyEncounter(ninja);
    if(ninja.getHealth() != 92)
    {
        return false;
    }
    manaCard.applyEncounter(healer);
    if(healer.getHealth() != 100)
    {
        return false;
    }
    manaCard.applyEncounter(warrior);
    if(warrior.getHealth() != 90)
    {
        return false;
    }
    merchantCard.applyEncounter(ninja);
    merchantCard.applyEncounter(healer);
    merchantCard.applyEncounter(warrior);
    merchantCard.applyEncounter(ninja);
    merchantCard.applyEncounter(healer);
    merchantCard.applyEncounter(warrior);
    merchantCard.applyEncounter(ninja);
    merchantCard.applyEncounter(healer);
    merchantCard.applyEncounter(warrior);
    return true;
}

int main(){
    run_test(cardConstructorTest, "cardConstructorTest");
    run_test(cardPrintsTest, "cardPrintsTest");
    run_test(applyBattleEncounterTest, "applyBattleEncounterTest");
    run_test(applyScenarioEncounterTests, "applyScenarioEncounterTests");
    return 0;
}