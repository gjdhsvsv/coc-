#include "Managers/ConfigManager.h"
namespace ConfigManager {
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
            default: return "Building";
        }
    }
    UpgradeCost getUpgradeCost(int id, int nextLevel) {
        if (id == 3) {
            int currentLevel = nextLevel - 1;
            if (currentLevel < 1) return { true, 0 };
            auto st = getElixirCollectorStats(currentLevel);
            return { true, st.upgradeGold };
        }
        if (id == 5) {
            int currentLevel = nextLevel - 1;
            if (currentLevel < 1) return { false, 0 };
            auto st = getGoldMineStats(currentLevel);
            return { false, st.upgradeGold };
        }
        int base = 500;
        int amount = base * nextLevel;
        bool useGold = true;
        if (id == 7 || id == 8) useGold = false;
        return { useGold, amount };
    }
    int getMaxLevel() { return 3; }
    CollectorStats getElixirCollectorStats(int level) {
        switch (level) {
            case 1: return { 200, 1000, 6, 75, 300 };
            case 2: return { 400, 2000, 15, 150, 700 };
            case 3: return { 600, 3000, 25, 300, 0 };
            default: return { 200, 1000, 6, 75, 300 };
        }
    }
    CollectorStats getGoldMineStats(int level) {
        switch (level) {
            case 1: return { 200, 1000, 6, 75, 300 };
            case 2: return { 400, 2000, 15, 150, 700 };
            case 3: return { 600, 3000, 25, 300, 0 };
            default: return { 200, 1000, 6, 75, 300 };
        }
    }
    UpgradeCost getBuildCost(int id) {
        if (id == 3) return { true, 150 };
        if (id == 5) return { false, 150 };
        return { true, 0 };
    }
}
