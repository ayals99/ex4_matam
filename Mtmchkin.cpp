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
char const SPACE = ' ';

LeaderBoard* createLeaderBoard(int numberOfPlayers);
Player* readAndCreatePlayer();
Player* findFirstPlayer(LeaderBoard* m_leaderBoard);
Player* createPlayer(const std::string &playerName, const std::string &playerClass);
std::unique_ptr<Deck> createDeck(const std::string &fileName);
Card* getCardFromLine(const std::string &line, int lineCounter);
std::string readAndCheckValidation();
std::string trim(const std::string &str);
int readNumberOfPlayers();
int numberOfWordsInLine(const std::string& line);
void playNextCard(std::unique_ptr<Deck>& deck, Player* currentPlayer);
void pushWinner(Player* currentPlayer, LeaderBoard* leaderBoard);
void pushBackBeforeLosers(Player* currentPlayer, LeaderBoard* leaderBoard);
bool isPlayerClassValid(const std::string& playerClass);
bool isPlayerNameValid(const std::string& playerName);
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
    if (isGameOver()) {
        throw invalidPlay();
    }
    ++m_numberOfRounds;
    printRoundStartMessage(m_numberOfRounds);
    int amountPlaying = m_numberOfPlayersLeft;
    for (int i = 0; i < amountPlaying; ++i) {
        Player *currentPlayer = findFirstPlayer(m_leaderBoard);
        printTurnStartMessage(currentPlayer->getName());
        playNextCard(m_deckOfCards, currentPlayer);
        if (currentPlayer->won()) {
            pushWinner(currentPlayer, m_leaderBoard);
            m_numberOfPlayersLeft--;
        } else {
            if (currentPlayer->dead()) {
                m_numberOfPlayersLeft--;
            }
            pushBackBeforeLosers(currentPlayer, m_leaderBoard);
        }
        //maybe we print the end game message out of here??
        if (isGameOver()) {
            printGameEndMessage();
        }
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

void playNextCard(std::unique_ptr<Deck>& deck, Player* currentPlayer){
    std::unique_ptr<Card>& currentCard = deck->front();
    currentCard->applyEncounter(*currentPlayer);
    deck->push(std::move(currentCard));
    deck->pop();
}

bool Mtmchkin::isGameOver() const {
    return m_numberOfPlayersLeft == 0;
}

void pushWinner(Player* currentPlayer, LeaderBoard* leaderBoard) {
    auto playerIterator = leaderBoard->begin();
    while (playerIterator != leaderBoard->end()) {
        if ((*playerIterator)->won()) {
            playerIterator++;
        } else {
            leaderBoard->insert(playerIterator, currentPlayer);
            return;
        }
    }
    leaderBoard->push_back(currentPlayer);
}

void pushBackBeforeLosers(Player* currentPlayer, LeaderBoard* leaderBoard) {
    auto playerIterator = leaderBoard->begin();
    while (playerIterator != leaderBoard->end()) {
        if ((*playerIterator)->dead()) {
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

std::unique_ptr<Deck> createDeck(const std::string &fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        throw DeckFileNotFound();
    }
    std::unique_ptr<Deck> deck(new Deck());
    std::string line;
    int lineCounter = 1;
    while (std::getline(file, line)) {
        try {
            Card* card = getCardFromLine(line, lineCounter);
            deck->push(std::unique_ptr<Card>(card));
            lineCounter++;
        } catch (std::bad_alloc &e) {
            throw e;
        } catch (const DeckFileFormatError &e) {
            throw DeckFileFormatError(lineCounter);
        }
    }
    if (lineCounter < MIN_NUMBER_OF_CARDS) {
        throw DeckFileInvalidSize();
    }
    return deck;
}


Card* getCardFromLine(const std::string &line, int lineCounter) {
    Card* card = nullptr;
    if (line == "Witch") {
        card = new Witch();
    } else if (line == "Barfight") {
        card = new Barfight();
    } else if (line == "Dragon") {
        card = new Dragon();
    } else if (line == "Mana") {
        card = new Mana();
    } else if (line == "Gremlin") {
        card = new Gremlin();
    } else if (line == "Merchant") {
        card = new Merchant();
    } else if (line == "Well") {
        card = new Well();
    } else if (line == "Treasure") {
        card = new Treasure();
    }
    if (card == nullptr) {
        throw DeckFileFormatError(lineCounter);
    }
    return card;
}


Player* readAndCreatePlayer()
{
    Player* player;
    std::string inputLine = readAndCheckValidation();
    std::string playerName = inputLine.substr(0, inputLine.find(SPACE));
    std::string playerClass = inputLine.substr(inputLine.find(SPACE) + 1);
    try{
        player = createPlayer(playerName, playerClass);
    }
    catch(std::exception& e) {
        throw e;
    }
    return player;
}

std::string trim(const std::string &str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}

std::string readAndCheckValidation() {
    printInsertPlayerMessage();
    std::string inputLine;
    std::getline(std::cin, inputLine);
    std::string playerName = trim(inputLine.substr(0, inputLine.find(SPACE)));
    std::string playerClass = trim(inputLine.substr(inputLine.find(SPACE) + 1));
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
        std::getline(std::cin, inputLine);
        playerName = trim(inputLine.substr(0, inputLine.find(SPACE)));
        playerClass = trim(inputLine.substr(inputLine.find(SPACE) + 1));
        isnNameValid = isPlayerNameValid(playerName);
        isClassValid = isPlayerClassValid(playerClass);
        isLineValid = numberOfWordsInLine(inputLine) <= MAX_WORDS_IN_LINE;
    }
    return inputLine;
}


Player* createPlayer(const std::string &playerName, const std::string &playerClass) {
    if (playerClass == "Warrior") {
        return new Warrior(playerName);
    }
    else if (playerClass == "Ninja") {
        return new Ninja(playerName);
    }
    else if (playerClass == "Healer") {
        return new Healer(playerName);
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
    if (line.empty()) return 0;
    int numberOfWords = 0;
    bool lastCharWasSpace = true;
    for (char c: line) {
        if (c == SPACE) {
            lastCharWasSpace = true;
        } else if (lastCharWasSpace) {
            numberOfWords++;
            lastCharWasSpace = false;
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