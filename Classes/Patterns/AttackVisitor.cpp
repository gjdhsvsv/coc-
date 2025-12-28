// File: AttackVisitor.cpp
// Brief: Implements the AttackVisitor component.
#include "Patterns/AttackVisitor.h"
#include <algorithm>

int AttackVisitor::computeDamage(const UnitBase& attacker, const Building& target)
{
    (void)target;
    
    return std::max(1, attacker.damage);
}
