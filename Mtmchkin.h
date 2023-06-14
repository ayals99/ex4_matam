#ifndef MTMCHKIN_H_
#define MTMCHKIN_H_

typdef std::vector<shared_pointer<Card>> deck;
typdef std::vector<shared_pointer<Player>> leaderboard;

class Mtmchkin{

private:
    deck m_deckOfCards;
    leaderboard m_leaderBoard;
    int m_numberOfRounds;
    int m_numberOfPlayers;

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

void Mtmchkin::playRound() {
    //
}

bool Mtmchkin::isGameOver() const {
    // loop through the leaderboard and check if there is a player who is still playing

}

Mtmchkin::Mtmchkin(const std::string& fileName) : m_numberOfRounds(0){
    // 1. read the file and create the deck, which is a vector of pointers to cards
    m_deckOfCards = createDeck(fileName); // Needs a function readFile() which reads the file and returns a vector of cards

    m_numberOfPlayers = receiveNumberOfPlayers(); // asks the user for input, the number of players

    // 2. Create a leaderboard which is a vector of pointers to players
    m_leaderBoard = createLeaderBoard(numberOfPlayers); // Needs a function createLeaderBoard() which creates a vector of players
}

int Mtmchkin::getNumberOfRounds() const {
    return m_numberOfRounds;
}


#endif /* MTMCHKIN_H_ */
