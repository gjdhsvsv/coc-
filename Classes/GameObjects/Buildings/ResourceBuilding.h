// File: ResourceBuilding.h
// Brief: Declares the ResourceBuilding component.
#pragma once
#include "GameObjects/Buildings/Building.h"
#include "Managers/ConfigManager.h"
#include "Managers/ResourceManager.h"
#include "cocos2d.h"
#include <algorithm>
#include <cmath>

// ElixirCollector encapsulates related behavior and state.

class ElixirCollector : public Building {
public:
    ElixirCollector() { image = "buildings/buildings3.png"; }
    cocos2d::Label* promptLabel = nullptr;
    void setupStats(int level) {
        auto st = ConfigManager::getElixirCollectorStats(level);
        ratePerHour = st.ratePerHour;
        capacity = st.capacity;
        chunkMinutes = st.chunkMinutes;
        hpMax = st.hp;
        if (hp > hpMax) hp = hpMax;
    }
    void updateProduction(float dt, float timeScale) {
        float add = ratePerHour * (timeScale * dt / 3600.0f);
        stored = std::min((float)capacity, stored + add);
    }
    bool canCollect() const {
        
        
        const int cap = ResourceManager::getElixirCap();
        const int cur = ResourceManager::getElixir();
        const int deliverMax = std::max(0, cap - cur);
        const int deliverable = std::min(deliverMax, (int)std::floor(stored));

        
        const int threshold = std::max(1, (int)std::ceil((float)cap * 0.01f));
        return deliverable >= threshold;
    }

    int collect(bool ignoreThreshold = false) {
        const int cap = ResourceManager::getElixirCap();
        const int cur = ResourceManager::getElixir();
        const int deliverMax = std::max(0, cap - cur);
        int deliver = std::min(deliverMax, (int)std::floor(stored));
        const int threshold = std::max(1, (int)std::ceil((float)cap * 0.01f));

        
        if (!ignoreThreshold && deliver < threshold) return 0;
        if (deliver > 0) {
            ResourceManager::addElixir(deliver);
            stored -= deliver;
        }
        return deliver;
    }

    void manageCollectPrompt(cocos2d::Node* parent, cocos2d::Sprite* sprite) {
        bool show = canCollect();
        if (show) {
            if (!promptLabel) {
                promptLabel = cocos2d::Label::createWithSystemFont("Collect", "Arial", 16);
                promptLabel->setColor(cocos2d::Color3B::BLACK);
                parent->addChild(promptLabel, 50);
            }
            if (promptLabel && sprite) {
                auto P = sprite->getPosition();
                promptLabel->setPosition(P + cocos2d::Vec2(0, 40));
            }
        }
        else {
            if (promptLabel) {
                promptLabel->removeFromParent();
                promptLabel = nullptr;
            }
        }
    }
};
// ElixirStorage encapsulates related behavior and state.
class ElixirStorage : public Building {
public:
    ElixirStorage() { image = "buildings/buildings4.png"; }
    int capAdd = 0;
    int capApplied = 0;
    void setupStats(int level) {
        auto st = ConfigManager::getElixirStorageStats(level);
        capAdd = st.capAdd;
        hpMax = st.hp;
        if (hp > hpMax) hp = hpMax;
    }
    void applyCap() {
        int currentCap = ResourceManager::getElixirCap();
        int delta = capAdd - capApplied;
        if (delta != 0) {
            ResourceManager::setElixirCap(currentCap + delta);
            capApplied = capAdd;
        }
    }
};
// GoldMine encapsulates related behavior and state.
class GoldMine : public Building {
public:
    GoldMine() { image = "buildings/buildings5.png"; }
    cocos2d::Label* promptLabel = nullptr;
    void setupStats(int level) {
        auto st = ConfigManager::getGoldMineStats(level);
        ratePerHour = st.ratePerHour;
        capacity = st.capacity;
        chunkMinutes = st.chunkMinutes;
        hpMax = st.hp;
        if (hp > hpMax) hp = hpMax;
    }
    void updateProduction(float dt, float timeScale) {
        float add = ratePerHour * (timeScale * dt / 3600.0f);
        stored = std::min((float)capacity, stored + add);
    }
        bool canCollect() const {
        
        
        const int cap = ResourceManager::getGoldCap();
        const int cur = ResourceManager::getGold();
        const int deliverMax = std::max(0, cap - cur);
        const int deliverable = std::min(deliverMax, (int)std::floor(stored));

        
        const int threshold = std::max(1, (int)std::ceil((float)cap * 0.01f));
        return deliverable >= threshold;
    }
        int collect(bool ignoreThreshold = false) {
        const int cap = ResourceManager::getGoldCap();
        const int cur = ResourceManager::getGold();
        const int deliverMax = std::max(0, cap - cur);
        int deliver = std::min(deliverMax, (int)std::floor(stored));
        const int threshold = std::max(1, (int)std::ceil((float)cap * 0.01f));

        
        if (!ignoreThreshold && deliver < threshold) return 0;
        if (deliver > 0) {
            ResourceManager::addGold(deliver);
            stored -= deliver;
        }
	        return deliver;
	    }
    void manageCollectPrompt(cocos2d::Node* parent, cocos2d::Sprite* sprite) {
        bool show = canCollect();
        if (show) {
            if (!promptLabel) {
                promptLabel = cocos2d::Label::createWithSystemFont("Collect", "Arial", 16);
                promptLabel->setColor(cocos2d::Color3B::BLACK);
                parent->addChild(promptLabel, 50);
            }
            if (promptLabel && sprite) {
                auto P = sprite->getPosition();
                promptLabel->setPosition(P + cocos2d::Vec2(0, 40));
            }
        }
        else {
            if (promptLabel) {
                promptLabel->removeFromParent();
                promptLabel = nullptr;
            }
        }
    }
};
// GoldStorage encapsulates related behavior and state.
class GoldStorage : public Building {
public:
    GoldStorage() { image = "buildings/buildings6.png"; }
    int capAdd = 0;
    int capApplied = 0;
    void setupStats(int level) {
        auto st = ConfigManager::getGoldStorageStats(level);
        capAdd = st.capAdd;
        hpMax = st.hp;
        if (hp > hpMax) hp = hpMax;
    }
    void applyCap() {
        int currentCap = ResourceManager::getGoldCap();
        int delta = capAdd - capApplied;
        if (delta != 0) {
            ResourceManager::setGoldCap(currentCap + delta);
            capApplied = capAdd;
        }
    }
};