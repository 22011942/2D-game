#include "perlinNoise.h"
#include <ctime>
#include <random>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "biomes.h"
#include "structureSpawn.h"
#include "mapGen.h"
#include <algorithm>
#include <unordered_map>
#include <utility>

const int CHUNK_SIZE = 16;
int topBlock = 0;
double treeSpawnRate;

biomes currentBiome;

typedef enum {
    SANDb, DIRTb, ROCKb, WATERb, LAVAb, DARK_DIRTb, CLAYb, CAVEb, GRASSb, AIRb
} blockTypes;


void middleBiome (float temperature, float humidity);
void biomeGen(float continentalness, float erosion, float temperature, float humidity);

float multiNoise(float blockX, float blockY, float frequency, float amplitude) {
    float value {0};

    // Generate height value using multiple octaves of Perlin noise

    for (int i = 0; i < 12; i++) { // 12 octaves
        float noiseX = blockX * frequency / 400;
        float noiseY = blockY * frequency / 400;
        value += perlin(noiseX, noiseY) * amplitude;
        frequency *= 2.0f; // Increase frequency
        amplitude /= 2.0f;  // Decrease amplitude
    }
    //std::cout << "value: " << value << std::endl;
    value *= 1.2f; // Adjust contrast
    value = std::clamp(value, -1.0f, 1.0f); // Clamp values between -1.0 and 1.0
    return value;
}


std::string biomeToString(biomes biome) {
    switch (biome) {
        case SNOWY_PLAINS: return "SNOWY_PLAINS";
        case ICE_SPIKES: return "ICE_SPIKES";
        case SNOWY_TUNDRA: return "SNOWY_TUNDRA";
        case SNOWY_TAIGA: return "SNOWY_TAIGA";
        case TAIGA: return "TAIGA";
        case PLAINS: return "PLAINS";
        case FOREST: return "FOREST";
        case OLD_GROWTH_SPRUCE_TAIGA: return "OLD_GROWTH_SPRUCE_TAIGA";
        case OLD_GROWTH_PINE_TAIGA: return "OLD_GROWTH_PINE_TAIGA";
        case FLOWER_FOREST: return "FLOWER_FOREST";
        case SUNFLOWER_PLAINS: return "SUNFLOWER_PLAINS";
        case BIRCH_FOREST: return "BIRCH_FOREST";
        case OLD_GROWTH_BIRCH_FOREST: return "OLD_GROWTH_BIRCH_FOREST";
        case DARK_FOREST: return "DARK_FOREST";
        case SAVANNA: return "SAVANNA";
        case JUNGLE: return "JUNGLE";
        case SPARSE_JUNGLE: return "SPARSE_JUNGLE";
        case BAMBOO_JUNGLE: return "BAMBOO_JUNGLE";
        case DESERT: return "DESERT";
        case SNOWY_SLOPES: return "SNOWY_SLOPES";
        case BADLANDS: return "BADLANDS";
        case PLATEAU: return "PLATEAU";
        case SHATTERED: return "SHATTERED";
        case WINDSWEPT_SAVANNA: return "WINDSWEPT_SAVANNA";
        case PEAKS: return "PEAKS";
        default: return "UNKNOWN_BIOME";
    }
}

bool grassCheck(int y, int x, std::vector<sf::Vertex> air) {
    for (size_t indx = 0; indx < air.size(); indx += 4) {
        if (air[indx].position.y == y && air[indx].position.x == x) {
            return true;
        }
    }
    return false;
}


bool surfaceCollisionCheck(int y, int x, std::vector<sf::Vertex> air) {
    for (size_t indx = 0; indx < air.size(); indx += 4) {
        if ((air[indx].position.y == y + BLOCK_SIZE && air[indx].position.x == x) || (air[indx].position.y == y - BLOCK_SIZE && air[indx].position.x == x) || (air[indx].position.y == y + BLOCK_SIZE && air[indx].position.x == x - BLOCK_SIZE) || (air[indx].position.y == y + BLOCK_SIZE && air[indx].position.x == x + BLOCK_SIZE)) {
            return true;
        }
    }
    return false;
}


void generateChunkImprov(int chunkX, int chunkY, std::unordered_map<std::pair<int, int>, ChunkData, PairHash> *chunks) {
    std::unordered_map<int, int> underGroundValues;
    //sf::VertexArray chunk(sf::Quads);
    //sf::VertexArray air(sf::Quads);

    ChunkData newChunk;


    std::map<std::pair<int, int>, sf::RectangleShape> collisionBlocks;

    for (int blockX = 0; blockX < CHUNK_SIZE; blockX++) {

        int worldX = chunkX * CHUNK_SIZE + blockX;

        //std::cout << "worldX: " << worldX << std::endl;

        float continentalness = multiNoise(worldX * 0.8, 0, 0.15f, 1.0f);
        float erosion = multiNoise(worldX * 0.6, 0, 0.6f, 0.8f);
        float peaksValleys = multiNoise(worldX, 0, 1.2f, 0.9f);
        float temperature = multiNoise(worldX * 0.3, 0, 4.4f, 0.75f);
        float humidity = multiNoise(worldX * 0.5, 0, 5.25f, 1.0f);

        //std::cout << "continentalness: " << continentalness << std::endl;

        biomeGen(continentalness, erosion, temperature, humidity);
        //std::cout << "Current biome: " << biomeToString(currentBiome) << "  continentalness: " << continentalness << "   erosion: " << erosion << "   temperature: " << temperature << "   humidity: " << humidity << std::endl;


        continentalness = std::clamp((continentalness + 1.0f) * 0.5f, 0.0f, 1.0f);
        erosion = std::clamp((erosion + 1.0f) * 0.5f, 0.0f, 1.0f);
        peaksValleys = std::clamp((peaksValleys + 1.0f) * 0.5f, 0.0f, 1.0f);
        //temperature = std::clamp((temperature + 1.0f) * 0.5f, 0.0f, 1.0f);
        //humidity = std::clamp((humidity + 1.0f) * 0.5f, 0.0f, 1.0f);


        float baseHeight = 500 + MAX_HEIGHT * (0.6f * continentalness);

        float erosionEffect = 0.5f + 0.5f * erosion;
        baseHeight *= erosionEffect;

        float peaksEffect = 1.0f + 0.5f * peaksValleys;

        float groundHeight = baseHeight * peaksEffect;

        groundHeight = std::clamp(groundHeight, 0.0f, static_cast<float>(MAX_HEIGHT));

        for (int blockY = 0; blockY < CHUNK_SIZE; blockY++) {

            
            int worldY = chunkY * CHUNK_SIZE + blockY;

            bool isGround = (worldY >= MAX_HEIGHT - groundHeight);
            //std:: cout << " height: " << MAX_HEIGHT - (int)groundHeight << std::endl;
            underGroundValues[worldX] = MAX_HEIGHT - (int)groundHeight;
            sf::Color blockColor = sf::Color::Transparent;

            if (isGround) {

                float caves = multiNoise(worldX * 0.4f, worldY, 20.0f, 1.0f);
                float waterCaves = multiNoise(worldX * 0.8f, worldY * 2.0f, 25.7f, 1.2f);
                float lavaCaves = multiNoise(worldX * 0.2f, worldY * 0.7f, 17.0f, 1.3f);
                float middleCaves = multiNoise(worldX * 0.4f, worldY, 30.0f, 2.0f);

                if (worldY >= MAX_HEIGHT - groundHeight) {
                    float stoneInDirt = multiNoise(worldX, worldY, 80.0f, 1.0f);
                    float dirtInStone = multiNoise(worldX * 0.9f, worldY , 90.0f, 1.0f);
                    float clay = multiNoise(worldX * 0.5f, worldY * 2.0f, 50.0f, 1.0f);
                    float upperCaves = multiNoise(worldX * 5.20f, worldY, 3.0f, 1.0f);
                    //float surfaceCaves = multiNoise(worldX * 3, worldY * 2, 2.2f, 0.6f);

                    //float DirtInStone = multiNoise(worldX, worldY, 80.0f, 1.0f);
                    // Deeper layers (stone)

                    //makes sure that when density is done the rock can only be placed where density is greater then 0 to avoid going over whats done
                    if (worldY < MAX_HEIGHT - groundHeight + 100 && multiNoise(worldX, worldY * 0.85f, 1.0f, 1.0f) > 0) {
                        if (stoneInDirt < -0.38) {
                            
                            blockColor = ROCK;
                        } else {
                            blockColor = DIRT;
                            //chunkGrassLayer[worldX][worldY] = DIRTb;
                        }

                        if (clay < -0.6) {
                            blockColor = CLAY;
                        }

                        if (upperCaves < -0.4) {
                            blockColor = DARK_DIRT;
                        }

                        //if (surfaceCaves < -0.12) {
                        //    blockColor = DARK_DIRT;
                        //}

                    //this is the normal case
                    } else if (worldY > MAX_HEIGHT - groundHeight + 100 && worldY < MAX_HEIGHT - groundHeight + 120) {
                        if (stoneInDirt < -0.3) {
                            blockColor = ROCK;
                        } else {
                            blockColor = DIRT;
                            //chunkGrassLayer[worldX][worldY] = DIRTb;
                        }

                        if (clay < -0.6) {
                            blockColor = CLAY;
                        }

                        if (caves < -0.7) { // water cave
                            blockColor = WATER;
                        }

                        if (upperCaves < -0.5) {
                            blockColor = DARK_DIRT;
                        }

                        //if (surfaceCaves < -0.12) {
                        //    blockColor = DARK_DIRT;
                        //}

                    } else if (worldY > MAX_HEIGHT - groundHeight + 120 && worldY < MAX_HEIGHT - groundHeight + 155) {
                        if (stoneInDirt < 0.1) {
                            blockColor = ROCK;
                        } else {
                            blockColor = DIRT;
                        }

                        if (clay < -0.6) {
                            blockColor = CLAY;
                        }

                        if (caves < -0.5) { // water cave
                            blockColor = WATER;
                        }

                        if (upperCaves < -0.6) {
                            blockColor = DARK_DIRT;
                        }

                        //if (surfaceCaves < -0.2) {
                        //    blockColor = DARK_DIRT;
                        //}


                    } else if (worldY > MAX_HEIGHT - groundHeight + 155) {
                        if (dirtInStone < 0.4) {
                            blockColor = ROCK;
                        } else {
                            blockColor = DIRT;
                        }

                        if (caves < -0.5) { // water cave
                            blockColor = WATER;
                        }

                        if (upperCaves < -0.6 && worldY < MAX_HEIGHT - groundHeight + 200) {
                            blockColor = DARK_DIRT;
                        }

                        if (middleCaves < -0.5) {
                            blockColor = CAVE;
                        }

                    }

                } 

                biomeEffects(currentBiome, &blockColor, blockX, blockY, &treeSpawnRate);
            

                if (worldY >= MAX_HEIGHT - groundHeight + 200 && worldY < MAX_HEIGHT - groundHeight + 400) {
                    //Caves

                    if (waterCaves < -0.6) { // water cave
                        blockColor = WATER;
                    }
                    
                    if (caves < -0.3) { // was -0.05
                        //r = CAVE.r; g = CAVE.g; b = CAVE.b;
                        blockColor = CAVE;
                    }

                    if (middleCaves < -0.5) {
                        blockColor = CAVE;
                    }

                }

                if (worldY >= MAX_HEIGHT - groundHeight + 400) {

                    if (caves < -0.3) { // was -0.05
                        //r = CAVE.r; g = CAVE.g; b = CAVE.b;
                        blockColor = CAVE;
                    }

                    if (lavaCaves < -0.5) { // lava cave
                        blockColor = LAVA;
                    }
                }
            } 

            if (blockColor != sf::Color::Transparent) {
                newChunk.chunkInfo.addQuad(worldX, worldY, blockColor);

            } else {
                newChunk.airInChunk.addQuad(worldX, worldY, blockColor);
            }
        }
    }


    for (size_t indx = 0; indx < newChunk.chunkInfo.vertices.size(); indx+=4) {
        if (newChunk.chunkInfo.vertices[indx].color == DIRT) {
            if (grassCheck(newChunk.chunkInfo.vertices[indx].position.y - BLOCK_SIZE, newChunk.chunkInfo.vertices[indx].position.x, newChunk.airInChunk.vertices)) { // && chunk[indx].position.y <= (underGroundValues[chunk[indx].position.x / BLOCK_SIZE]) * BLOCK_SIZE
                float treeSpawns = multiNoise(newChunk.chunkInfo.vertices[indx].position.x * 0.5f, newChunk.chunkInfo.vertices[indx].position.y * 2.0f, 50.0f, 1.0f);

                newChunk.chunkInfo.vertices[indx].color = GRASS;
                newChunk.chunkInfo.vertices[indx + 1].color = GRASS;
                newChunk.chunkInfo.vertices[indx + 2].color = GRASS;
                newChunk.chunkInfo.vertices[indx + 3].color = GRASS;

                if (treeSpawns < treeSpawnRate) {
                    spawnTreeAt(newChunk.chunkInfo.vertices[indx].position.x + BLOCK_SIZE, newChunk.chunkInfo.vertices[indx].position.y, &newChunk);
                }
            }
        }
    }


    for (size_t indx = 0; indx < newChunk.chunkInfo.vertices.size(); indx+=4) {
        if (surfaceCollisionCheck(newChunk.chunkInfo.vertices[indx].position.y, newChunk.chunkInfo.vertices[indx].position.x, newChunk.airInChunk.vertices) && newChunk.chunkInfo.vertices[indx].color != TRUNK_BLOCK && newChunk.chunkInfo.vertices[indx].color != LEAVES_BLOCK) {

            float minX = newChunk.chunkInfo.vertices[indx].position.x;
            float minY = newChunk.chunkInfo.vertices[indx].position.y;
            float maxX = newChunk.chunkInfo.vertices[indx].position.x;
            float maxY = newChunk.chunkInfo.vertices[indx].position.y;

            for (size_t i = 1; i < 4; ++i) {
                sf::Vector2f point = newChunk.chunkInfo.vertices[indx + i].position;
                if (point.x < minX) minX = point.x;
                if (point.y < minY) minY = point.y;
                if (point.x > maxX) maxX = point.x;
                if (point.y > maxY) maxY = point.y;
            }

            sf::FloatRect rect(minX, minY, maxX - minX, maxY - minY);

            sf::RectangleShape block;

            block.setSize(rect.getSize());
            block.setPosition(rect.getPosition());

            //std::cout << "block pos x: " << newChunk.chunkInfo.vertices[indx].position.x <<  " block pos y: " << newChunk.chunkInfo.vertices[indx].position.y << std::endl;
            //if (newChunk.chunkInfo.vertices[indx].position.y == 3752) {
            //    std::cout << " found" << std::endl;
            //}
            
            collisionBlocks[{newChunk.chunkInfo.vertices[indx].position.x, newChunk.chunkInfo.vertices[indx].position.y}] = block;

        }
    }

    //newChunk.chunkInfo = chunk;
    //newChunk.airInChunk = air;
    newChunk.collisionBlocks = collisionBlocks;

    (*chunks)[{chunkX, chunkY}] = newChunk;
}

void middleBiome (float temperature, float humidity) {
    float weirdness = multiNoise(temperature, humidity, 1.0f, 1.0f);

    if (temperature >= -1 && temperature < -0.7) {
        //level 0 
        if (humidity >= -1 && humidity < -0.7) {
            if (weirdness < 0) {
                //snowy plains
                currentBiome = SNOWY_PLAINS;
            } else if (weirdness > 0) {
                //ice spikes
                currentBiome = ICE_SPIKES;
            }
        } else if (humidity >= -0.7 && humidity < -0.3) {
            //snowy plains
            currentBiome = SNOWY_PLAINS;
        } else if (humidity >= -0.3 && humidity < 0.3) {
            if (weirdness < 0) {
                //snowy tundra
                currentBiome = SNOWY_TUNDRA;
            } else if (weirdness > 0) {
                //snowy taiga
                currentBiome = SNOWY_TAIGA;
            }
        } else if (humidity >= 0.3 && humidity < 0.7) {
            //snowy taiga
            currentBiome = SNOWY_TAIGA;
        } else if (humidity >= 0.7 && humidity < 1) {
            //Taiga
            currentBiome = TAIGA;
        }
    } else if (temperature >= -0.7 && temperature < -0.2) {
        //level 1
        if (humidity >= 1 && humidity < -0.3) {
            //plains
            currentBiome = PLAINS;
        } else if (humidity >= -0.3 && humidity < 0.3) {
            //forest
            currentBiome = FOREST;
        } else if (humidity >= 0.3 && humidity < 0.7) {
            //Taiga
            currentBiome = TAIGA;
        } else if (humidity >= 0.7 && humidity <= 1) {
            if (weirdness < 0) {
                //old growth spruce taiga
                currentBiome = OLD_GROWTH_SPRUCE_TAIGA;
            } else if (weirdness > 0) {
                //old growth pine taiga
                currentBiome = OLD_GROWTH_PINE_TAIGA;
            }
        }
    } else if (temperature >= -0.2 && temperature < 0.5) {
        //level 2
        if (humidity >= -1 && humidity < -0.7) {
            if (weirdness < 0) {
                //Flower forest
                currentBiome = FLOWER_FOREST;
            } else if (weirdness > 0) {
                //Sunflower plains
                currentBiome = SUNFLOWER_PLAINS;
            }
        } else if (humidity >= -0.7 && humidity < -0.3) {
            //plains
            currentBiome = PLAINS;
        } else if (humidity >= -0.3 && humidity < 0.3) {
            // forest
            currentBiome = FOREST;
        } else if (humidity >= 0.3 && humidity < 0.7) {
            if (weirdness < 0) {
                //Birch forest
                currentBiome = BIRCH_FOREST;
            } else if (weirdness > 0) {
                //Old growth birch forest
                currentBiome = OLD_GROWTH_BIRCH_FOREST;
            }
        } else if (humidity >= 0.7 && humidity <= 1) {
            //dark forest
            currentBiome = DARK_FOREST;
        }
    } else if (temperature >= 0.5 && temperature < 0.8) {
        //level 3
        if (humidity >= 1 && humidity < -0.3) {
            //Savanna
            currentBiome = SAVANNA;
        } else if (humidity >= -0.3 && humidity < 0.3) {
            if (weirdness < 0) {
                //Forest
                currentBiome = FOREST;
            } else if (weirdness > 0) {
                //Plains
                currentBiome = PLAINS;
            }
        } else if (humidity >= 0.3 && humidity < 0.7) {
            if (weirdness < 0) {
                //Jungle
                currentBiome = JUNGLE;
            } else if (weirdness > 0) {
                //Sparse jungle
                currentBiome = SPARSE_JUNGLE;
            }
        } else if (humidity >= 0.7 && humidity <= 1) {
            if (weirdness < 0) {
                //Jungle
                currentBiome = JUNGLE;
            } else if (weirdness > 0) {
                //Bamboo jungle
                currentBiome = BAMBOO_JUNGLE;
            }
        }
    } else if (temperature >= 0.8 && temperature <= 1) {
        //desert
        currentBiome = DESERT;
    }
}

void biomeGen(float continentalness, float erosion, float temperature, float humidity) {
    
    if (erosion >= -1 && erosion < -0.78) {
            //level 0
            //peak biome
            currentBiome = PEAKS;
    } else if (erosion >= -0.78 && erosion < -0.375) {
        //level 1
        if (continentalness < 0) {
            if (temperature >= -1 && temperature < -0.4) {
                //slope biome COLD
                currentBiome = SNOWY_SLOPES;
            } else if (temperature >= -0.4 && temperature < 0.4) {
                //Middle biome
                middleBiome(temperature, humidity);
            } else if (temperature >= 0.4 && temperature < 1) {
                //Badlands biome HOT
                currentBiome = BADLANDS;
            }
        } else if (continentalness > 0) {
            //peak biome
            currentBiome = PEAKS;
        }
    } else if (erosion >= -0.375 && erosion < -0.2225) {
        //level 2
        if (continentalness < 0) {
            //middle biome
            middleBiome(temperature, humidity);
        } else if (continentalness > 0) {
            //plateau biome
            currentBiome = PLATEAU;
        }
    } else if (erosion >= -0.2225 && erosion < 0.05) {
        //level 3
        if (continentalness < 0) {
            //middle biome
            middleBiome(temperature, humidity);
        } else if (continentalness > 0 && continentalness < 0.5) {
            if (temperature < 0) {
                //middle biome
                middleBiome(temperature, humidity);
            } else if (temperature > 0) {
                //badlands biome
                currentBiome = BADLANDS;
            }
        } else if (continentalness >= 0.5 && continentalness <= 1) {
            //plateau biome
            currentBiome = PLATEAU;
        }
    } else if (erosion >= 0.05 && erosion < 0.45) {
        //level 4
        //middle biome
        middleBiome(temperature, humidity);
    } else if (erosion >= 0.45 && erosion < 0.55) {
        //level 5
        if (continentalness < 0) {
            if (temperature < 0) {
                //shattered biome
                currentBiome = SHATTERED;
            } else if (temperature > 0) {
                //windswept savanna
                currentBiome = SAVANNA;
            }
        } else if (continentalness > 0) {
            //shattered biome
            currentBiome = SHATTERED;
        }
    } else if (erosion >= 0.55 && erosion <= 1) {
        //level 6
        //middle biome
        middleBiome(temperature, humidity);
    }
}