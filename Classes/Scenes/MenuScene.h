#pragma once

#include "cocos2d.h"

// Main menu:
//  - Create New Save (auto pick first empty slot then enter MainScene)
//  - Load Existing Save (go to LoginScene)
//
// NOTE: Keep this scene lightweight and readable. All heavy data logic is handled by SaveSystem.
class MenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init() override;
    CREATE_FUNC(MenuScene);

private:
    void openSettings();
    void closeSettings();

    // Tiny toast text (for errors like "No empty slot")
    void showToast(const std::string& text);

private:
    cocos2d::LayerColor* _settingsMask = nullptr;
    cocos2d::Label* _toast = nullptr;
};
