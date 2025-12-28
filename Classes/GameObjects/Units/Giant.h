// File: Giant.h
// Brief: Declares the Giant component.
#pragma once

#include "GameObjects/Units/UnitBase.h"






// Giant encapsulates related behavior and state.






class Giant : public UnitBase {
public:
    Giant();
    // TODO: Add a brief description.
    void applyLevel(int lvl);
    virtual ~Giant() = default;
};
