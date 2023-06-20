#include "Mtmchkin.h"
#include "Cards/Witch.h"
#include "Cards/Barfight.h"
#include "Cards/Dragon.h"
#include "Cards/Mana.h"
#include "Cards/Gremlin.h"
#include "Cards/Merchant.h"
#include "Cards/Well.h"
#include "Cards/Treasure.h"
#include "Players/Ninja.h"
#include "Players/Healer.h"
#include "Players/Warrior.h"
#include <fstream>

static int const MAX_NUMBER_OF_PLAYERS = 6;
static int const MIN_NUMBER_OF_PLAYERS = 2;
static int const MIN_NUMBER_OF_CARDS = 5;
static int const MAX_PLAYER_NAME_LENGTH = 15;
int const MAX_WORDS_IN_LINE = 2;
int const STRING_START_INDEX = 0;


typedef std::queue<Card*> Deck;
typedef std::vector<Player*> LeaderBoard;

LeaderBoard* createLeaderBoard(int numberOfPlayers);
int readNumberOfPlayers();
Player* readAndCreatePlayer();
Deck* createDeck(const std::string &fileName);
Player* findFirstPlayer(LeaderBoard* m_leaderBoard);
void playNextCard(Deck* deck, Player* currentPlayer);
void pushWinner(Player* currentPlayer, LeaderBoard* leaderBoard);
void pushBackBeforeLosers(Player* currentPlayer, LeaderBoard* leaderBoard);
Card* getCardFromLine(const std::string &line, int lineCounter);
Player* createPlayer(const std::string &playerName, const std::string &playerClass);
int numberOfWordsInLine(const std::string& line);
bool isPlayerClassValid(const std::string& playerClass);
bool isPlayerNameValid(const std::string& playerName);
std::string readAndCheckValidation();
bool isNumberOfPlayersValid(int numberOfPlayers);


Mtmchkin::Mtmchkin(const std::string& fileName) : m_numberOfRounds(0){
    try{
        m_deckOfCards = createDeck(fileName);
    }
    catch (std::bad_alloc &e) {
        throw e;
    }
    catch(const DeckFileFormatError& e) {
    throw e;
    }
    try{
        printStartGameMessage();
        m_numberOfPlayers = readNumberOfPlayers();
        m_numberOfPlayersLeft = m_numberOfPlayers;
        m_leaderBoard = createLeaderBoard(m_numberOfPlayers);
    }
    catch (std::exception& e){
        throw e;
    }
}

LeaderBoard* createLeaderBoard(int numberOfPlayers)
{
    //LeaderBoard* leaderBoard = new LeaderBoard();
    LeaderBoard* leaderBoard = new LeaderBoard();
    for(int i = 0; i < numberOfPlayers; ++i)
    {
        Player* player = readAndCreatePlayer();
        leaderBoard->push_back(player);
    }
    return leaderBoard;
}


void Mtmchkin::playRound() {
    if(isGameOver()){
        throw invalidPlay();
    }
    ++m_numberOfRounds;
    printRoundStartMessage(m_numberOfRounds);
    int amountPlaying = m_numberOfPlayersLeft;
    for(int i = 0; i < amountPlaying; ++i){
        Player* currentPlayer = findFirstPlayer(m_leaderBoard);
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

Player* findFirstPlayer(LeaderBoard* leaderBoard) {
    for (auto playerIterator = leaderBoard->begin();
    playerIterator != leaderBoard->end();
    playerIterator++){
        if ((*playerIterator)->isInGame()){
            Player* firstPlayer = *playerIterator;
            leaderBoard->erase(playerIterator);
            return firstPlayer;
        }
    }
    throw noPlayersInGame();
}

void playNextCard(Deck* deck, Player* currentPlayer){
    Card* currentCard = deck->front();
    deck->pop();
    currentCard->applyEncounter(*currentPlayer);
    deck->push(currentCard);
}

bool Mtmchkin::isGameOver() const {
    if (m_numberOfPlayersLeft == 0){
        return true;
    }
    return false;
}

void pushWinner(Player* currentPlayer, LeaderBoard* leaderBoard)
{
    auto playerIterator = leaderBoard->begin();
    while(playerIterator != leaderBoard->end())
    {
        if((*playerIterator)->won())
        {
            playerIterator++;
        } else
        {
            leaderBoard->insert(playerIterator, currentPlayer);
            return;
        }
    }
    leaderBoard->push_back(currentPlayer);
}

void pushBackBeforeLosers(Player* currentPlayer, LeaderBoard* leaderBoard)
{
    auto playerIterator = leaderBoard->begin();
    while(playerIterator != leaderBoard->end())
    {
        if((*playerIterator)->dead())
        {
            leaderBoard->insert(playerIterator, currentPlayer);
            return;
        }
        playerIterator++;
    }
    leaderBoard->push_back(currentPlayer);
}

int Mtmchkin::getNumberOfRounds() const {
    return m_numberOfRounds;
}

void Mtmchkin::printLeaderBoard() const {
    printLeaderBoardStartMessage();
    int rankingCounter = 1;
    for (const auto & i : *m_leaderBoard){
        printPlayerLeaderBoard(rankingCounter, *i);
        rankingCounter++;
    }
}

Deck* createDeck(const std::string &fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        throw DeckFileNotFound();
    }
    Deck *deck;
    try {
        deck = new Deck();
    }catch (std::bad_alloc &e) {
        file.close();
        throw e;
    }
    std::string line;
    int lineCounter = 1;
    Card *card;
    while (std::getline(file, line)) {
        try {
            card = getCardFromLine(line, lineCounter);
        }catch (std::bad_alloc &e) {
            file.close();
            delete deck;
            throw e;
        }
        catch(const DeckFileFormatError& e) {
            file.close();
            delete deck;
            throw DeckFileFormatError(lineCounter);
        }
        deck->push(card);
        lineCounter++;
    }
    if (lineCounter < MIN_NUMBER_OF_CARDS) {
        file.close();
        delete deck;
        throw DeckFileInvalidSize();
    }
    return deck;
}

Card* getCardFromLine(const std::string &line, int lineCounter) {
    if (line == "Witch") {
        Witch *witch = new Witch();
        return witch;
    }
    if (line == "Barfight") {
        Barfight *barfight = new Barfight();
        return barfight;
    }
    if (line == "Dragon") {
        Dragon *dragon = new Dragon();
        return dragon;
    }
    if (line == "Mana") {
        Mana *mana = new Mana();
        return mana;
    }
    if (line == "Gremlin") {
        Gremlin *gremlin = new Gremlin();
        return gremlin;
    }
    if (line == "Merchant") {
        Merchant *merchant = new Merchant();
        return merchant;
    }
    if (line == "Well") {
        Well *well = new Well();
        return well;
    }
    if (line == "Treasure") {
        Treasure *treasure = new Treasure();
        return treasure;
    }
    throw DeckFileFormatError(lineCounter);
}


Player* readAndCreatePlayer()
{
    Player* player;
    std::string inputLine = readAndCheckValidation();
    std::string playerName = inputLine.substr(0, inputLine.find(' '));
    std::string playerClass = inputLine.substr(inputLine.find(' ') + 1);
    try{
        player = createPlayer(playerName, playerClass);
    }
    catch(std::exception& e) {
        throw e;
    }
    return player;
}

std::string readAndCheckValidation() {
    std::string inputLine;
    printInsertPlayerMessage();
    std::getline(std::cin, inputLine);
    std::string playerName = inputLine.substr(0, inputLine.find(' '));
    std::string playerClass = inputLine.substr(inputLine.find(' ') + 1);
    bool isnNameValid = isPlayerNameValid(playerName);
    bool isClassValid = isPlayerClassValid(playerClass);
    bool isLineValid = numberOfWordsInLine(inputLine) <= MAX_WORDS_IN_LINE;
    while (!isnNameValid || !isClassValid || !isLineValid)
    {
        if (!isLineValid) {
            printInvalidInput();
        } else if (!isnNameValid) {
            printInvalidName();
        } else if (!isClassValid) {
            printInvalidClass();
        }
        printInsertPlayerMessage();
        std::getline(std::cin, inputLine);
        playerName = inputLine.substr(STRING_START_INDEX, inputLine.find(' '));
        playerClass = inputLine.substr(inputLine.find(' ') + 1);
        isnNameValid = isPlayerNameValid(playerName);
        isClassValid = isPlayerClassValid(playerClass);
        isLineValid = numberOfWordsInLine(inputLine) <= MAX_WORDS_IN_LINE;
    }
    return inputLine;
}

Player* createPlayer(const std::string &playerName, const std::string &playerClass) {
    if (playerClass == "Warrior") {
        Warrior *warrior = new Warrior(playerName);
        return warrior;
    }
    if (playerClass == "Ninja") {
        Ninja *ninja = new Ninja(playerName);
        return ninja;
    }
    if (playerClass == "Healer") {
        Healer *healer = new Healer(playerName);
        return healer;
    }
    throw std::invalid_argument("Invalid player class");
}

bool isPlayerNameValid(const std::string& playerName) {
    if (playerName.length() > MAX_PLAYER_NAME_LENGTH) {
        return false;
    }
    for (char c: playerName) {
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) {
            return false;
        }
    }
    return true;
}

bool isPlayerClassValid(const std::string& playerClass) {
    if (playerClass == "Warrior" || playerClass == "Ninja" ||
        playerClass == "Healer") {
        return true;
    }
    return false;
}

int numberOfWordsInLine(const std::string& line) {
    int numberOfWords = 0;
    for (char c: line) {
        if (c == ' ') {
            numberOfWords++;
        }
    }
    return numberOfWords;
}

int readNumberOfPlayers() {
    std::string inputLine;
    printEnterTeamSizeMessage();
    std::getline(std::cin, inputLine);
    int numberOfPlayers = std::stoi(inputLine);
    while (!isNumberOfPlayersValid(numberOfPlayers)) {
        printInvalidTeamSize();
        printEnterTeamSizeMessage();
        std::getline(std::cin, inputLine);
        numberOfPlayers = std::stoi(inputLine);
    }
    return numberOfPlayers;
}

bool isNumberOfPlayersValid(int numberOfPlayers) {
    return numberOfPlayers >= MIN_NUMBER_OF_PLAYERS &&
           numberOfPlayers <= MAX_NUMBER_OF_PLAYERS;
}