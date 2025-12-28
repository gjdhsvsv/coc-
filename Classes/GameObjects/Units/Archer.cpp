// File: Archer.cpp
// Brief: Implements the Archer component.
#include "GameObjects/Units/Archer.h"

#include <algorithm>





Archer::Archer()
{
    unitId = 2;
    name = "Archer";

    
    image = "archor/archor_stand.png";

    applyLevel(1);
}

void Archer::applyLevel(int lvl)
{
    
    static const int kHp[5] = { 22, 26, 29, 33, 40 };
    static const int kDmg[5] = { 8, 10, 13, 16, 20 };

    lvl = std::max(1, std::min(5, lvl));
    level = lvl;

    hpMax = kHp[lvl - 1];
    hp = hpMax;
    damage = kDmg[lvl - 1];
    attackInterval = 1.0f;

    
    
    attackRangeTiles = 3.0f;
    moveSpeedStat = 24.0f;

    housingSpace = 1;
    costElixir = 0;
    trainingTimeSec = 0;
}