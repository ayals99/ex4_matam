#ifndef EX4_MATAM_HEALER_H
#define EX4_MATAM_HEALER_H

#include "Player.h"

class Healer : public Player {
public:
    void addHealth(int healthToAdd) override{
        m_health += 2*healthToAdd;
    }
    std::string getPlayerJob() const override{
        return "Healer";
    }
};

#endif //EX4_MATAM_HEALER_H
