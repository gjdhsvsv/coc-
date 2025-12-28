// File: ConfigManager.cpp
// Brief: Implements the ConfigManager component.
#include "Managers/ConfigManager.h"
#include <algorithm>
namespace ConfigManager {

    
    static int sec(int s) { return s; }
    static int min_(int m) { return m * 60; }
    static int hour(int h) { return h * 3600; }

    
    
    static int getTownHallRequiredForLevel(int id, int level) {
        level = std::max(1, std::min(5, level));

        
        if (id == 3 || id == 5) {
            
            return 1;
        }
        
        if (id == 4 || id == 6) {
            if (level == 1) return 1;
            if (level == 2 || level == 3) return 2;
            return 3; 
        }
        
        if (id == 2) {
            if (level <= 2) return 1;
            if (level == 3) return 2;
            if (level == 4) return 3;
            return 4;
        }
        
        if (id == 1) {
            if (level <= 2) return 2;
            if (level == 3) return 3;
            if (level == 4) return 4;
            return 5;
        }
        
        if (id == 7) {
            return level; 
        }
        
        if (id == 8) {
            if (level <= 3) return 1;
            if (level == 4) return 2;
            return 3;
        }
        
        
        
        if (id == 9) return std::max(1, level - 1);

        
        if (id == 10) return 1;

        
        if (id == 11) {
            
            static const int req[6] = { 0, 2, 3, 4, 5, 5 };
            return req[level];
        }

        return 1;
    }
    std::string getBuildingName(int id) {
        switch (id) {
        case 1: return "Arrow Tower";
        case 2: return "Cannon";
        case 3: return "Elixir Collector";
        case 4: return "Elixir Storage";
        case 5: return "Gold Mine";
        case 6: return "Gold Storage";
        case 7: return "Barracks";
        case 8: return "Training Camp";
        case 9: return "Town Hall";
        case 10: return "Wall";
        case 11: return "Laboratory";
        default: return "Building";
        }
    }
    UpgradeCost getUpgradeCost(int id, int nextLevel) {
        nextLevel = std::max(1, std::min(5, nextLevel));

        
        

        
        if (id == 3) {
            static const int kCost[6] = { 0, 150, 300, 700, 1400, 3000 };
            return { true, kCost[nextLevel] };
        }
        
        if (id == 5) {
            static const int kCost[6] = { 0, 150, 300, 700, 1400, 3000 };
            return { false, kCost[nextLevel] };
        }
        
        if (id == 4) {
            static const int kCost[6] = { 0, 300, 750, 1500, 3000, 6000 };
            return { true, kCost[nextLevel] };
        }
        
        if (id == 6) {
            static const int kCost[6] = { 0, 300, 750, 1500, 3000, 6000 };
            return { false, kCost[nextLevel] };
        }
        
        if (id == 2) {
            static const int kCost[6] = { 0, 250, 1000, 4000, 16000, 50000 };
            return { true, kCost[nextLevel] };
        }
        
        if (id == 1) {
            static const int kCost[6] = { 0, 1000, 2000, 5000, 20000, 70000 };
            return { true, kCost[nextLevel] };
        }
        
        if (id == 7) {
            static const int kCost[6] = { 0, 200, 2000, 10000, 100000, 250000 };
            return { false, kCost[nextLevel] };
        }
        
        if (id == 8) {
            
            
            
            static const int kCost[6] = { 0, 100, 500, 2500, 5000, 20000 };
            
            
            return { false, kCost[nextLevel] };
        }
        
        if (id == 9) {
            static const int kCost[6] = { 0, 0, 1000, 4000, 25000, 150000 };
            return { true, kCost[nextLevel] };
        }
        
        if (id == 10) {
            
            
            static const int kCost[6] = { 0, 0, 1000, 5000, 10000, 20000 };
            return { true, kCost[nextLevel] };
        }

        
        if (id == 11) {
            
            
            static const int kCost[6] = { 0, 5000, 25000, 50000, 100000, 200000 };
            return { false, kCost[nextLevel] };
        }

        return { true, 0 };
    }
    int getMaxLevel() { return 5; }
    CollectorStats getElixirCollectorStats(int level) {
        switch (level) {
        case 1: return { 200, 1000, 1, 75, 0 };
        case 2: return { 400, 2000, 1, 150, 0 };
        case 3: return { 600, 3000, 1, 300, 0 };
        case 4: return { 800, 5000, 1, 400, 0 };
        case 5: return { 1000, 10000, 1, 500, 0 };
        default: return { 200, 1000, 1, 75, 0 };
        }
    }
    CollectorStats getGoldMineStats(int level) {
        switch (level) {
        case 1: return { 200, 1000, 1, 75, 0 };
        case 2: return { 400, 2000, 1, 150, 0 };
        case 3: return { 600, 3000, 1, 300, 0 };
        case 4: return { 800, 5000, 1, 400, 0 };
        case 5: return { 1000, 10000, 1, 500, 0 };
        default: return { 200, 1000, 1, 75, 0 };
        }
    }
    StorageStats getElixirStorageStats(int level) {
        switch (level) {
        case 1: return { 1500, 150, 0 };
        case 2: return { 3000, 300, 0 };
        case 3: return { 6000, 450, 0 };
        case 4: return { 12000, 600, 0 };
        case 5: return { 150000, 800, 0 };
        default: return { 1500, 150, 0 };
        }
    }
    StorageStats getGoldStorageStats(int level) {
        switch (level) {
        case 1: return { 1500, 150, 0 };
        case 2: return { 3000, 300, 0 };
        case 3: return { 6000, 450, 0 };
        case 4: return { 12000, 600, 0 };
        case 5: return { 150000, 800, 0 };
        default: return { 1500, 150, 0 };
        }
    }
    UpgradeCost getBuildCost(int id) {
        
        if (id == 1) return getUpgradeCost(id, 1);
        if (id == 2) return getUpgradeCost(id, 1);
        if (id == 3) return getUpgradeCost(id, 1);
        if (id == 4) return getUpgradeCost(id, 1);
        if (id == 5) return getUpgradeCost(id, 1);
        if (id == 6) return getUpgradeCost(id, 1);
        if (id == 7) return getUpgradeCost(id, 1);
        if (id == 8) return getUpgradeCost(id, 1);
        if (id == 10) return getUpgradeCost(id, 1);
        if (id == 11) return getUpgradeCost(id, 1);
        
        return { true, 0 };
    }

    int getBuildTimeSec(int id, int level) {
        level = std::max(1, std::min(5, level));

        
        if (id == 10) return 0;

        
        if (id == 3 || id == 5) {
            static const int t[6] = { 0, sec(5), sec(15), min_(1), min_(2), min_(5) };
            return t[level];
        }
        
        if (id == 4 || id == 6) {
            static const int t[6] = { 0, sec(10), min_(2), min_(5), min_(15), min_(30) };
            return t[level];
        }
        
        if (id == 2) {
            static const int t[6] = { 0, sec(5), sec(30), min_(2), min_(20), min_(30) };
            return t[level];
        }
        
        if (id == 1) {
            static const int t[6] = { 0, sec(15), min_(2), min_(20), hour(1), hour(1) + min_(30) };
            return t[level];
        }
        
        if (id == 9) {
            static const int t[6] = { 0, 0, sec(10), min_(30), hour(3), hour(6) };
            return t[level];
        }
        
        if (id == 7) {
            static const int t[6] = { 0, min_(1), min_(5), min_(30), hour(2), hour(6) };
            return t[level];
        }
        
        if (id == 8) {
            static const int t[6] = { 0, sec(10), sec(15), min_(2), min_(30), hour(2) };
            return t[level];
        }

        
        if (id == 11) {
            
            
            static const int t[6] = { 0, min_(1), min_(30), hour(2), hour(4), hour(8) };
            return t[level];
        }

        return 0;
    }
    TownHallStats getTownHallStats(int level) {
        switch (level) {
        case 1: return { 400, 0, 0 };
        case 2: return { 800, 0, 0 };
        case 3: return { 1600, 0, 0 };
        case 4: return { 2000, 0, 0 };
        case 5: return { 2400, 0, 0 };
        default: return { 400, 0, 0 };
        }
    }
    DefenseStats getArrowTowerStats(int level) {
        switch (level) {
        case 1: return { 380, 5.5f, 11.0f / 5.5f, 10 };
        case 2: return { 420, 7.5f, 15.0f / 7.5f, 10 };
        case 3: return { 460, 9.5f, 19.0f / 9.5f, 10 };
        case 4: return { 500, 12.5f, 25.0f / 12.5f, 10 };
        case 5: return { 540, 15.0f, 30.0f / 15.0f, 10 };
        default: return { 380, 5.5f, 11.0f / 5.5f, 10 };
        }
    }
    DefenseStats getCannonStats(int level) {
        switch (level) {
        case 1: return { 300, 5.6f, 7.0f / 5.6f, 9 };
        case 2: return { 360, 8.0f, 10.0f / 8.0f, 9 };
        case 3: return { 420, 10.4f, 13.0f / 10.4f, 9 };
        case 4: return { 500, 13.6f, 17.0f / 13.6f, 9 };
        case 5: return { 600, 18.4f, 23.0f / 18.4f, 9 };
        default: return { 300, 5.6f, 7.0f / 5.6f, 9 };
        }
    }
    BarracksStats getBarracksStats(int level) {
        switch (level) {
        case 1: return { 20, 100 };
        case 2: return { 30, 150 };
        case 3: return { 35, 200 };
        case 4: return { 40, 250 };
        case 5: return { 45, 300 };
        default: return { 20, 100 };
        }
    }
    TrainingCampStats getTrainingCampStats(int level) {
        switch (level) {
        case 1: return { 100 };
        case 2: return { 200 };
        case 3: return { 250 };
        case 4: return { 300 };
        case 5: return { 360 };
        default: return { 100 };
        }
    }

    LaboratoryStats getLaboratoryStats(int level) {
        switch (level) {
        case 1: return { 500 };
        case 2: return { 550 };
        case 3: return { 600 };
        case 4: return { 650 };
        case 5: return { 700 };
        default: return { 500 };
        }
    }
    int getBuildLimit(int id, int townHallLevel) {
        int th = townHallLevel;
        if (id == 1) {
            if (th <= 1) return 0;
            if (th == 2) return 1;
            return 2;
        }
        if (id == 2) {
            if (th <= 1) return 1;
            if (th == 2) return 2;
            return 3;
        }
        if (id == 7) {
            if (th <= 1) return 1;
            if (th == 2) return 2;
            return 3;
        }
        if (id == 3 || id == 5) {
            if (th <= 1) return 1;
            if (th == 2) return 2;
            return 3;
        }
        if (id == 4 || id == 6) {
            if (th <= 2) return 1;
            return 2;
        }
        if (id == 10) {
            if (th <= 1) return 25;
            if (th == 2) return 50;
            return 75;
        }

        if (id == 11) {
            
            if (th < 2) return 0;
            return 1;
        }
        return 1;
    }
    bool isUpgradeAllowed(int id, int nextLevel, int townHallLevel, int maxBarracksLevel) {
        
        
        int requiredTH = getTownHallRequiredForLevel(id, nextLevel);
        if (townHallLevel < requiredTH) return false;

        
        (void)maxBarracksLevel;
        return true;
    }
}







int ConfigManager::getTroopResearchTimeSec(int unitId, int targetLevel)
{
	(void)unitId;
	if (targetLevel <= 1) return 0;
	
	const int halfHourSec = 30 * 60;
	return (targetLevel - 1) * halfHourSec;
}

int ConfigManager::getTroopResearchCostElixir(int unitId, int targetLevel)
{
	(void)unitId;
	if (targetLevel <= 1) return 0;
	
	int cost = 10000;
	for (int lv = 2; lv < targetLevel; ++lv) {
		cost *= 2;
	}
	return cost;
}
