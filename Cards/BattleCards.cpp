#include "BattleCards.h"

const std::string GREMLIN = "Gremlin";
const int GREMLIN_FORCE = 5;
const int GREMLIN_LOOT = 2;
const int GREMLIN_DAMAGE_UPON_LOSS = 10;

const std::string WITCH = "Witch";
const int WITCH_FORCE = 11;
const int WITCH_LOOT = 2;
const int WITCH_DAMAGE_UPON_LOSS = 10;

const std::string DRAGON = "Dragon";
const int DRAGON_FORCE = 25;
const int DRAGON_LOOT = 1000;
const int DRAGON_DAMAGE_UPON_LOSS = MAX_HP;

BattleCard::BattleCard(const std::string &name) : Card(name) {
    if(name == GREMLIN){
        m_force = GREMLIN_FORCE;
        m_loot = GREMLIN_LOOT;
        m_damageUponLoss = GREMLIN_DAMAGE_UPON_LOSS;
    }
    else if(name == WITCH){
        m_force = WITCH_FORCE;
        m_loot = WITCH_LOOT;
        m_damageUponLoss = WITCH_DAMAGE_UPON_LOSS;
    }
    else if(name == DRAGON){
        m_force = DRAGON_FORCE;
        m_loot = DRAGON_LOOT;
        m_damageUponLoss = DRAGON_DAMAGE_UPON_LOSS;
    }
    else{
        throw std::invalid_argument("Invalid name for BattleCard");
    }
}

void BattleCard::applyEncounter(Player& player) const
{
    if(player.IsPlayerStronger(m_force))
    {
        player.addCoins(m_loot);
        player.levelUp();
    }
    else
    {
      player.damage(m_damageUponLoss);
      if(m_name == WITCH)
      {
          player.loseOneForce();
      }
    }
}

void BattleCard::printCardInfo(std::ostream &os) const
{
    printCardDetails(os, m_name);
    bool isDragon = m_name == DRAGON;
    printMonsterDetails(os, m_force,m_damageUponLoss, m_loot, isDragon);
    printEndOfCardDetails(os);
}







