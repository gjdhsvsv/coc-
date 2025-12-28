// File: AttackVisitor.h
// Brief: Declares the AttackVisitor component.
#pragma once
#include "GameObjects/Units/UnitBase.h"
#include "GameObjects/Buildings/DefenseBuilding.h"
#include "GameObjects/Buildings/TownHall.h"
#include "GameObjects/Buildings/ResourceBuilding.h"
#include "GameObjects/Buildings/TroopBuilding.h"

// AttackVisitor encapsulates related behavior and state.

class AttackVisitor {
public:
    // TODO: Add a brief description.
    static int computeDamage(const UnitBase& attacker, const Building& target);
};
