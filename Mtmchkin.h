#ifndef MTMCHKIN_H_
#define MTMCHKIN_H_


#include <memory>
#include "Exception.h"
#include "utilities.h"

typedef std::vector<std::shared_ptr<Card>> deck;
typedef std::vector<std::shared_ptr<Player>> leaderboard;

class Mtmchkin{

private:
    deck m_deckOfCards;
    leaderboard m_leaderBoard;
    int m_numberOfRounds;
    //int m_numberOfPlayers;

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

Player& findFirstPlayer(leaderboard m_leaderBoard){
    for (leaderboard::iterator i = m_leaderBoard.begin(); i != m_leaderBoard.end(); i++){
        if ( (*i)->isInGame() ){
            return **i;
        }
    }
    throw noPlayersInGame();
}

int countPlayersInGame(leaderboard m_leaderBoard){
    int counter = 0;
    for (leaderboard::iterator i = m_leaderBoard.begin(); i != m_leaderBoard.end(); i++){
        if ( (*i)->isInGame()){
         counter++;
        }
    }
    return counter;
}

void playNextCard(deck& m_deckOfCards, Player& currentPlayer){
    Card& currentCard = *(m_deckOfCards.front());
    currentCard.Card::applyEncounter(currentPlayer);
    m_deckOfCards.push_back(m_deckOfCards.front());
    deck::iterator iterator = m_deckOfCards.begin();
    m_deckOfCards.erase(iterator);
}

void Mtmchkin::playRound() {
    if(isGameOver()){
        throw invalidPlay();
    }
    ++m_numberOfRounds;
    printRoundStartMessage(m_numberOfRounds);
    int amountPlaying = countPlayersInGame(m_leaderBoard);
    for(int i = 0; i < amountPlaying; ++i){
        Player& currentPlayer = findFirstPlayer(m_leaderBoard);
        printTurnStartMessage(currentPlayer.getName());
        playNextCard(m_deckOfCards, currentPlayer);
    }
    if(isGameOver()){
        printGameEndMessage();
    }
}

bool Mtmchkin::isGameOver() const {
    if (countPlayersInGame(m_leaderBoard) == 0){
        return true;
    }
    return false;
}

Mtmchkin::Mtmchkin(const std::string& fileName) : m_numberOfRounds(0){
    // 1. read the file and create the deck, which is a vector of pointers to cards
    //TODO: implement createDeck()
    m_deckOfCards = createDeck(fileName); // Needs a function readFile() which reads the file and returns a vector of cards

    // TODO: implement receiveNumberOfPlayers()
    int numberOfPlayers = receiveNumberOfPlayers(); // asks the user for input, the number of players

    // TODO: implement createLeaderBoard()
    // 2. Create a leaderboard which is a vector of pointers to players
    m_leaderBoard = createLeaderBoard(numberOfPlayers); // Needs a function createLeaderBoard() which creates a vector of players
}

int Mtmchkin::getNumberOfRounds() const {
    return m_numberOfRounds;
}

void Mtmchkin::printLeaderBoard() const {
    printLeaderBoardStartMessage();
    int rankingCounter = 1;
    for (leaderboard::const_iterator i = m_leaderBoard.begin(); i != m_leaderBoard.end(); i++){
        printPlayerLeaderBoard(rankingCounter, **i);
        rankingCounter++;
    }
}


#endif /* MTMCHKIN_H_ */