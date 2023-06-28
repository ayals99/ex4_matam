#include "Mtmchkin.h"
#include "Exception.h"
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
char const SPACE = ' ';

std::unique_ptr<LeaderBoard> createLeaderBoard(int numberOfPlayers);
Player* readAndCreatePlayer();
std::unique_ptr<Player> findFirstPlayer(std::unique_ptr<LeaderBoard>& leaderBoard);
Player* createPlayer(const std::string &playerName, const std::string &playerClass);
std::unique_ptr<Deck> createDeck(const std::string &fileName);
Card* getCardFromLine(const std::string &line, int lineCounter);
std::string readAndCheckValidation();
std::string trim(const std::string &str);
int readNumberOfPlayers();
int numberOfWordsInLine(const std::string& line);
void playNextCard(std::unique_ptr<Deck>& deck, Player* currentPlayer);
void pushBackBeforeLosers(std::unique_ptr<Player>& currentPlayer, std::unique_ptr<LeaderBoard>& leaderBoard);
void pushWinner(std::unique_ptr<Player>& currentPlayer, std::unique_ptr<LeaderBoard>& leaderBoard);
bool isPlayerClassValid(const std::string& playerClass);
bool isPlayerNameValid(const std::string& playerName);
bool isNumberOfPlayersValid(int numberOfPlayers);


Mtmchkin::Mtmchkin(const std::string& fileName) : m_numberOfRounds(0){
    printStartGameMessage();
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
        m_numberOfPlayers = readNumberOfPlayers();
        m_numberOfPlayersLeft = m_numberOfPlayers;
        m_leaderBoard = createLeaderBoard(m_numberOfPlayers);
    }
    catch (std::exception& e){
        throw e;
    }
}

std::unique_ptr<LeaderBoard> createLeaderBoard(int numberOfPlayers)
{
    // Create a unique_ptr to LeaderBoard
    std::unique_ptr<LeaderBoard> leaderBoard(new LeaderBoard());
    for(int i = 0; i < numberOfPlayers; ++i)
    {
        std::unique_ptr<Player> player(readAndCreatePlayer());
        leaderBoard->push_back(std::move(player));
    }
    return leaderBoard;
}


void Mtmchkin::playRound() {
    if (isGameOver()) {
        throw InvalidPlay();
    }
    ++m_numberOfRounds;
    printRoundStartMessage(m_numberOfRounds);
    int amountPlaying = m_numberOfPlayersLeft;
    for (int i = 0; i < amountPlaying; ++i) {
        std::unique_ptr<Player> currentPlayer = findFirstPlayer(m_leaderBoard);
        printTurnStartMessage(currentPlayer->getName());
        playNextCard(m_deckOfCards, currentPlayer.get());
        if (currentPlayer->won()) {
            pushWinner(currentPlayer, m_leaderBoard);
            m_numberOfPlayersLeft--;
        } else {
            if (currentPlayer->dead()) {
                m_numberOfPlayersLeft--;
            }
            pushBackBeforeLosers(currentPlayer, m_leaderBoard);
        }
        if (isGameOver()) {
            printGameEndMessage();
        }
    }
}

std::unique_ptr<Player> findFirstPlayer(std::unique_ptr<LeaderBoard>& leaderBoard) {
    for (LeaderBoard::iterator playerIterator = leaderBoard->begin();
         playerIterator != leaderBoard->end();
         playerIterator++){
        if ((*playerIterator)->isInGame()){
            std::unique_ptr<Player> firstPlayer = std::move(*playerIterator);
            leaderBoard->erase(playerIterator);
            return firstPlayer;
        }
    }
    throw NoPlayersInGame();
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

void pushWinner(std::unique_ptr<Player>& currentPlayer, std::unique_ptr<LeaderBoard>& leaderBoard) {
    LeaderBoard::iterator playerIterator = leaderBoard->begin();
    while (playerIterator != leaderBoard->end()) {
        if ((*playerIterator)->won()) {
            playerIterator++;
        } else {
            leaderBoard->insert(playerIterator, std::move(currentPlayer));
            return;
        }
    }
    leaderBoard->push_back(std::move(currentPlayer));
}


void pushBackBeforeLosers(std::unique_ptr<Player>& currentPlayer, std::unique_ptr<LeaderBoard>& leaderBoard) {
    LeaderBoard::iterator playerIterator = leaderBoard->begin();
    while (playerIterator != leaderBoard->end()) {
        if ((*playerIterator)->dead()) {
            leaderBoard->insert(playerIterator, std::move(currentPlayer));
            return;
        }
        playerIterator++;
    }
    leaderBoard->push_back(std::move(currentPlayer));
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

    if (deck->size() < MIN_NUMBER_OF_CARDS) {
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
    size_t first = str.find_first_not_of(SPACE);
    if (first == std::string::npos) {
        return "";
    }
    size_t last = str.find_last_not_of(SPACE);
    return str.substr(first, last - first + 1);
}


void readCurrentLineAndValidate(std::string& inputLine, bool& isNameValid, bool& isClassValid, bool& isLineValid,
                                std::string& playerName,std::string& playerClass){
    std::getline(std::cin, inputLine);
    std::string trimmedLine = trim(inputLine);
    playerName = trim(trimmedLine.substr(0, trimmedLine.find(SPACE)));
    playerClass = trim(trimmedLine.substr(trimmedLine.find(SPACE) + 1));
    isNameValid = isPlayerNameValid(playerName);
    isClassValid = isPlayerClassValid(playerClass);
    isLineValid = numberOfWordsInLine(trimmedLine) <= MAX_WORDS_IN_LINE;
}

std::string readAndCheckValidation() {
    printInsertPlayerMessage();
    std::string inputLine;
    bool isNameValid = false;
    bool isClassValid = false;
    bool isLineValid = false;
    std::string playerName;
    std::string playerClass;
    readCurrentLineAndValidate(inputLine, isNameValid, isClassValid, isLineValid, playerName, playerClass);
    while (!isNameValid || !isClassValid || !isLineValid)
    {
        if (!isLineValid) {
            printInvalidInput();
        }
        else if (!isNameValid) {
            printInvalidName();
        }
        else {
            printInvalidClass();
        }
        readCurrentLineAndValidate(inputLine, isNameValid, isClassValid, isLineValid, playerName, playerClass);
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
    int numberOfPlayers = 0;
    while (!isNumberOfPlayersValid(numberOfPlayers)) {
        printEnterTeamSizeMessage();
        std::getline(std::cin, inputLine);
        try{
            numberOfPlayers = std::stoi(inputLine);
        }catch(std::exception& e){
            printInvalidTeamSize();
            continue;
        }
        if (!isNumberOfPlayersValid(numberOfPlayers)) {
            printInvalidTeamSize();
        }
    }
    return numberOfPlayers;
}

bool isNumberOfPlayersValid(int numberOfPlayers) {
    return numberOfPlayers >= MIN_NUMBER_OF_PLAYERS &&
           numberOfPlayers <= MAX_NUMBER_OF_PLAYERS;
}