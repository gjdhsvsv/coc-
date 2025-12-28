// File: Archer.h
// Brief: Declares the Archer component.
#pragma once

#include "GameObjects/Units/UnitBase.h"







// Archer encapsulates related behavior and state.







class Archer : public UnitBase {
public:
    Archer();
    // TODO: Add a brief description.
    void applyLevel(int lvl);
    virtual ~Archer() = default;
};
