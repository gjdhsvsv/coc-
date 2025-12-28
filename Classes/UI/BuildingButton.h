// File: BuildingButton.h
// Brief: Declares the BuildingButton component.
#pragma once
#include "cocos2d.h"
#include <functional>
#include <string>

// BuildingButton encapsulates related behavior and state.

class BuildingButton : public cocos2d::Node {
public:
    CREATE_FUNC(BuildingButton);
    std::function<void()> onClicked;
    // Initializes the object.
    virtual bool init() override;
    // Sets the ButtonScale.
    void setButtonScale(float s);
    // Sets the ButtonOffset.
    void setButtonOffset(const cocos2d::Vec2& o);
private:
    // TODO: Add a brief description.
    void layout();
    cocos2d::MenuItem* _item = nullptr;
    cocos2d::Menu* _menu = nullptr;
    float _scale = 1.0f;
    cocos2d::Vec2 _offset = cocos2d::Vec2(16.f, 16.f);
};