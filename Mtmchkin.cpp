#include "Mtmchkin.h"

typedef std::shared_ptr<Player> PlayerPointer;
typedef std::shared_ptr<Card> CardPointer;

LeaderBoard & createLeaderBoard(int numberOfPlayers);
int readNumberOfPlayers();
PlayerPointer readPlayerInfo();
Deck createDeck(const std::string &fileName);
PlayerPointer findFirstPlayer(LeaderBoard & m_leaderBoard);
void playNextCard(Deck& deck, PlayerPointer& currentPlayer);
void pushWinner(PlayerPointer& currentPlayer, LeaderBoard& leaderBoard);
void pushBackBeforeLosers(PlayerPointer& currentPlayer, LeaderBoard& leaderBoard);



Mtmchkin::Mtmchkin(const std::string& fileName) : m_numberOfRounds(0){
    try{
        m_deckOfCards = createDeck(fileName);
    }
    catch (std::exception& e){
        throw;
    }
    try{
        m_numberOfPlayers = readNumberOfPlayers();
        m_numberOfPlayersLeft = m_numberOfPlayers;
        m_leaderBoard = createLeaderBoard(m_numberOfPlayers);
    }
    catch (std::exception& e){
        throw;
    }
}


LeaderBoard& createLeaderBoard(int numberOfPlayers)
{

    //LeaderBoard* leaderBoard = new LeaderBoard();
    auto* leaderBoard = new LeaderBoard();
    for(int i = 0; i < numberOfPlayers; ++i)
    {
        PlayerPointer player = readPlayerInfo();
        leaderBoard->push_back(player);
    }
    return *leaderBoard;
}


void Mtmchkin::playRound() {
    if(isGameOver()){
        throw invalidPlay();
    }
    ++m_numberOfRounds;
    printRoundStartMessage(m_numberOfRounds);
    int amountPlaying = m_numberOfPlayersLeft;
    for(int i = 0; i < amountPlaying; ++i){
        PlayerPointer currentPlayer = findFirstPlayer(m_leaderBoard);
        printTurnStartMessage(currentPlayer->getName());
        playNextCard(m_deckOfCards, currentPlayer);
        if(currentPlayer->won())
        {
            pushWinner(currentPlayer, m_leaderBoard);
            m_numberOfPlayersLeft--;
            continue;
        }
        if(currentPlayer->dead()){
            m_numberOfPlayersLeft--;
        }
        pushBackBeforeLosers(currentPlayer, m_leaderBoard);
    }
    if(isGameOver()){
        printGameEndMessage();
    }
}

PlayerPointer findFirstPlayer(LeaderBoard& leaderBoard) {
    for (auto playerIterator = leaderBoard.begin();
    playerIterator != leaderBoard.end() || (*playerIterator)->isInGame();
    playerIterator++){
        if ((*playerIterator)->isInGame()){
            PlayerPointer firstPlayer = *playerIterator;
            leaderBoard.erase(playerIterator);
            return firstPlayer;
        }
    }
    throw noPlayersInGame();
}

void playNextCard(Deck& deck, PlayerPointer& currentPlayer){
    CardPointer currentCard = deck.front();
    deck.pop();
    currentCard->applyEncounter(*currentPlayer);
    deck.push(currentCard);
}

bool Mtmchkin::isGameOver() const {
    if (m_numberOfPlayersLeft == 0){
        return true;
    }
    return false;
}

void pushWinner(PlayerPointer& currentPlayer, LeaderBoard& leaderBoard)
{
    auto playerIterator = leaderBoard.begin();
    while(playerIterator != leaderBoard.end() || (*playerIterator)->won())
    {
        playerIterator++;
    }
    leaderBoard.insert(playerIterator, currentPlayer);
}

void pushBackBeforeLosers(PlayerPointer& currentPlayer, LeaderBoard& leaderBoard)
{
    auto playerIterator = leaderBoard.begin();
    while(playerIterator != leaderBoard.end() || (*playerIterator)->dead())
    {
        playerIterator++;
    }
    leaderBoard.insert(playerIterator, currentPlayer);
}


int Mtmchkin::getNumberOfRounds() const {
    return m_numberOfRounds;
}

void Mtmchkin::printLeaderBoard() const {
    printLeaderBoardStartMessage();
    int rankingCounter = 1;
    for (const auto & i : m_leaderBoard){
        printPlayerLeaderBoard(rankingCounter, *i);
        rankingCounter++;
    }
}
