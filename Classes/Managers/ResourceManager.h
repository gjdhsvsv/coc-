// File: ResourceManager.h
// Brief: Declares the ResourceManager component.
#pragma once
#include <functional>

// Resources encapsulates related behavior and state.

struct Resources {
    int elixir = 5000;
    int gold = 5000;
    int population = 0;
    int elixirCap = 5000;
    int goldCap = 5000;
    int populationCap = 0;
};

// ResourceManager encapsulates related behavior and state.

class ResourceManager {
public:
    // TODO: Add a brief description.
    static const Resources& get();
    // Returns the Elixir.
    static int getElixir();
    // Returns the Gold.
    static int getGold();
    // Returns the Population.
    static int getPopulation();
    // Returns the ElixirCap.
    static int getElixirCap();
    // Returns the GoldCap.
    static int getGoldCap();
    // Returns the PopulationCap.
    static int getPopulationCap();
    // Sets the Elixir.
    static void setElixir(int v);
    // Sets the Gold.
    static void setGold(int v);
    // Sets the Population.
    static void setPopulation(int v);
    // Sets the ElixirCap.
    static void setElixirCap(int v);
    // Sets the GoldCap.
    static void setGoldCap(int v);
    // Sets the PopulationCap.
    static void setPopulationCap(int v);
    // Adds an item.
    static void addElixir(int v);
    // Adds an item.
    static void addGold(int v);
    // Adds an item.
    static void addPopulation(int v);
    // TODO: Add a brief description.
    static bool spendElixir(int v);
    // TODO: Add a brief description.
    static bool spendGold(int v);
    // TODO: Add a brief description.
    static bool spendPopulation(int v);
    // Resets state to defaults.
    static void reset();
    static void onChanged(const std::function<void(const Resources&)>& cb);
    
    // Adds an item.
    
    static void addPopulationCap(int amount);
   
// TODO: Add a brief description.
   
private:
    static void notify();
    static Resources _res;
    static std::function<void(const Resources&)> _callback;
    static int s_populationCap;
    static int s_population;
};