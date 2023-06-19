#ifndef EX4_MATAM_PLAYER_H
#define EX4_MATAM_PLAYER_H

#include <string>
#include "../HealthPoints.h"

static const int MAXIMAL_LEVEL = 10;
static const int MINIMUM_FORCE = 0;
static const int MINIMUM_COINS = 0;

static const int INITIAL_FORCE = 5;
static const int INITIAL_COINS = 10;
static const int INITIAL_LEVEL = 1;
static const int MAX_HP = 100;

class Player{

protected:
    std::string m_name; // shorter than 15 letters and no spaces
    int m_level; // 1-10
    int m_force; // >= 0
    HealthPoints m_health;
    int m_coins; // >=0

public:

    explicit Player(std::string& name);

    Player(Player& other) = delete;
    Player& operator=(Player& other) = delete;
    virtual ~Player() = default;

    /** Getters: **/
    std::string getName() const;
    int getLevel() const;
    int getForce () const;
    bool isInGame() const;
    bool dead() const;
    bool won() const;
    HealthPoints getHealth() const;
    int getCoins() const;
    virtual bool playerIsStronger(int opponentForce) const; // Determines who will win the battle. Override by warrior
    virtual const std::string& getPlayerJob() const = 0; // Pure virtual function


    /** Setters: **/

    /**
    * @param coinsToAdd - The amount of coins to add to the player.
     * @note: Ninja will override this in order to add twice the amount of coins
    * @return void
    */
    virtual void addCoins(int coinsToAdd);

    /**
     * @param hpToAdd - The amount of HP to add to the player.
     * @note: will be overridden by Healer to receive double HP
     * @return void
     */
    virtual void heal(int hpToAdd);

    /**
     * Reduces the player's HP by the given amount. If the damage is 0 or less, does nothing.
     * Only reduces the player's HP to 0, not below.
     * @param hpToReduce - The amount of HP to reduce from the player.
     * @return void
     */
    void damage(int hpToReduce);

    /**
     * @param forceToAdd - The amount of force to add to the player.
     * @return void
     */
    void buff(int forceToAdd);

    /**
     * @param coinsToPay - The amount of coins to pay.
     * @return true if the player has enough coins to pay. false otherwise.
     */
    bool pay(int coinsToPay);

    /**
     * Increases the players level by 1. If the player's level is 10, does nothing.
     * @param none
     * @return void
     */
    void levelUp();

    /**
    * Sets the player's HP to 0.
    * @param none
    * @return void
    */
    void setDead();

    /**
    * Reduces force by one point. If the player's force is 0, does nothing.
    * @param none
    * @return void
    */
    void loseOneForce();

private:
    friend std::ostream& operator<<(std::ostream&, const Player&);

};

#endif //EX4_MATAM_PLAYER_H
