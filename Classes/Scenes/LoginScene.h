// File: LoginScene.h
// Brief: Declares the LoginScene component.
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"




// LoginScene encapsulates related behavior and state.




class LoginScene : public cocos2d::Scene
{
public:
    // Creates an instance.
    static cocos2d::Scene* createScene();
    // Initializes the object.
    virtual bool init() override;
    CREATE_FUNC(LoginScene);

// Saves data to storage.

private:
    void openSaveSelector();
    // Saves data to storage.
    void closeSaveSelector();
    // Saves data to storage.
    void buildSaveUI();
    // Saves data to storage.
    void refreshSaveList();
    // TODO: Add a brief description.
    void backToMenu();

private:
    cocos2d::LayerColor* _saveMask = nullptr;
    cocos2d::ui::ScrollView* _saveScroll = nullptr;
    cocos2d::Node* _saveContent = nullptr;
};
