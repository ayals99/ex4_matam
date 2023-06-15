#include <string>
#include <iostream>
#include <functional>
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <sstream>
#include <random>
#include <cstdio>
#include <fstream>
#include <cstring>

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

bool player()
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

int main(){
    run_test(playerConstructorTest,"playerConstructorTest");
    run_test(playersPrintsTest,"playersPrintsTest");
    run_test(playerGetJobTest,"playerGetJobTest");
    run_test(playerGetCoinsTest,"playerGetCoinsTest");
    return 0;
}