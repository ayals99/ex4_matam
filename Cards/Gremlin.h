#ifndef EX4_MATAM_GREMLIN_H
#define EX4_MATAM_GREMLIN_H

#include "BattleCards.h"
static const std::string GREMLIN_NAME = "Gremlin";
static const int GREMLIN_FORCE = 5; //TODO change later to 5!!!!!!!
static const int GREMLIN_DAMAGE = 10;
static const int GREMLIN_LOOT = 2;

class Gremlin : public BattleCard {

public:
    Gremlin() : BattleCard(GREMLIN_NAME, GREMLIN_FORCE, GREMLIN_DAMAGE, GREMLIN_LOOT){};

    Gremlin(Gremlin& other) = delete;
    Gremlin& operator=(const Gremlin& other) = delete;
    ~Gremlin() override = default;

};

#endif //EX4_MATAM_GREMLIN_H
