#include "Mtmchkin.h"

leaderboard& createLeaderBoard();


explicit Mtmchkin(const std::string &fileName){
    try{
        m_deckOfCards = createDeck(fileName);
    }
    catch (std::exception& e){
        throw;
    }
    try{
        m_leaderBoard = createLeaderBoard();
    }
    catch (std::exception& e){
        throw;
    }



}


leaderboard& createLeaderBoard()
{
    int numberOfPlayers = readNumberOfPlayers();
}

