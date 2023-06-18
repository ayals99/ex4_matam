#ifndef EX4_MATAM_CARD_H
#define EX4_MATAM_CARD_H

#include "../Players/Player.h"
#include "../Exception.h"
#include "../utilities.h"

class Card{
protected:
    std::string m_name;

public:
    explicit Card(std::string name) : m_name(name) {};

    Card(Card& other) = delete;
    Card() = delete;
    virtual ~Card() = default;

    virtual void getName() const = 0;
    virtual void applyEncounter(Player& player) const = 0;
};

#endif //EX4_MATAM_CARD_H
