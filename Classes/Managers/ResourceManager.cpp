#include "Managers/ResourceManager.h"
#include <algorithm>

Resources ResourceManager::_res;
std::function<void(const Resources&)> ResourceManager::_callback;

const Resources& ResourceManager::get() { return _res; }
int ResourceManager::getElixir() { return _res.elixir; }
int ResourceManager::getGold() { return _res.gold; }
int ResourceManager::getPopulation() { return _res.population; }

void ResourceManager::setElixir(int v) { _res.elixir = std::max(0, v); notify(); }
void ResourceManager::setGold(int v) { _res.gold = std::max(0, v); notify(); }
void ResourceManager::setPopulation(int v) { _res.population = std::max(0, v); notify(); }

void ResourceManager::addElixir(int v) { setElixir(_res.elixir + v); }
void ResourceManager::addGold(int v) { setGold(_res.gold + v); }
void ResourceManager::addPopulation(int v) { setPopulation(_res.population + v); }

bool ResourceManager::spendElixir(int v) {
    if (v <= 0) return true;
    if (_res.elixir < v) return false;
    _res.elixir -= v;
    notify();
    return true;
}

bool ResourceManager::spendGold(int v) {
    if (v <= 0) return true;
    if (_res.gold < v) return false;
    _res.gold -= v;
    notify();
    return true;
}

bool ResourceManager::spendPopulation(int v) {
    if (v <= 0) return true;
    if (_res.population < v) return false;
    _res.population -= v;
    notify();
    return true;
}

void ResourceManager::reset() {
    _res = Resources();
    notify();
}

void ResourceManager::onChanged(const std::function<void(const Resources&)>& cb) {
    _callback = cb;
    notify();
}

void ResourceManager::notify() {
    if (_callback) _callback(_res);
}
