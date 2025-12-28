// File: Giant.cpp
// Brief: Implements the Giant component.
#include "GameObjects/Units/Giant.h"

#include <algorithm>

Giant::Giant()
{
    unitId = 3;
    name = "Giant";

    image = "giant/giant_stand.png";

    applyLevel(1);
}

void Giant::applyLevel(int lvl)
{
    
    
    
    static const int kHp[5] = { 400, 500, 600, 700, 900 };
    static const int kDmg[5] = { 24, 30, 40, 48, 62 };

    lvl = std::max(1, std::min(5, lvl));
    level = lvl;

    hpMax = kHp[lvl - 1];
    hp = hpMax;
    damage = kDmg[lvl - 1];

    
    attackInterval = 2.0f;
    attackRangeTiles = 1.0f;
    moveSpeedStat = 12.0f;

    housingSpace = 5;
    costElixir = 0;
    trainingTimeSec = 0;
}
