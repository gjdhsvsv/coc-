// File: Pathfinding.h
// Brief: Declares the Pathfinding component.
#pragma once
#include "cocos2d.h"
#include <vector>

namespace Pathfinding {

    // GridPos encapsulates related behavior and state.

    struct GridPos {
        int r = 0;
        int c = 0;
    };

    
    
    // TODO: Add a brief description.

    
    
    cocos2d::Vec2 stepTowards(const cocos2d::Vec2& cur,
        const cocos2d::Vec2& dst,
        float step,
        float stopDistance);

    
    
    
    // TODO: Add a brief description.

    
    
    
    std::vector<GridPos> findPathAStar(int rows, int cols,
        GridPos start, GridPos goal,
        const std::vector<unsigned char>& blocked,
        bool allowDiag,
        int maxIters);

    
    // TODO: Add a brief description.

    
    std::vector<cocos2d::Vec2> makeDirectPath(const cocos2d::Vec2& start,
        const cocos2d::Vec2& end,
        int segments);
}
