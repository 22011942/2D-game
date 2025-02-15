#include "biomes.h"
#include "SFML/Graphics.hpp"
#include "mapGen.h"

const sf::Color podzol = sf::Color(255, 239, 0);

void plainsBiomes(biomes selectedBiome, sf::Color *blockColor, float blockX, float blockY, double *treeSpawnRate) { // Normal case sparse trees
    float tree = multiNoise(blockX, blockY,1.0f, 1.0f);
    (*treeSpawnRate) = SPARSE_TREES;
    if (selectedBiome == SNOWY_PLAINS) { // plains but with snow

    } else if (selectedBiome == PLAINS) { // plains
        
    } else if (selectedBiome == SUNFLOWER_PLAINS) { // plains but with lots of sunflowers

    }
}

void taigaBiomes(biomes selectedBiome, sf::Color *blockColor, float blockX, float blockY, double *treeSpawnRate) { // spruce and pine woods little grass, dense trees
    (*treeSpawnRate) = DENSE_TREES;
    if (selectedBiome == SNOWY_TAIGA) { // taiga biome but with snow

    } else if (selectedBiome == TAIGA) { // normal

    } else if (selectedBiome == OLD_GROWTH_PINE_TAIGA) { // pine trees taller trees

    } else if (selectedBiome == OLD_GROWTH_SPRUCE_TAIGA) { // spruce trees taller trees

    }
}   

void forestBiomes(biomes selectedBiome, sf::Color *blockColor, float blockX, float blockY, double *treeSpawnRate) { // mostly oak, but can also have birch, dense trees
    (*treeSpawnRate) = MEDIUM_TREES;
    if (selectedBiome == FOREST) { // normal

    } else if (selectedBiome == DARK_FOREST) { // Dark oak forest

    } else if (selectedBiome == BIRCH_FOREST) { // birch forest

    } else if (selectedBiome == FLOWER_FOREST) { // normal forest but lots of flowers

    } else if (selectedBiome == OLD_GROWTH_BIRCH_FOREST) { // tall birch trees everywhere 

    }

}

void jungleBiomes(biomes selectedBiome, sf::Color *blockColor, float blockX, float blockY, double *treeSpawnRate) { // high vegetation, jungle trees, fruit
    (*treeSpawnRate) = DENSE_TREES;
    if (selectedBiome == JUNGLE) { // normal

    } else if (selectedBiome == BAMBOO_JUNGLE) { //few jungle trees mostly bamboo everywhere

    } else if (selectedBiome == SPARSE_JUNGLE) { // normal jungle just much less vegetation

    }

}

void savannaBiomes(biomes selectedBiome, sf::Color *blockColor, float blockX, float blockY, double *treeSpawnRate) { //sparse trees, acacia, dead type grass
    (*treeSpawnRate) = SPARSE_TREES;
    if (selectedBiome == SAVANNA) { // normal

    } else if (selectedBiome == WINDSWEPT_SAVANNA) { // fewer trees then normal

    }

}

void iceSpikesBiome(biomes selectedBiome, sf::Color *blockColor, float blockX, float blockY, double *treeSpawnRate) { // spikes of ice, snow and ice as the terrain
    (*treeSpawnRate) = NO_TREES;

}

void snowyTundraBiome(biomes selectedBiome, sf::Color *blockColor, float blockX, float blockY, double *treeSpawnRate) { // sparse spruce trees mostly snow landsacpe
    (*treeSpawnRate) = SPARSE_TREES;
}

void desertBiome(biomes selectedBiome, sf::Color *blockColor, float blockX, float blockY, double *treeSpawnRate) { // no trees, sand and sandstone, cactus
    (*treeSpawnRate) = NO_TREES;
}

void snowySlopesBiome(biomes selectedBiome, sf::Color *blockColor, float blockX, float blockY, double *treeSpawnRate) { // no trees just snow and ice
    (*treeSpawnRate) = NO_TREES;
}

void badlandsBiome(biomes selectedBiome, sf::Color *blockColor, float blockX, float blockY, double *treeSpawnRate) { // almost no trees, acacia, looks like mc mesa, cactus different colored sands
    (*treeSpawnRate) = VERY_SPARSE_TREES;

}

void plateauBiome(biomes selectedBiome, sf::Color *blockColor, float blockX, float blockY, double *treeSpawnRate) { // acacia trees, sparse
    (*treeSpawnRate) = SPARSE_TREES;
}

void shatteredBiome(biomes selectedBiome, sf::Color *blockColor, float blockX, float blockY, double *treeSpawnRate) { // acacia trees, sparse
    (*treeSpawnRate) = SPARSE_TREES;

}

void peaksBiome(biomes selectedBiome, sf::Color *blockColor, float blockX, float blockY, double *treeSpawnRate) { // pretty much no tree depends on
    (*treeSpawnRate) = VERY_SPARSE_TREES;
}

void biomeEffects(biomes selectedBiome, sf::Color *blockColor, float blockX, float blockY, double *treeSpawnRate) {
    switch (selectedBiome)
    {
    case SNOWY_PLAINS:
        plainsBiomes(selectedBiome, blockColor, blockX, blockY, treeSpawnRate);
        break;
    case ICE_SPIKES:
        iceSpikesBiome(selectedBiome, blockColor, blockX, blockY, treeSpawnRate);
        break;
    case SNOWY_TUNDRA:
        snowyTundraBiome(selectedBiome, blockColor, blockX, blockY, treeSpawnRate);
        break;
    case SNOWY_TAIGA:
        taigaBiomes(selectedBiome, blockColor, blockX, blockY, treeSpawnRate);
        break;
    case TAIGA:
        taigaBiomes(selectedBiome, blockColor, blockX, blockY, treeSpawnRate);
        break;
    case PLAINS:
        plainsBiomes(selectedBiome, blockColor, blockX, blockY, treeSpawnRate);
        break;
    case FOREST:
        forestBiomes(selectedBiome, blockColor, blockX, blockY, treeSpawnRate);
        break;
    case OLD_GROWTH_SPRUCE_TAIGA:
        taigaBiomes(selectedBiome, blockColor, blockX, blockY, treeSpawnRate);
        break;
    case OLD_GROWTH_PINE_TAIGA:
        taigaBiomes(selectedBiome, blockColor, blockX, blockY, treeSpawnRate);
        break;
    case FLOWER_FOREST:
        forestBiomes(selectedBiome, blockColor, blockX, blockY, treeSpawnRate);
        break;
    case SUNFLOWER_PLAINS:
        plainsBiomes(selectedBiome, blockColor, blockX, blockY, treeSpawnRate);
        break;
    case BIRCH_FOREST:
        forestBiomes(selectedBiome, blockColor, blockX, blockY, treeSpawnRate);
        break;
    case OLD_GROWTH_BIRCH_FOREST:
        forestBiomes(selectedBiome, blockColor, blockX, blockY, treeSpawnRate);
        break;
    case DARK_FOREST:
        forestBiomes(selectedBiome, blockColor, blockX, blockY, treeSpawnRate);
        break;
    case SAVANNA:
        savannaBiomes(selectedBiome, blockColor, blockX, blockY, treeSpawnRate);
        break;
    case JUNGLE:
        jungleBiomes(selectedBiome, blockColor, blockX, blockY, treeSpawnRate);
        break;
    case SPARSE_JUNGLE:
        jungleBiomes(selectedBiome, blockColor, blockX, blockY, treeSpawnRate);
        break;
    case BAMBOO_JUNGLE:
        jungleBiomes(selectedBiome, blockColor, blockX, blockY, treeSpawnRate);
        break;
    case DESERT:
        desertBiome(selectedBiome, blockColor, blockX, blockY, treeSpawnRate);
        break;
    case SNOWY_SLOPES:
        snowySlopesBiome(selectedBiome, blockColor, blockX, blockY, treeSpawnRate);
        break;
    case BADLANDS:
        badlandsBiome(selectedBiome, blockColor, blockX, blockY, treeSpawnRate);
        break;
    case PLATEAU:
        plateauBiome(selectedBiome, blockColor, blockX, blockY, treeSpawnRate);
        break;
    case SHATTERED:
        shatteredBiome(selectedBiome, blockColor, blockX, blockY, treeSpawnRate);
        break;
    case WINDSWEPT_SAVANNA:
        savannaBiomes(selectedBiome, blockColor, blockX, blockY, treeSpawnRate);
        break;
    case PEAKS:
        peaksBiome(selectedBiome, blockColor, blockX, blockY, treeSpawnRate);
        break;
    
    default:
        break;
    }
    
}