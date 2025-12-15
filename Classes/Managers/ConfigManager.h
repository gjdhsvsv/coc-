#pragma once
#include <string>
namespace ConfigManager {
struct UpgradeCost { bool useGold; int amount; };
std::string getBuildingName(int id);
UpgradeCost getUpgradeCost(int id, int nextLevel);
int getMaxLevel();
struct CollectorStats { int ratePerHour; int capacity; int chunkMinutes; int hp; int upgradeGold; };
CollectorStats getElixirCollectorStats(int level);
CollectorStats getGoldMineStats(int level);
UpgradeCost getBuildCost(int id);
}
