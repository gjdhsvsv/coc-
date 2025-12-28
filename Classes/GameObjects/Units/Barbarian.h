// File: Barbarian.h
// Brief: Declares the Barbarian component.
#pragma once

#include "GameObjects/Units/UnitBase.h"







// Barbarian encapsulates related behavior and state.







class Barbarian : public UnitBase {
public:
    Barbarian();
    // TODO: Add a brief description.
    void applyLevel(int lvl);
    virtual ~Barbarian() = default;
};
