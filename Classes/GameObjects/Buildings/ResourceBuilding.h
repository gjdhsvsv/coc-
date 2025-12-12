#pragma once
#include "GameObjects/Buildings/Building.h"

class ElixirCollector : public Building { public: ElixirCollector() { image = "buildings/buildings3.png"; } };
class ElixirStorage : public Building { public: ElixirStorage() { image = "buildings/buildings4.png"; } };
class GoldMine : public Building { public: GoldMine() { image = "buildings/buildings5.png"; } };
class GoldStorage : public Building { public: GoldStorage() { image = "buildings/buildings6.png"; } };