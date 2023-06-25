#ifndef EX4_MATAM_HEALER_H
#define EX4_MATAM_HEALER_H

#include "Player.h"

const int HP_MULTIPLIER = 2;


class Healer : public Player {
private:
    std::string m_job = "Healer";

public:
    explicit Healer(std::string name) : Player(name) {}

    void heal(int healthToAdd) override{
        if(healthToAdd > 0) {
            m_health += HP_MULTIPLIER * healthToAdd;
        }
    }

    const std::string& getPlayerJob() const override{
        return m_job;
    }
};

#endif //EX4_MATAM_HEALER_H
