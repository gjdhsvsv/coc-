#pragma once
#include <functional>

struct Resources {
    int elixir = 1000;
    int gold = 1000;
    int population = 0;
};

class ResourceManager {
public:
    static const Resources& get();
    static int getElixir();
    static int getGold();
    static int getPopulation();
    static void setElixir(int v);
    static void setGold(int v);
    static void setPopulation(int v);
    static void addElixir(int v);
    static void addGold(int v);
    static void addPopulation(int v);
    static bool spendElixir(int v);
    static bool spendGold(int v);
    static bool spendPopulation(int v);
    static void reset();
    static void onChanged(const std::function<void(const Resources&)>& cb);
private:
    static void notify();
    static Resources _res;
    static std::function<void(const Resources&)> _callback;
};
