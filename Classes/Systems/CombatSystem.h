// File: CombatSystem.h
// Brief: Declares the CombatSystem component.
#pragma once
#include "cocos2d.h"
#include <vector>

#include "GameObjects/Units/UnitBase.h"
#include "GameObjects/Buildings/Building.h"
#include "Systems/AISystem.h"

namespace CombatSystem {

    
    // Returns whether InRange is true.

    
    bool isInRange(const cocos2d::Vec2& a, const cocos2d::Vec2& b, float range);

    
    
    // TODO: Add a brief description.

    
    
    void ensureHpBar(cocos2d::Sprite* sprite, int hp, int hpMax, bool isUnit);

    
    // TODO: Add a brief description.

    
    bool tryUnitAttackBuilding(UnitBase& attacker,
        cocos2d::Sprite* attackerSprite,
        Building& target,
        cocos2d::Sprite* targetSprite);

    
    
    // TODO: Add a brief description.

    
    
    bool unitHitBuildingNoRange(UnitBase& attacker,
        cocos2d::Sprite* attackerSprite,
        Building& target,
        cocos2d::Sprite* targetSprite);

    
    
    
    
    // TODO: Add a brief description.

    
    
    
    
    bool tryBomberExplode(UnitBase& bomber,
        cocos2d::Sprite* bomberSprite,
        EnemyBuildingRuntime& targetWall,
        std::vector<EnemyBuildingRuntime>& enemyBuildings);

    
    
    // TODO: Add a brief description.

    
    
    bool bomberExplodeNoRange(UnitBase& bomber,
        cocos2d::Sprite* bomberSprite,
        EnemyBuildingRuntime& targetWall,
        std::vector<EnemyBuildingRuntime>& enemyBuildings);

    
    // TODO: Add a brief description.

    
    bool tryDefenseShoot(float dt,
        Building& defense,
        cocos2d::Sprite* defenseSprite,
        std::vector<BattleUnitRuntime>& units,
        float& cooldown,
        float cellSizePx);
}
