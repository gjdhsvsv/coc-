#pragma once
#include "cocos2d.h"
#include <string>

class Building {
public:
    virtual ~Building() = default;
    int hp = 100;
    int level = 1;
    std::string image;
    virtual cocos2d::Sprite* createSprite() const {
        auto s = cocos2d::Sprite::create(image);
        if (!s) {
            auto label = cocos2d::Label::createWithSystemFont("B", "Arial", 24);
            auto node = cocos2d::Sprite::create();
            node->addChild(label);
            return node;
        }
        return s;
    }
};