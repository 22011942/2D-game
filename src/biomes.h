#pragma once
#include "SFML/Graphics.hpp"

typedef enum {SNOWY_PLAINS, ICE_SPIKES, SNOWY_TUNDRA, SNOWY_TAIGA, TAIGA,
PLAINS, FOREST, OLD_GROWTH_SPRUCE_TAIGA, OLD_GROWTH_PINE_TAIGA, FLOWER_FOREST,
SUNFLOWER_PLAINS, BIRCH_FOREST, OLD_GROWTH_BIRCH_FOREST, DARK_FOREST,
SAVANNA, JUNGLE, SPARSE_JUNGLE, BAMBOO_JUNGLE, DESERT, SNOWY_SLOPES,
BADLANDS, PLATEAU, SHATTERED, WINDSWEPT_SAVANNA, PEAKS} biomes; // The biomes which can generate in the world

void biomeEffects(biomes selectedBiome, sf::Color *blockColor, float blockX, float blockY, double *treeSpawnRate);