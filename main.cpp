#include "Mtmchkin.h"
#include <string>
#include <iostream>

int main(int argc, char** argv){
    if(argc < 1) {
        std::cout << "Wrong amount of arguments for program, expected 1, got " << argc << std::endl;
        return 0;
    }

    std::string deck_path = argv[1];
    try
    {
        Mtmchkin game(deck_path);
        while(!game.isGameOver()){
            game.playRound();
            game.printLeaderBoard();
        }
    }
    catch (std::exception &e)
    {
        std::cout << e.what();
    }
    return 0;
}