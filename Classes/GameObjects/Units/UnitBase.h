// File: UnitBase.h
// Brief: Declares the UnitBase component.
#pragma once

#include "cocos2d.h"

#include <memory>
#include <string>













// UnitBase encapsulates related behavior and state.













class UnitBase {
public:
    virtual ~UnitBase() = default;

    
    int unitId = 0;               
    int level = 1;
    std::string name;
    std::string image;            

    
    int hpMax = 1;
    int hp = 1;
    int damage = 1;
    float attackInterval = 1.0f;  
    
    
    
    float attackRangeTiles = 0.4f;   
    float moveSpeedStat = 18.0f;     

    float attackRange = 20.0f;       
    float moveSpeed = 60.0f;         

    
    int housingSpace = 1;
    int costElixir = 0;
    int trainingTimeSec = 0;

    
    float attackCooldown = 0.0f;  

// Creates an instance.

public:
    
    
    virtual cocos2d::Sprite* createSprite() const;

    
    // Resets state to defaults.

    
    virtual void reset();

    
    // TODO: Add a brief description.

    
    virtual int takeDamage(int amount);

    bool isDead() const { return hp <= 0; }

    
    float getDPS() const { return attackInterval <= 0.0001f ? (float)damage : (float)damage / attackInterval; }

    
    // TODO: Add a brief description.

    
    void tickAttack(float dt);     
    bool canAttack() const { return attackCooldown <= 0.0f; }
    // TODO: Add a brief description.
    void startAttackCooldown();    
};


namespace UnitFactory {
    // Creates an instance.
    std::unique_ptr<UnitBase> create(int unitId, int level);
}
