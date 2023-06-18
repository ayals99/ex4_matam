#ifndef EX4_MATAM_CARD_H
#define EX4_MATAM_CARD_H

#include "../Players/Player.h"
#include "../Exception.h"
#include "../utilities.h"
#include <iostream>
#include <string>


class Card{
protected:
    const std::string m_name;

public:
    /**
     * C'tor of Card class
     *
     * @param name - The type of the card is its name.
     * @return
     *      A new instance of Card.
    */
    explicit Card(const std::string& name): m_name(name) {}

    /**
     * Copy C'tor of Card class
     *
     * @param other - The card to copy.
     * @return
     *      A new instance of Card.
    */
    Card(const Card& other) = default;

    /**
    * D'tor of Card class
    */
    virtual ~Card() = default;

    /**
     * @return
     *      The name of the card.
    */
    const std::string& getName() const
    {
        return m_name;
    }
    /**
     * Applies the card's effect on the player.
     *
     * @param player - The player to apply the card's effect on.
     * @return void
    */
    virtual void applyEncounter(Player& player) const = 0;

    /**
     * Prints the card's info.
     *
     * @param os - The output stream to print to.
     * @param card - The card to print.
     * @return void
    */
    friend std::ostream& operator<<(std::ostream& os, const Card& card)
    {
        printCardDetails(os, card.m_name);
        return os;
    }
};



#endif //EX4_MATAM_CARD_H
