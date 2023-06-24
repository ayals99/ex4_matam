#ifndef EX4_MATAM_EXCEPTION_H
#define EX4_MATAM_EXCEPTION_H

#include <stdexcept>
#include <string>
#include <iostream>

class invalidPlay : std::exception {
public:
    const char* what() const noexcept override{
        return "Mtmchkin playing error: Invalid play was attempted. Game is over";
    }

};

class noPlayersInGame : std::exception {
public:
    const char* what() const noexcept override{
        return "Mtmchkin playing error: No players in the game";
    }
};

class DeckFileNotFound : std::exception {
public:
    const char* what() const noexcept override{
        return "Deck File Error: File not found";
    }
};

class DeckFileFormatError : public std::exception {
private:
    std::runtime_error m_runtimeError;
public:
    explicit DeckFileFormatError(int lineNum) :
    m_runtimeError("Deck File Error: File format error in line " + std::to_string(lineNum)) {
    }
    const char* what() const noexcept override{
        return m_runtimeError.what();
    }
};

class DeckFileInvalidSize : public std::exception {
public:
    const char* what() const noexcept override{
        return "Deck File Error: Deck size is invalid";
    }
};

#endif //EX4_MATAM_EXCEPTION_H