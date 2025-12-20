#pragma once
#include "cocos2d.h"
#include <vector>

class BattleScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(BattleScene);

private:
    void renderTargetVillage();
    cocos2d::Vec2 gridToWorld(int r, int c) const;
    void setBuildingVisualParams();

    // ESC menu (settings / back / quit)
    void openEscMenu();
    void closeEscMenu();
    void openSettings();
    cocos2d::LayerColor* _escMask = nullptr;
    cocos2d::LayerColor* _settingsMask = nullptr;
    cocos2d::Node* _world = nullptr;
    cocos2d::Sprite* _background = nullptr;
    int _rows = 30;
    int _cols = 30;
    float _tileW = 0.0f;
    float _tileH = 0.0f;
    cocos2d::Vec2 _anchor;
    float _buildingScale = 1.0f;
    std::vector<float> _buildingScaleById;
    std::vector<cocos2d::Vec2> _buildingOffsetById;
};