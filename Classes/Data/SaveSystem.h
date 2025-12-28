// File: SaveSystem.h
// Brief: Declares the SaveSystem component.
#pragma once

#include "cocos2d.h"
#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>

// SaveMeta encapsulates related behavior and state.

struct SaveMeta
{
    int slot = 0;
    bool exists = false;
    std::string name;
    std::string path;
    int64_t updatedAt = 0;
};

// SaveBuilding encapsulates related behavior and state.

struct SaveBuilding
{
    int id = 0;
    int level = 1;
    int r = 0;
    int c = 0;
    int hp = 0;
    float stored = 0.0f;

    
    int buildState = 0;          
    float buildTotalSec = 0.0f;  
    float buildRemainSec = 0.0f; 
    int upgradeTargetLevel = 0;  
};


// SaveTrainedTroop encapsulates related behavior and state.


struct SaveTrainedTroop
{
    int type = 0; 
    int r = 0;    
    int c = 0;    
};

// SaveData encapsulates related behavior and state.

struct SaveData
{
    int slot = 0;
    std::string name;
    int gold = 0;
    int elixir = 0;
    int population = 0;
    float timeScale = 1.0f;
    int64_t lastRealTime = 0; 
    std::vector<SaveBuilding> buildings;
    std::vector<SaveTrainedTroop> trainedTroops;

    
    std::unordered_map<int, int> troopLevels;

    
    int researchUnitId = 0;
    int researchTargetLevel = 0;
    float researchTotalSec = 0.0f;
    float researchRemainSec = 0.0f;


};

// SaveSystem encapsulates related behavior and state.

class SaveSystem
{
public:
    // Sets the CurrentSlot.
    static void setCurrentSlot(int slot);
    // Returns the CurrentSlot.
    static int getCurrentSlot();

    // Sets the BattleTargetSlot.

    static void setBattleTargetSlot(int slot);
    // Returns the BattleTargetSlot.
    static int getBattleTargetSlot();

    
    // Sets the BattleReadyTroops.

    
    static void setBattleReadyTroops(const std::unordered_map<int, int>& troops);
    static const std::unordered_map<int, int>& getBattleReadyTroops();

    
    // Sets the BattleTroopLevels.

    
    static void setBattleTroopLevels(const std::unordered_map<int, int>& levels);
    static const std::unordered_map<int, int>& getBattleTroopLevels();

    // Returns the SaveDir.

    static std::string getSaveDir();
    // Returns the SavePath.
    static std::string getSavePath(int slot);
    // TODO: Add a brief description.
    static bool exists(int slot);
    // TODO: Add a brief description.
    static std::vector<SaveMeta> listAllSlots();

    // Loads data from storage.

    static bool load(int slot, SaveData& outData);
    // Saves data to storage.
    static bool save(const SaveData& data);
    // Removes an item.
    static bool remove(int slot);
    // TODO: Add a brief description.
    static SaveData makeDefault(int slot, const std::string& name);

private:
    static constexpr int kMaxSlots = 20;
    static int s_currentSlot;
    static int s_battleTargetSlot;
    static std::unordered_map<int, int> s_battleReadyTroops;
    static std::unordered_map<int, int> s_battleTroopLevels;
};