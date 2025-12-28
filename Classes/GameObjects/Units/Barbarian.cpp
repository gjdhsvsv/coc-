// File: Barbarian.cpp
// Brief: Implements the Barbarian component.
#include "GameObjects/Units/Barbarian.h"

#include <algorithm>






Barbarian::Barbarian()
{
    unitId = 1;
    name = "Barbarian";

    
    image = "barbarian/barbarian_stand.png";

    
    applyLevel(1);
}

void Barbarian::applyLevel(int lvl)
{
    
    
    static const int kHp[5] = { 45, 54, 65, 85, 105 };
    static const int kDmg[5] = { 9, 12, 15, 18, 23 };

    lvl = std::max(1, std::min(5, lvl));
    level = lvl;

    hpMax = kHp[lvl - 1];
    hp = hpMax;
    damage = kDmg[lvl - 1];
    attackInterval = 1.0f;

    
    attackRangeTiles = 0.4f;
    moveSpeedStat = 18.0f;

    housingSpace = 1;
    costElixir = 0;
    trainingTimeSec = 0;
}