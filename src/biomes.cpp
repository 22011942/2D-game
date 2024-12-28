#include "biomes.h"
#include "SFML/Graphics.hpp"
#include "mapGen.h"

const sf::Color podzol = sf::Color(255, 239, 0);

void plainsBiomes(biomes selectedBiome, sf::Color *blockColor, float blockX, float blockY) { // Normal case sparse trees
    if (selectedBiome == SNOWY_PLAINS) { // plains but with snow

    } else if (selectedBiome == PLAINS) { // plains

    } else if (selectedBiome == SUNFLOWER_PLAINS) { // plains but with lots of sunflowers

    }
}

void taigaBiomes(biomes selectedBiome, sf::Color *blockColor, float blockX, float blockY) { // spruce and pine woods little grass, dense trees
    if (selectedBiome == SNOWY_TAIGA) { // taiga biome but with snow

    } else if (selectedBiome == TAIGA) { // normal

    } else if (selectedBiome == OLD_GROWTH_PINE_TAIGA) { // pine trees taller trees

    } else if (selectedBiome == OLD_GROWTH_SPRUCE_TAIGA) { // spruce trees taller trees

    }
}   

void forestBiomes(biomes selectedBiome, sf::Color *blockColor, float blockX, float blockY) { // mostly oak, but can also have birch, dense trees
    if (selectedBiome == FOREST) { // normal

    } else if (selectedBiome == DARK_FOREST) { // Dark oak forest

    } else if (selectedBiome == BIRCH_FOREST) { // birch forest

    } else if (selectedBiome == FLOWER_FOREST) { // normal forest but lots of flowers

    } else if (selectedBiome == OLD_GROWTH_BIRCH_FOREST) { // tall birch trees everywhere 

    }

}

void jungleBiomes(biomes selectedBiome, sf::Color *blockColor, float blockX, float blockY) { // high vegetation, jungle trees, fruit
    if (selectedBiome == JUNGLE) { // normal

    } else if (selectedBiome == BAMBOO_JUNGLE) { //few jungle trees mostly bamboo everywhere

    } else if (selectedBiome == SPARSE_JUNGLE) { // normal jungle just much less vegetation

    }

}

void savannaBiomes(biomes selectedBiome, sf::Color *blockColor, float blockX, float blockY) { //sparse trees, acacia, dead type grass
    if (selectedBiome == SAVANNA) { // normal

    } else if (selectedBiome == WINDSWEPT_SAVANNA) { // fewer trees then normal

    }

}

void iceSpikesBiome(biomes selectedBiome, sf::Color *blockColor, float blockX, float blockY) { // spikes of ice, snow and ice as the terrain
    

}

void snowyTundraBiome(biomes selectedBiome, sf::Color *blockColor, float blockX, float blockY) { // sparse spruce trees mostly snow landsacpe

}

void desertBiome(biomes selectedBiome, sf::Color *blockColor, float blockX, float blockY) { // no trees, sand and sandstone, cactus

}

void snowySlopesBiome(biomes selectedBiome, sf::Color *blockColor, float blockX, float blockY) { // no trees just snow and ice

}

void badlandsBiome(biomes selectedBiome, sf::Color *blockColor, float blockX, float blockY) { // almost no trees, acacia, looks like mc mesa, cactus different colored sands

}

void plateauBiome(biomes selectedBiome, sf::Color *blockColor, float blockX, float blockY) { // acacia trees, sparse

}

void shatteredBiome(biomes selectedBiome, sf::Color *blockColor, float blockX, float blockY) { // acacia trees, sparse


}

void peaksBiome(biomes selectedBiome, sf::Color *blockColor, float blockX, float blockY) { // pretty much no tree depends on

}

void biomeEffects(biomes selectedBiome, sf::Color *blockColor, float blockX, float blockY) {
    switch (selectedBiome)
    {
    case SNOWY_PLAINS:
        plainsBiomes(selectedBiome, blockColor, blockX, blockY);
        break;
    case ICE_SPIKES:
        iceSpikesBiome(selectedBiome, blockColor, blockX, blockY);
        break;
    case SNOWY_TUNDRA:
        snowyTundraBiome(selectedBiome, blockColor, blockX, blockY);
        break;
    case SNOWY_TAIGA:
        taigaBiomes(selectedBiome, blockColor, blockX, blockY);
        break;
    case TAIGA:
        taigaBiomes(selectedBiome, blockColor, blockX, blockY);
        break;
    case PLAINS:
        plainsBiomes(selectedBiome, blockColor, blockX, blockY);
        break;
    case FOREST:
        forestBiomes(selectedBiome, blockColor, blockX, blockY);
        break;
    case OLD_GROWTH_SPRUCE_TAIGA:
        taigaBiomes(selectedBiome, blockColor, blockX, blockY);
        break;
    case OLD_GROWTH_PINE_TAIGA:
        taigaBiomes(selectedBiome, blockColor, blockX, blockY);
        break;
    case FLOWER_FOREST:
        forestBiomes(selectedBiome, blockColor, blockX, blockY);
        break;
    case SUNFLOWER_PLAINS:
        plainsBiomes(selectedBiome, blockColor, blockX, blockY);
        break;
    case BIRCH_FOREST:
        forestBiomes(selectedBiome, blockColor, blockX, blockY);
        break;
    case OLD_GROWTH_BIRCH_FOREST:
        forestBiomes(selectedBiome, blockColor, blockX, blockY);
        break;
    case DARK_FOREST:
        forestBiomes(selectedBiome, blockColor, blockX, blockY);
        break;
    case SAVANNA:
        savannaBiomes(selectedBiome, blockColor, blockX, blockY);
        break;
    case JUNGLE:
        jungleBiomes(selectedBiome, blockColor, blockX, blockY);
        break;
    case SPARSE_JUNGLE:
        jungleBiomes(selectedBiome, blockColor, blockX, blockY);
        break;
    case BAMBOO_JUNGLE:
        jungleBiomes(selectedBiome, blockColor, blockX, blockY);
        break;
    case DESERT:
        desertBiome(selectedBiome, blockColor, blockX, blockY);
        break;
    case SNOWY_SLOPES:
        snowySlopesBiome(selectedBiome, blockColor, blockX, blockY);
        break;
    case BADLANDS:
        badlandsBiome(selectedBiome, blockColor, blockX, blockY);
        break;
    case PLATEAU:
        plateauBiome(selectedBiome, blockColor, blockX, blockY);
        break;
    case SHATTERED:
        shatteredBiome(selectedBiome, blockColor, blockX, blockY);
        break;
    case WINDSWEPT_SAVANNA:
        savannaBiomes(selectedBiome, blockColor, blockX, blockY);
        break;
    case PEAKS:
        peaksBiome(selectedBiome, blockColor, blockX, blockY);
        break;
    
    default:
        break;
    }
    
}