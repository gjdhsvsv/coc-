#pragma once

#include "cocos2d.h"
#include <cstdint>
#include <string>
#include <vector>

struct SaveMeta
{
    int slot = 0;
    bool exists = false;
    std::string name;
    std::string path;
    int64_t updatedAt = 0;
};

struct SaveBuilding
{
    int id = 0;
    int level = 1;
    int r = 0;
    int c = 0;
    int hp = 0;
    float stored = 0.0f;
};

struct SaveData
{
    int slot = 0;
    std::string name;
    int gold = 0;
    int elixir = 0;
    int population = 0;
    float timeScale = 1.0f;
    std::vector<SaveBuilding> buildings;
};

class SaveSystem
{
public:
    static void setCurrentSlot(int slot);
    static int getCurrentSlot();

    static void setBattleTargetSlot(int slot);
    static int getBattleTargetSlot();

    static std::string getSaveDir();
    static std::string getSavePath(int slot);
    static bool exists(int slot);
    static std::vector<SaveMeta> listAllSlots();

    static bool load(int slot, SaveData& outData);
    static bool save(const SaveData& data);
    static bool remove(int slot);
    static SaveData makeDefault(int slot, const std::string& name);

private:
    static constexpr int kMaxSlots = 20;
    static int s_currentSlot;
    static int s_battleTargetSlot;
};