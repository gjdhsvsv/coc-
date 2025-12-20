#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class LoginScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init() override;
    CREATE_FUNC(LoginScene);

private:
    void openSettings();
    void buildSaveUI();
    void refreshSaveList();

    cocos2d::LayerColor* _saveMask = nullptr;
    cocos2d::ui::ScrollView* _saveScroll = nullptr;
    cocos2d::Node* _saveContent = nullptr;
};
