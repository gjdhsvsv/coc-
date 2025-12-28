// File: BattleScene.h
// Brief: Declares the BattleScene component.
#pragma once

#include "cocos2d.h"
#include <vector>
#include <unordered_map>

#include "Systems/AISystem.h"
#include "Data/SaveSystem.h"

// BattleScene encapsulates related behavior and state.

class BattleScene : public cocos2d::Scene
{
public:
    // Creates an instance.
    static cocos2d::Scene* createScene();
    // Initializes the object.
    virtual bool init() override;
    // Updates the object state.
    virtual void update(float dt) override;
    CREATE_FUNC(BattleScene);

// TODO: Add a brief description.

private:
    void renderTargetVillage();

    
    
    enum class Phase { Scout, Battle, End };
    // Sets the upBattleHUD.
    void setupBattleHUD();
    // Sets the upLootHUD.
    void setupLootHUD();
    // Updates the object state.
    void updateLootHUD();

    // Sets the upTroopBar.

    void setupTroopBar();
    // TODO: Add a brief description.
    void refreshTroopBar();

    
    // TODO: Add a brief description.

    
    bool handleTroopBarClick(const cocos2d::Vec2& glPos);         
    // Returns whether PosInTroopBar is true.
    bool isPosInTroopBar(const cocos2d::Vec2& glPos) const;       
    // Returns whether PosInDeployArea is true.
    bool isPosInDeployArea(const cocos2d::Vec2& worldLocal) const;
    // TODO: Add a brief description.
    cocos2d::Vec2 worldToGridFloat(const cocos2d::Vec2& worldLocal) const;
    // TODO: Add a brief description.
    bool worldToGrid(const cocos2d::Vec2& worldLocal, int& outR, int& outC) const;
    // Returns whether GridBlocked is true.
    bool isGridBlocked(int r, int c) const;
    // TODO: Add a brief description.
    void rebuildDeployBlockedMap();
    // TODO: Add a brief description.
    void ensureDeployOverlay();
    // TODO: Add a brief description.
    void rebuildDeployOverlay();
    // Updates the object state.
    void updateDeployOverlayVisibility();
    // Sets the SelectedTroop.
    void setSelectedTroop(int troopType);                          
    // TODO: Add a brief description.
    void deploySelectedTroop(const cocos2d::Vec2& glPos);          
    // TODO: Add a brief description.
    bool spawnUnit(int unitId, const cocos2d::Vec2& worldLocalPos);

    // TODO: Add a brief description.

    void showBattleToast(const std::string& msg, float seconds = 2.0f);
    // Sets the Zoom.
    void setZoom(float z);
    // TODO: Add a brief description.
    void clampWorld();
    // TODO: Add a brief description.
    void startPhase(Phase p, float durationSec);
    // Updates the object state.
    void updateBattleHUD();
    // TODO: Add a brief description.
    void showReturnButton();

    
    // TODO: Add a brief description.

    
    void showBattleResultPopup(bool win);
    // TODO: Add a brief description.
    void openAbandonConfirmPopup();
    // TODO: Add a brief description.
    void closeAbandonConfirmPopup(bool resumeBattle);
    // TODO: Add a brief description.
    void endBattleAndShowResult(bool win);

    
    // TODO: Add a brief description.

    
    void checkBattleResult(bool timeUp);

    
    // Loads data from storage.

    
    void loadBattleSaves();
    // Saves data to storage.
    void persistBattleSaves();
    
    
    
    // Sets the tleBattleLoot.
    
    
    
    void settleBattleLoot();
    // Saves data to storage.
    int calcGoldCapFromSave(const SaveData& data) const;
    // Saves data to storage.
    int calcElixirCapFromSave(const SaveData& data) const;
    // Returns whether TownHallDestroyed is true.
    bool isTownHallDestroyed() const;
    // TODO: Add a brief description.
    bool areAllNonWallBuildingsDestroyed() const;
    // TODO: Add a brief description.
    bool areAllTroopsDeployedAndDead() const;

    Phase _phase = Phase::Scout;
    float _phaseRemaining = 0.0f;
    float _phaseTotal = 1.0f;

    cocos2d::Node* _hud = nullptr;
    cocos2d::Label* _phaseLabel = nullptr;
    cocos2d::Label* _timeLabel = nullptr;
    cocos2d::LayerColor* _barBg = nullptr;
    cocos2d::LayerColor* _barFill = nullptr;
    cocos2d::Menu* _returnMenu = nullptr;

    
    cocos2d::Node* _lootHud = nullptr;
    cocos2d::Label* _lootableTitle = nullptr;
    cocos2d::Label* _lootedTitle = nullptr;
    cocos2d::LayerColor* _lootableGoldBg = nullptr;
    cocos2d::LayerColor* _lootableGoldFill = nullptr;
    cocos2d::Label* _lootableGoldText = nullptr;
    cocos2d::LayerColor* _lootableElixirBg = nullptr;
    cocos2d::LayerColor* _lootableElixirFill = nullptr;
    cocos2d::Label* _lootableElixirText = nullptr;
    cocos2d::LayerColor* _lootedGoldBg = nullptr;
    cocos2d::LayerColor* _lootedGoldFill = nullptr;
    cocos2d::Label* _lootedGoldText = nullptr;
    cocos2d::LayerColor* _lootedElixirBg = nullptr;
    cocos2d::LayerColor* _lootedElixirFill = nullptr;
    cocos2d::Label* _lootedElixirText = nullptr;

    int _lootGoldTotal = 0;
    int _lootElixirTotal = 0;
    int _lootedGold = 0;
    int _lootedElixir = 0;
    bool _lootSettled = false;

    // TODO: Add a brief description.

    cocos2d::Vec2 gridToWorld(int r, int c) const;
    // Sets the BuildingVisualParams.
    void setBuildingVisualParams();

    
    // TODO: Add a brief description.

    
    void openEscMenu();
    // TODO: Add a brief description.
    void closeEscMenu();
    // TODO: Add a brief description.
    void openSettings();
    cocos2d::LayerColor* _escMask = nullptr;
    cocos2d::LayerColor* _settingsMask = nullptr;

    
    cocos2d::LayerColor* _abandonMask = nullptr;
    cocos2d::LayerColor* _resultMask = nullptr;
    bool _pausedByPopup = false;

    cocos2d::Node* _world = nullptr;

    
    float _zoom = 1.0f;
    float _minZoom = 0.5f;
    float _maxZoom = 2.5f;
    bool _dragging = false;
    cocos2d::Vec2 _dragLast = cocos2d::Vec2::ZERO;

    // TroopSlot encapsulates related behavior and state.

    struct TroopSlot {
        int type = -1;
        cocos2d::Node* root = nullptr;
        cocos2d::Label* countLabel = nullptr;
        cocos2d::Label* selectedLabel = nullptr;
    };

    std::unordered_map<int, int> _troopCounts; 

    
    std::unordered_map<int, int> _deployedCounts;

    
    std::unordered_map<int, int> _troopLevels;
    std::vector<TroopSlot> _troopSlots;
    int _selectedTroopType = -1;

    long long _lastDeployMs = 0;
    bool _hasDeployedAnyTroop = false;

    
    bool _mouseDown = false;
    bool _mouseConsumed = false;
    bool _mouseMoved = false;
    cocos2d::Vec2 _mouseDownPos = cocos2d::Vec2::ZERO;

    
    bool _touchDown = false;
    bool _touchConsumed = false;
    bool _touchMoved = false;
    cocos2d::Vec2 _touchDownPos = cocos2d::Vec2::ZERO;

    
    cocos2d::Node* _troopBar = nullptr;
    cocos2d::Sprite* _background = nullptr;
    int _rows = 30;
    int _cols = 30;
    float _tileW = 0.0f;
    float _tileH = 0.0f;
    cocos2d::Vec2 _anchor;

    
    bool _deployAreaReady = false;
    cocos2d::Vec2 _deployTop = cocos2d::Vec2::ZERO;
    cocos2d::Vec2 _deployRight = cocos2d::Vec2::ZERO;
    cocos2d::Vec2 _deployBottom = cocos2d::Vec2::ZERO;
    cocos2d::Vec2 _deployLeft = cocos2d::Vec2::ZERO;

    float _buildingScale = 1.0f;
    std::vector<float> _buildingScaleById;
    std::vector<cocos2d::Vec2> _buildingOffsetById;

    
    
    std::vector<std::vector<uint8_t>> _deployBlocked; 
    cocos2d::DrawNode* _deployOverlay = nullptr;       

    
    AISystem _ai;
    float _cellSizePx = 32.0f;

    std::vector<EnemyBuildingRuntime> _enemyBuildings;
    std::vector<BattleUnitRuntime> _units;

    bool _battleEnded = false;

    
    int _attackerSlot = -1;
    int _defenderSlot = -1;
    SaveData _attackerData;
    SaveData _defenderData;
    bool _savesLoaded = false;
    bool _savesDirty = false;
};
