#ifndef EX4_MATAM_DRAGON_H
#define EX4_MATAM_DRAGON_H
#include <string>

static const std::string DRAGON_NAME = "Dragon";
static const int DRAGON_FORCE = 25;

#include "BattleCards.h"
class Dragon : public BattleCard {
    Dragon() : BattleCard(DRAGON_NAME, ){};
};

#endif //EX4_MATAM_DRAGON_H
