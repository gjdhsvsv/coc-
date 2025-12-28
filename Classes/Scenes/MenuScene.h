// File: MenuScene.h
// Brief: Declares the MenuScene component.
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"




// MenuScene encapsulates related behavior and state.




class MenuScene : public cocos2d::Scene
{
public:
    // Creates an instance.
    static cocos2d::Scene* createScene();
    // Initializes the object.
    virtual bool init() override;
    CREATE_FUNC(MenuScene);

// Saves data to storage.

private:
    void createNewSaveAndEnter();

    
    // Saves data to storage.

    
    void openSaveSelector();
    // Saves data to storage.
    void closeSaveSelector();
    // Saves data to storage.
    void buildSaveUI();
    // Saves data to storage.
    void refreshSaveList();

private:
    cocos2d::LayerColor* _saveMask = nullptr;
    cocos2d::ui::ScrollView* _saveScroll = nullptr;
    cocos2d::Node* _saveContent = nullptr;
    cocos2d::Node* _savePanel = nullptr;
    cocos2d::EventListenerMouse* _saveMouseListener = nullptr;
};
