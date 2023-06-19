#ifndef EX4_MATAM_CARD_H
#define EX4_MATAM_CARD_H

#include <utility>

#include "../Players/Player.h"
#include "../Exception.h"
#include "../utilities.h"

class Card{
protected:
    const std::string m_name;

public:
    explicit Card(std::string  name) : m_name(std::move(name)) {};

    Card(Card& other) = delete;
    Card() = delete;
    virtual ~Card() = default;

    //virtual void getName() const = 0;
    virtual void applyEncounter(Player& player) const = 0;

    virtual std::ostream& stringToPrint(std::ostream& os) const{
        printCardDetails(os, m_name);
        printEndOfCardDetails(os);
        return os;
    }
};

inline std::ostream& operator<<(std::ostream& os, const Card& card){
    return card.stringToPrint(os);
}
#endif //EX4_MATAM_CARD_H
