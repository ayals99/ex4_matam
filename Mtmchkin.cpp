#include "Mtmchkin.h"

leaderboard& createLeaderBoard();
int readNumberOfPlayers();

typedef std::shared_ptr<Player> PlayerPointer;

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
    LeaderBoard* leaderBoard = new LeaderBoard();
    for(int i = 0; i < numberOfPlayers; ++i){



        }
    }
}

