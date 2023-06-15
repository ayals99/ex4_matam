#ifndef EX4_MATAM_PLAYER_H
#define EX4_MATAM_PLAYER_H

#include <string>
#include "HealthPoints.h"
#include "utilities.h"

static const int MAXIMAL_LEVEL = 10;
static const int MINIMUM_FORCE = 0;
static const int MINIMUM_HEALTH = 0;
static const int INITIAL_FORCE = 5;
static const int INITIAL_COINS = 10;
static const int INITIAL_LEVEL = 1;
static const int MAX_HP = 100;

class Player{ // in order to get the type of the player, we'll use dynamic_cast
protected:
    std::string m_name; // shorter than 15 letters and no spaces
    int m_level; // 1-10
    int m_force; // >= 0
    HealthPoints m_health;
    int m_coins; // >=0

public:
    Player();
    friend std::ostream& operator<<(std::ostream&, const Player&);

    /**getters:*/
    std::string getName() const;
    int getLevel() const;
    bool isInGame() const;
    bool dead() const;
    bool won() const;
    int getForce() const;
    HealthPoints getHealth() const;
    int getCoins() const;
    virtual bool playerIsStronger(int opponentForce) const; // Determines who will win the battle. Override by warrior
    virtual std::string getPlayerJob() const = 0; // Pure virtual function. Override by Ninja and Warrior

    /** Setters: */
    void levelUp();
    virtual void addHealth(int healthToAdd); // Override by Healer
    void reduceHealthPoints(int healthToReduce);
    virtual void addCoins(int coinsToAdd); // Ninja will override this in order to add twice the amount of coins
    void setDead();
    void loseOneForce();
};

#endif //EX4_MATAM_PLAYER_H
