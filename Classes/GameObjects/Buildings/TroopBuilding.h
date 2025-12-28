// File: TroopBuilding.h
// Brief: Declares the TroopBuilding component.
#pragma once

#include "GameObjects/Buildings/Building.h"
#include "Managers/ConfigManager.h"
#include "Managers/ResourceManager.h"
#include "cocos2d.h"               
#include "ui/CocosGUI.h"    
#include <unordered_map>





// Barracks encapsulates related behavior and state.





class Barracks : public Building {
public:
    Barracks() { image = "buildings/buildings7.png"; }

    int capAdd = 0;
    int capApplied = 0;

    void setupStats(int level) {
        auto st = ConfigManager::getBarracksStats(level);
        capAdd = st.capAdd;
        hpMax = st.hp;
        if (hp > hpMax) hp = hpMax;
    }

    
    void applyCap() {
        int currentCap = ResourceManager::getPopulationCap();
        int delta = capAdd - capApplied;
        if (delta != 0) {
            ResourceManager::setPopulationCap(currentCap + delta);
            capApplied = capAdd;
        }
    }

    int getHousingCap() const { return capAdd; }

    static int getHousingCapByLevel(int level) {
        auto st = ConfigManager::getBarracksStats(level);
        return st.capAdd;
    }
};

// TrainingCamp encapsulates related behavior and state.

class TrainingCamp : public Building {
public:
    enum TroopType {
        TROOP_BARBARIAN = 1,
        TROOP_ARCHER = 2,
        TROOP_GIANT = 3,
        TROOP_WALLBREAKER = 4,
    };

    TrainingCamp() { image = "buildings/buildings8.png"; }

    void setupStats(int level) {
        auto st = ConfigManager::getTrainingCampStats(level);
        hpMax = st.hp;
        if (hp > hpMax) hp = hpMax;
    }

    
    static int getTroopHousing(TroopType t) {
        switch (t) {
            case TROOP_BARBARIAN:   return 1;
            case TROOP_ARCHER:      return 1;
            
            case TROOP_GIANT:       return 5;
            case TROOP_WALLBREAKER: return 2;
            default:                return 1;
        }
    }

    
    static const char* getTroopIcon(TroopType t) {
        switch (t) {
            case TROOP_BARBARIAN:   return "ui/barbarian_choose_button.png";
            case TROOP_ARCHER:      return "ui/archer_choose_button.png";
            case TROOP_GIANT:       return "ui/giant_choose_buuton.png";
            case TROOP_WALLBREAKER: return "ui/wallbreaker_choose_button.png";
            default:                return "ui/barbarian_choose_button.png";
        }
    }

    static int getUnlockLevel(TroopType t) {
        switch (t) {
            case TROOP_BARBARIAN:   return 1;
            case TROOP_ARCHER:      return 2;
            case TROOP_GIANT:       return 3;
            case TROOP_WALLBREAKER: return 4;
            default:                return 1;
        }
    }

    bool isUnlocked(TroopType t) const { return level >= getUnlockLevel(t); }

    
    int getReadyCount(TroopType t) const {
        auto it = readyTroops.find((int)t);
        return it == readyTroops.end() ? 0 : it->second;
    }

    void setReadyCount(TroopType t, int count) {
        int key = (int)t;
        if (count <= 0) readyTroops.erase(key);
        else readyTroops[key] = count;
    }

    const std::unordered_map<int, int>& getAllReadyCounts() const { return readyTroops; }
    void clearAllReadyCounts() { readyTroops.clear(); }

    
    int getUsedHousing() const {
        int sum = 0;
        for (const auto& kv : readyTroops) {
            sum += kv.second * getTroopHousing((TroopType)kv.first);
        }
        return sum;
    }

    
    bool tryAddReadyTroop(TroopType t) {
        if (!isUnlocked(t)) return false;

        
        int totalCap = ResourceManager::getPopulationCap();
        if (totalCap <= 0) return false;

        
        int newUsed = getUsedHousing() + getTroopHousing(t);
        if (newUsed > totalCap) return false;

        
        int key = (int)t;
        readyTroops[key] = getReadyCount(t) + 1;
        return true;
    }

    
    bool tryRemoveReadyTroop(TroopType t) {
        int key = (int)t;
        auto it = readyTroops.find(key);
        if (it == readyTroops.end() || it->second <= 0) return false;

        it->second -= 1;
        if (it->second <= 0) readyTroops.erase(it);
        return true;
    }

    
    void updateTraining(float dt) {} 
    int getQueuedCount(TroopType t) const { return 0; } 
    int getActiveType() const { return 0; } 
    float getActiveProgress01() const { return 0.0f; } 
    bool tryAddTroop(TroopType t) { return tryAddReadyTroop(t); } 
    bool tryRemoveQueued(TroopType t) { return false; } 
    std::vector<int> getQueueOrder() const { return {}; } 

private:
    std::unordered_map<int, int> readyTroops; 
};



// Laboratory encapsulates related behavior and state.



class Laboratory : public Building {
public:
    Laboratory() { image = "buildings/building11L1.png"; }

    void setupStats(int level) {
        auto st = ConfigManager::getLaboratoryStats(level);
        hpMax = st.hp;
        if (hp > hpMax) hp = hpMax;
    }
};