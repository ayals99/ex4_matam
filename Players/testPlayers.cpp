#include <string>
#include <iostream>
#include <functional>


#include "Player.h"
#include "Ninja.h"
#include "Healer.h"
#include "Warrior.h"

void run_test(std::function<bool()> test, std::string test_name){
    if(!test()){
        std::cout<< test_name <<" FAILED."<<std::endl;
        std::cout << std::endl;
        return;
    }
    std::cout<<test_name<<" SUCCEEDED."<<std::endl;
    std::cout << std::endl;

}

bool playersPrintsTest()
{
    Ninja player1("Itay");
    Warrior player2("Efrat");
    Healer player3("Jimmy");
    std::cout << player1 << std::endl << player2 << std::endl << player3
         << std::endl;
    return true;
}

bool playerConstructorTest()
{
    Ninja player1("Itay");
    Warrior player2("Efrat");
    Healer player3("Jimmy");
    return true;
}

bool playerGetJobTest()
{
    Ninja player1("Itay");
    if(player1.getPlayerJob() != "Ninja"){
        return false;
    }
    Warrior player2("Efrat");
    if(player2.getPlayerJob() != "Warrior"){
        return false;
    }
    Healer player3("Jimmy");
    if(player3.getPlayerJob() != "Healer"){
        return false;
    }
    return true;
}

bool playerGetCoinsTest(){
    Ninja player1("Itay");
    if(player1.getCoins() != INITIAL_COINS){
        return false;
    }
    Warrior player2("Efrat");
    if(player2.getCoins() != INITIAL_COINS){
        return false;
    }
    Healer player3("Jimmy");
    if(player3.getCoins() != INITIAL_COINS){
        return false;
    }

    player1.addCoins(3);
    if(player1.getCoins() != INITIAL_COINS + 6){
        return false;
    }
    player2.addCoins(100);
    if(player2.getCoins() != INITIAL_COINS + 100){
        return false;
    }

    player3.addCoins(0);
    if(player3.getCoins() != INITIAL_COINS){
        return false;
    }

//    player3.addCoins(-1);
//    if(player3.getCoins() != INITIAL_COINS){
//        return false;
//    }

    return true;
}

bool playerTestLevelUp()
{
    Ninja player1("Itay");
    if(player1.getLevel() != INITIAL_LEVEL){ // level is 1
        return false;
    }
    player1.levelUp();

    if(player1.getLevel() != INITIAL_LEVEL + 1){ // level is now 2
        return false;
    }

    for(int i = 0; i < 10; i++){
        player1.levelUp();
    }

    if(player1.getLevel() != MAXIMAL_LEVEL){ // level is now 10
        return false;
    }
    return true;
}

bool testPlayerHealthPoints(){
    Healer player1("Itay");
    player1.heal(20);
    if(player1.getHealth() != MAX_HP){
        return false;
    }
    player1.heal(-1);
    if(player1.getHealth() != MAX_HP){
        return false;
    }
    player1.damage(200);
    if(player1.getHealth() != MINIMAL_HEALTH){
        return false;
    }
    player1.heal(1);
    if(player1.getHealth() != 2){
        return false;
    }

    player1.heal(10000);
    if(player1.getHealth() != MAX_HP){
        return false;
    }

    player1.setDead();
    if(player1.getHealth() != MINIMAL_HEALTH){
        return false;
    }

    Ninja player2("Boris");
    if(player2.getHealth() != MAX_HP){
        return false;
    }

    player2.damage(20);

    if(player2.getHealth() != 80){
        return false;
    }

    player2.heal(5);
    if(player2.getHealth() != 85){
        return false;
    }

    player2.damage(100);
    if(player2.getHealth() != MINIMAL_HEALTH){
        return false;
    }

    player2.heal(10);
    if(player2.getHealth() != MINIMAL_HEALTH){
        return false;
    }

    player2.setDead();
    if(player2.getHealth() != MINIMAL_HEALTH){
        return false;
    }

    return true;
}


bool testGetName(){
    Ninja player1("Itay");
    if(player1.getName() != "Itay"){
        return false;
    }

    Healer player2("Boris");
    if (player2.getName() != "Boris"){
        return false;
    }

    Warrior player3("Efrat");
    if (player3.getName() != "Efrat"){
        return false;
    }

    return true;

}

bool testBuff(){
    Warrior player1("Itay");
    if(player1.getForce() != 5){
        return false;
    }
    player1.buff(10);
    if(player1.getForce() != 15){
        return false;
    }

    player1.buff(-1);

    if(player1.getForce() != 15){
        return false;
    }

    player1.buff(100);
    if(player1.getForce() != 115){
        return false;
    }

    player1.loseOneForce();
    if(player1.getForce() != 114){
        return false;
    }

    Healer player2("Boris");
    if(player2.getForce() != 5){
        return false;
    }
    player2.buff(10);
    if(player2.getForce() != 15){
        return false;
    }

    player2.buff(-1);
    if (player2.getForce() != 15){
        return false;
    }

    for(int i = 0; i < 20; ++i){
        player2.loseOneForce();
    }

    if(player2.getForce() != 0){
        return false;
    }

    return true;

}

bool playerInGameTest(){
    Warrior player1("Itay");
    Healer player2("Boris");
    Ninja player3("Efrat");

    if(! player1.isInGame()){
        return false;
    }

    if(! player2.isInGame()){
        return false;
    }

    if(! player3.isInGame()){
        return false;
    }

    player1.setDead();
    if(player1.isInGame()){
        return false;
    }

    for(int i = 0; i< 10; ++i){
        player2.levelUp();
    }

    if(player2.isInGame()){
        return false;
    }

    if(player3.getLevel() != 1){
        return false;
    }

    for(int i = 0; i < 8; ++i){
        player3.levelUp();
        if (!player3.isInGame()) {
            return false;
        }
    }

    if(player3.getLevel() != 9){
        return false;
    }

    player3.levelUp();
    if (player3.isInGame()) {
        return false;
    }

    return true;
}

bool coinsTest(){
    Ninja player1("purpleHaze");
    Healer player2("voodooChild");
    Warrior player3("theWatchtower");

    if(player1.getCoins() != 10){
        return false;
    }
    if(player2.getCoins() != 10){
        return false;
    }
    if(player3.getCoins() != 10){
        return false;
    }

    if (player1.pay(100)){
        return false;
    }

    if (player1.getCoins() != 10){
        return false;
    }

    player2.addCoins(2);
    if(player2.getCoins() != 12){
        return false;
    }

    player2.pay(14);
    if(player2.getCoins() != 12) {
        return false;
    }

    if(player1.getCoins() != 10){
        return false;
    }
    player1.addCoins(2);
    if(player1.getCoins() != 14){
        return false;
    }
    player1.pay(14);
    if(player1.getCoins() != MINIMUM_COINS){
        return false;
    }


    player3.addCoins(150);
    if(player3.getCoins() != 160){
        return false;
    }

    return true;
}




bool playersPrintsTestWithReference()
{

    Ninja ninja("Itay");
    Warrior warrior("Efrat");
    Healer healer("Jimmy");
    Player& player1 = ninja;
    Player& player2 = warrior;
    Player& player3 = healer;

    std::cout << player1 << std::endl << player2 << std::endl << player3
              << std::endl;
    return true;


}

bool playerConstructorTestWithReference()
{
    Ninja ninja("Itay");
    Warrior warrior("Efrat");
    Healer healer("Jimmy");
    Player& player1 = ninja;
    Player& player2 = warrior;
    Player& player3 = healer;
    return true;
}

bool playerGetJobTestWithReference()
{
    Ninja ninja("Itay");

    Player& player1 = ninja;


    if(player1.getPlayerJob() != "Ninja"){
        return false;
    }
    Warrior warrior("Efrat");
    Player& player2 = warrior;
    if(player2.getPlayerJob() != "Warrior"){
        return false;
    }

    Healer healer("Jimmy");
    Player& player3 = healer;
    if(player3.getPlayerJob() != "Healer"){
        return false;
    }
    return true;
}

bool playerGetCoinsTestWithReference(){
    Ninja ninja("Itay");
    Warrior warrior("Efrat");
    Healer healer("Jimmy");
    Player& player1 = ninja;
    Player& player2 = warrior;
    Player& player3 = healer;
    if(player1.getCoins() != INITIAL_COINS){
        return false;
    }
    if(player2.getCoins() != INITIAL_COINS){
        return false;
    }
    if(player3.getCoins() != INITIAL_COINS){
        return false;
    }

    player1.addCoins(3);
    if(player1.getCoins() != INITIAL_COINS + 6){
        return false;
    }
    player2.addCoins(100);
    if(player2.getCoins() != INITIAL_COINS + 100){
        return false;
    }

    player3.addCoins(0);
    if(player3.getCoins() != INITIAL_COINS){
        return false;
    }

//    player3.addCoins(-1);
//    if(player3.getCoins() != INITIAL_COINS){
//        return false;
//    }

    return true;
}

bool playerTestLevelUpWithReference()
{
    Ninja ninja("Itay");
    Warrior warrior("Efrat");
    Healer healer("Jimmy");
    Player& player1 = ninja;
    Player& player2 = warrior;
    Player& player3 = healer;
    if(player1.getLevel() != INITIAL_LEVEL){ // level is 1
        return false;
    }
    player1.levelUp();

    if(player1.getLevel() != INITIAL_LEVEL + 1){ // level is now 2
        return false;
    }

    for(int i = 0; i < 10; i++){
        player1.levelUp();
    }

    if(player1.getLevel() != MAXIMAL_LEVEL){ // level is now 10
        return false;
    }

    player2.levelUp();
    if(player2.getLevel() != INITIAL_LEVEL + 1){ // level is now 2
        return false;
    }

    player3.levelUp();
    if(player3.getLevel() != INITIAL_LEVEL + 1){ // level is now 2
        return false;
    }

    for(int i = 0; i < 100; i++){
        player3.levelUp();
    }
    if(player3.getLevel() != MAXIMAL_LEVEL){
        return false;
    }

    return true;
}

bool testPlayerHealthPointsWithReference(){
    Healer healer("Jimmy");
    Ninja ninja("Boris");
    Player& player1 = healer;
    Player& player2 = ninja;

    player1.heal(20);
    if(player1.getHealth() != MAX_HP){
        return false;
    }
    player1.heal(-1);
    if(player1.getHealth() != MAX_HP){
        return false;
    }
    player1.damage(200);
    if(player1.getHealth() != MINIMAL_HEALTH){
        return false;
    }
    player1.heal(1);
    if(player1.getHealth() != 2){
        return false;
    }

    player1.heal(10000);
    if(player1.getHealth() != MAX_HP){
        return false;
    }

    player1.setDead();
    if(player1.getHealth() != MINIMAL_HEALTH){
        return false;
    }

    if(player2.getHealth() != MAX_HP){
        return false;
    }

    player2.damage(20);

    if(player2.getHealth() != 80){
        return false;
    }

    player2.heal(5);
    if(player2.getHealth() != 85){
        return false;
    }

    player2.damage(100);
    if(player2.getHealth() != MINIMAL_HEALTH){
        return false;
    }

    player2.heal(10);
    if(player2.getHealth() != MINIMAL_HEALTH){
        return false;
    }

    player2.setDead();
    if(player2.getHealth() != MINIMAL_HEALTH){
        return false;
    }

    return true;
}


bool testGetNameWithReference(){

    Ninja ninja("Itay");
    Player& player1 = ninja;

    if(player1.getName() != "Itay"){
        return false;
    }

    Healer healer("Boris");
    Player& player2 = healer;
    if (player2.getName() != "Boris"){
        return false;
    }

    Warrior warrior("Efrat");
    Player& player3 = warrior;
    if (player3.getName() != "Efrat"){
        return false;
    }

    return true;

}

bool testBuffWithReference(){
    Warrior warrior("Itay");
    Player& player1 = warrior;
    if(player1.getForce() != 5){
        return false;
    }
    player1.buff(10);
    if(player1.getForce() != 15){
        return false;
    }

    player1.buff(-1);

    if(player1.getForce() != 15){
        return false;
    }

    player1.buff(100);
    if(player1.getForce() != 115){
        return false;
    }

    player1.loseOneForce();
    if(player1.getForce() != 114){
        return false;
    }

    Healer healer("Boris");
    Player& player2 = healer;
    if(player2.getForce() != 5){
        return false;
    }
    player2.buff(10);
    if(player2.getForce() != 15){
        return false;
    }

    player2.buff(-1);
    if (player2.getForce() != 15){
        return false;
    }

    for(int i = 0; i < 20; ++i){
        player2.loseOneForce();
    }

    if(player2.getForce() != 0){
        return false;
    }

    return true;

}

bool playerInGameTestWithReference(){
    Warrior warrior("Itay");
    Healer healer("Boris");
    Ninja ninja("Efrat");
    Player& player1 = warrior;
    Player& player2 = healer;
    Player& player3 = ninja;

    if(! player1.isInGame()){
        return false;
    }

    if(! player2.isInGame()){
        return false;
    }

    if(! player3.isInGame()){
        return false;
    }

    player1.setDead();
    if(player1.isInGame()){
        return false;
    }

    for(int i = 0; i< 10; ++i){
        player2.levelUp();
    }

    if(player2.isInGame()){
        return false;
    }

    if(player3.getLevel() != 1){
        return false;
    }

    for(int i = 0; i < 8; ++i){
        player3.levelUp();
        if (!player3.isInGame()) {
            return false;
        }
    }

    if(player3.getLevel() != 9){
        return false;
    }

    player3.levelUp();
    if (player3.isInGame()) {
        return false;
    }

    return true;
}

bool coinsTestWithReference(){
    Ninja ninja("purpleHaze");
    Healer healer("voodooChild");
    Warrior warrior("theWatchtower");

    Player& player1 = ninja;
    Player& player2 = healer;
    Player& player3 = warrior;

    if(player1.getCoins() != 10){
        return false;
    }
    if(player2.getCoins() != 10){
        return false;
    }
    if(player3.getCoins() != 10){
        return false;
    }

    if (player1.pay(100)){
        return false;
    }

    if (player1.getCoins() != 10){
        return false;
    }

    player2.addCoins(2);
    if(player2.getCoins() != 12){
        return false;
    }

    player2.pay(14);
    if(player2.getCoins() != 12) {
        return false;
    }

    if(player1.getCoins() != 10){
        return false;
    }
    player1.addCoins(2);
    if(player1.getCoins() != 14){
        return false;
    }
    player1.pay(14);
    if(player1.getCoins() != MINIMUM_COINS){
        return false;
    }


    player3.addCoins(150);
    if(player3.getCoins() != 160){
        return false;
    }

    return true;
}

int main(){

    /** Tests with Player */
    run_test(playerConstructorTest,"playerConstructorTest");
    run_test(playersPrintsTest,"playersPrintsTest");
    run_test(playerGetJobTest,"playerGetJobTest");
    run_test(playerGetCoinsTest,"playerGetCoinsTest");
    run_test(playerTestLevelUp,"playerTestLevelUp");
    run_test(testPlayerHealthPoints,"testPlayerHealthPoints");
    run_test(testGetName,"testGetName");
    run_test(testBuff,"testBuff");
    run_test(playerInGameTest, "inGameTest");
    run_test(coinsTest, "coinsTest");

    /** Tests with Player& */
    run_test(testGetNameWithReference,"testGetNameWithReference");
    run_test(testBuffWithReference,"testBuffWithReference");
    run_test(playerInGameTestWithReference,"playerInGameTestWithReference");
    run_test(coinsTestWithReference,"coinsTestWithReference");
    run_test(testPlayerHealthPointsWithReference,"testPlayerHealthPointsWithReference");
    run_test(playerGetCoinsTestWithReference,"playerGetCoinsTestWithReference");
    run_test(playerTestLevelUpWithReference,"playerTestLevelUpWithReference");
    run_test(playerGetJobTestWithReference,"playerGetJobTestWithReference");
    run_test(playerConstructorTestWithReference, "playerConstructorTestWithReference");
    run_test(playersPrintsTestWithReference,"playersPrintsTestWithReference");

    return 0;
}