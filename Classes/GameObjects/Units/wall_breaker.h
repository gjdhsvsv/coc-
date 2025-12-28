// File: wall_breaker.h
// Brief: Declares the wall_breaker component.
#pragma once

#include "GameObjects/Units/UnitBase.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"





// WallBreaker encapsulates related behavior and state.





class WallBreaker : public UnitBase {
public:
    
    int wallDamageMultiplier = 40;
    float damageRadiusTiles = 2.0f;
    int deathDamage = 6; 

    WallBreaker();
    // TODO: Add a brief description.
    void applyLevel(int lvl);

    virtual ~WallBreaker() = default;
};
