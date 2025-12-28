#pragma once

#include "GameObjects/Buildings/Building.h"
#include "Managers/ConfigManager.h"

/**
 * @file DefenseBuilding.h
 *
 * Defines defensive building types used by both the village scene and the battle scene.
 *
 * Notes:
 * - These classes are lightweight data holders that inherit from Building.
 * - Runtime behavior (shooting, targeting, visuals, cooldowns) is implemented in systems
 *   such as AISystem and CombatSystem.
 */

/**
 * Arrow tower building.
 *
 * The arrow tower is a ranged defense that periodically shoots the nearest enemy unit
 * within its configured range.
 */
class ArrowTower : public Building {
public:
    /** Creates an arrow tower with the default (village) placeholder texture. */
    ArrowTower() { image = "buildings/buildings1.png"; }

    /** Damage dealt per successful hit. */
    float damagePerHit = 0.0f;

    /** Number of attacks per second. Used to derive the cooldown interval. */
    float attacksPerSecond = 0.0f;

    /** Attack range expressed in grid cells. */
    int rangeCells = 0;

    /**
     * Loads per-level stats from ConfigManager and updates HP/damage/range.
     *
     * @param level Building level (1-based).
     */
    void setupStats(int level) {
        auto st = ConfigManager::getArrowTowerStats(level);
        hpMax = st.hp;
        if (hp > hpMax) hp = hpMax;
        damagePerHit = st.damagePerHit;
        attacksPerSecond = st.attacksPerSecond;
        rangeCells = st.rangeCells;
    }
};

/**
 * Cannon building.
 *
 * The cannon is a defense that shoots the nearest enemy unit within range.
 * In battle, the cannon barrel sprite is rotated by swapping textures based on
 * the current target direction (see CombatSystem::tryDefenseShoot).
 */
class Cannon : public Building {
public:
    /** Creates a cannon with the default (village) placeholder texture. */
    Cannon() { image = "buildings/buildings2.png"; }

    /** Damage dealt per successful hit. */
    float damagePerHit = 0.0f;

    /** Number of attacks per second. Used to derive the cooldown interval. */
    float attacksPerSecond = 0.0f;

    /** Attack range expressed in grid cells. */
    int rangeCells = 0;

    /**
     * Loads per-level stats from ConfigManager and updates HP/damage/range.
     *
     * @param level Building level (1-based).
     */
    void setupStats(int level) {
        auto st = ConfigManager::getCannonStats(level);
        hpMax = st.hp;
        if (hp > hpMax) hp = hpMax;
        damagePerHit = st.damagePerHit;
        attacksPerSecond = st.attacksPerSecond;
        rangeCells = st.rangeCells;
    }
};

/**
 * Wall building.
 *
 * Walls block movement. They are treated specially by the pathfinding system and
 * (depending on unit type) may be attacked to open a path.
 */
class Wall : public Building {
public:
    /** Creates a wall with the default texture. */
    Wall() { image = "buildings/buildings9.png"; }

    /**
     * Applies wall HP based on level.
     *
     * @param level Wall level (1..5).
     */
    void setupStats(int level) {
        if (level < 1) level = 1;
        if (level > 5) level = 5;

        // Index 0 is unused so level can be used directly.
        static const int kHp[6] = { 0, 100, 200, 400, 800, 1200 };
        hpMax = kHp[level];
        if (hp > hpMax) hp = hpMax;
    }
};
