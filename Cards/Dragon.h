#ifndef EX4_MATAM_DRAGON_H
#define EX4_MATAM_DRAGON_H
#include <string>
#include "BattleCards.h"

static const std::string DRAGON_NAME = "Dragon";
static const int DRAGON_FORCE = 25;
static const int DRAGON_DAMAGE = DEFAULT_MAXIMAL_HEALTH;
static const int DRAGON_LOOT = 1000;

class Dragon : public BattleCard {
public:
    Dragon() : BattleCard(DRAGON_NAME, DRAGON_FORCE, DRAGON_DAMAGE, DRAGON_LOOT) {};

    Dragon& operator=(const Dragon& other) = delete;
    Dragon(Dragon& other) = delete;
    ~Dragon() override = default;
};

#endif //EX4_MATAM_DRAGON_H
