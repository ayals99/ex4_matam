#ifndef EX4_MATAM_WITCH_H
#define EX4_MATAM_WITCH_H
#include "BattleCards.h"
#include <string>

static const std::string WITCH_NAME = "Witch";
static const int WITCH_FORCE = 11;
static const int WITCH_DAMAGE = 10;
static const int WITCH_LOOT = 2;

class Witch : public BattleCard {
public:
    explicit Witch() : BattleCard(WITCH_NAME, WITCH_FORCE, WITCH_DAMAGE, WITCH_LOOT) {};

    Witch& operator=(const Witch& other) = delete;
    Witch(Witch& other) = delete;
    ~Witch() override = default;
};

#endif //EX4_MATAM_WITCH_H
