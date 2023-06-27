#ifndef MTMCHKIN_H_
#define MTMCHKIN_H_


#include <memory>
#include <vector>
#include <queue>

#include "utilities.h"
#include "Cards/Card.h"

typedef std::queue<std::unique_ptr<Card>> Deck;
typedef std::vector<std::unique_ptr<Player>> LeaderBoard;

class Mtmchkin{

private:
    std::unique_ptr<Deck> m_deckOfCards;
    std::unique_ptr<LeaderBoard> m_leaderBoard;
    int m_numberOfRounds;
    int m_numberOfPlayers;
    int m_numberOfPlayersLeft;

public:
    /*
    * C'tor of Mtmchkin class
    *
    * @param filename - a file which contains the cards of the deck.
    * @return
    *      A new instance of Mtmchkin.
    */
    explicit Mtmchkin(const std::string &fileName);
    
    /*
    * Play the next Round of the game - according to the instruction in the exercise document.
    *
    * @return
    *      void
    */
    void playRound();
    
    /*
    * Prints the leaderBoard of the game at a given stage of the game - according to the instruction in the exercise document.
    *
    * @return
    *      void
    */
    void printLeaderBoard() const;
    
    /*
    *  Checks if the game ended:
    *
    *  @return
    *          True if the game ended
    *          False otherwise
    */
    bool isGameOver() const;
    
	/*
    *  Returns the number of rounds played.
    *
    *  @return
    *          int - number of rounds played
    */
    int getNumberOfRounds() const;
};



#endif /* MTMCHKIN_H_ */