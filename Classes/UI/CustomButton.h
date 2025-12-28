// File: CustomButton.h
// Brief: Declares the CustomButton component.
#pragma once
#include "cocos2d.h"
#include <functional>
// CustomButton encapsulates related behavior and state.
class CustomButton {
public:
    
    
    static cocos2d::LayerColor* createUpgradePanel(const std::string& title, const std::string& resName, int amount, bool disabled, bool isMaxLevel, const std::function<bool()>& onUpgrade, const std::function<void()>& onCancel);
};