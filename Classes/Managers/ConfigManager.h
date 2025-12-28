// File: ConfigManager.h
// Brief: Declares the ConfigManager component.
#pragma once
#include <string>
namespace ConfigManager {
	// UpgradeCost encapsulates related behavior and state.
	struct UpgradeCost { bool useGold; int amount; };
	// Returns the BuildingName.
	std::string getBuildingName(int id);
	// Returns the UpgradeCost.
	UpgradeCost getUpgradeCost(int id, int nextLevel);
	// Returns the MaxLevel.
	int getMaxLevel();
	// CollectorStats encapsulates related behavior and state.
	struct CollectorStats { int ratePerHour; int capacity; int chunkMinutes; int hp; int upgradeGold; };
	// Returns the ElixirCollectorStats.
	CollectorStats getElixirCollectorStats(int level);
	// Returns the GoldMineStats.
	CollectorStats getGoldMineStats(int level);
	// StorageStats encapsulates related behavior and state.
	struct StorageStats { int capAdd; int hp; int upgradeCost; };
	// Returns the ElixirStorageStats.
	StorageStats getElixirStorageStats(int level);
	// Returns the GoldStorageStats.
	StorageStats getGoldStorageStats(int level);
	// Returns the BuildCost.
	UpgradeCost getBuildCost(int id);
	
	
	
	// Returns the BuildTimeSec.
	
	
	
	int getBuildTimeSec(int id, int level);
	// TownHallStats encapsulates related behavior and state.
	struct TownHallStats { int hp; int capAddElixir; int capAddGold; };
	// Returns the TownHallStats.
	TownHallStats getTownHallStats(int level);
	// DefenseStats encapsulates related behavior and state.
	struct DefenseStats { int hp; float damagePerHit; float attacksPerSecond; int rangeCells; };
	// Returns the ArrowTowerStats.
	DefenseStats getArrowTowerStats(int level);
	// Returns the CannonStats.
	DefenseStats getCannonStats(int level);
	// BarracksStats encapsulates related behavior and state.
	struct BarracksStats { int capAdd; int hp; };
	// Returns the BarracksStats.
	BarracksStats getBarracksStats(int level);
	// TrainingCampStats encapsulates related behavior and state.
	struct TrainingCampStats { int hp; };
	// Returns the TrainingCampStats.
	TrainingCampStats getTrainingCampStats(int level);
	
	// LaboratoryStats encapsulates related behavior and state.
	
	struct LaboratoryStats { int hp; };
	// Returns the LaboratoryStats.
	LaboratoryStats getLaboratoryStats(int level);
	// Returns the BuildLimit.
	int getBuildLimit(int id, int townHallLevel);
	// Returns whether UpgradeAllowed is true.
	bool isUpgradeAllowed(int id, int nextLevel, int townHallLevel, int maxBarracksLevel);

	
	// Returns the TroopResearchTimeSec.

	
	int getTroopResearchTimeSec(int unitId, int targetLevel);
	// Returns the TroopResearchCostElixir.
	int getTroopResearchCostElixir(int unitId, int targetLevel);
}