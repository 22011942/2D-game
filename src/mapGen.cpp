#include "perlinNoise.h"
#include <ctime>
#include <random>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "biomes.h"

//float seed = static_cast<float>(std::time(nullptr));

const int BLOCK_SIZE = 8;
const int WORLD_HEIGHT = 10000;
const int MAX_HEIGHT = WORLD_HEIGHT / BLOCK_SIZE;
const int WORLD_WIDTH = 30000;
const int CHUNK_SIZE = 16;

biomes currentBiome;

struct Color {
    unsigned int r, g, b;
};

void setColor(Color& color,unsigned int r, unsigned int g, unsigned int b) {
    color.r = r;
    color.g = g;
    color.b = b;
}

float multiNoise(float blockX, float blockY, float frequency, float amplitude) {
    float value {0};

    // Generate height value using multiple octaves of Perlin noise

    for (int i = 0; i < 4; i++) { // 12 octaves
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

void middleBiome (float temperature, float humidity) {
    float weirdness = multiNoise(temperature, humidity, 1.0f, 1.0f);

    if (temperature >= -1 && temperature < -0.7) {
        //level 0 
        if (humidity >= -1 && humidity < -0.7) {
            if (weirdness >= -1 && weirdness < 0) {
                //snowy plains
                currentBiome = SNOWY_PLAINS;
            } else if (weirdness >= 0 && weirdness < 1) {
                //ice spikes
                currentBiome = ICE_SPIKES;
            }
        } else if (humidity >= -0.7 && humidity < -0.3) {
            //snowy plains
            currentBiome = SNOWY_PLAINS;
        } else if (humidity >= -0.3 && humidity < 0.3) {
            if (weirdness >= -1 && weirdness < 0) {
                //snowy tundra
                currentBiome = SNOWY_TUNDRA;
            } else if (weirdness >= 0 && weirdness < 1) {
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
        } else if (humidity >= 0.7 && humidity < 1) {
            if (weirdness >= -1 && weirdness < 0) {
                //old growth spruce taiga
                currentBiome = OLD_GROWTH_SPRUCE_TAIGA;
            } else if (weirdness >= 0 && weirdness < 1) {
                //old growth pine taiga
                currentBiome = OLD_GROWTH_PINE_TAIGA;
            }
        }
    } else if (temperature >= -0.2 && temperature < 0.5) {
        //level 2
        if (humidity >= -1 && humidity < -0.7) {
            if (weirdness >= -1 && weirdness < 0) {
                //Flower forest
                currentBiome = FLOWER_FOREST;
            } else if (weirdness >= 0 && weirdness < 1) {
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
            if (weirdness >= -1 && weirdness < 0) {
                //Birch forest
                currentBiome = BIRCH_FOREST;
            } else if (weirdness >= 0 && weirdness < 1) {
                //Old growth birch forest
                currentBiome = OLD_GROWTH_BIRCH_FOREST;
            }
        } else if (humidity >= 0.7 && humidity < 1) {
            //dark forest
            currentBiome = DARK_FOREST;
        }
    } else if (temperature >= 0.5 && temperature < 0.8) {
        //level 3
        if (humidity >= 1 && humidity < -0.3) {
            //Savanna
            currentBiome = SAVANNA;
        } else if (humidity >= -0.3 && humidity < 0.3) {
            if (weirdness >= -1 && weirdness < 0) {
                //Forest
                currentBiome = FOREST;
            } else if (weirdness >= 0 && weirdness < 1) {
                //Plains
                currentBiome = PLAINS;
            }
        } else if (humidity >= 0.3 && humidity < 0.7) {
            if (weirdness >= -1 && weirdness < 0) {
                //Jungle
                currentBiome = JUNGLE;
            } else if (weirdness >= 0 && weirdness < 1) {
                //Sparse jungle
                currentBiome = SPARSE_JUNGLE;
            }
        } else if (humidity >= 0.7 && humidity < 1) {
            if (weirdness >= -1 && weirdness < 0) {
                //Jungle
                currentBiome = JUNGLE;
            } else if (weirdness >= 0 && weirdness < 1) {
                //Bamboo jungle
                currentBiome = BAMBOO_JUNGLE;
            }
        }
    } else if (temperature >= 0.8 && temperature < 1) {
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
        if (continentalness >= -1 && continentalness < 0) {
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
        } else if (continentalness >= 0 && continentalness < 1) {
            //peak biome
            currentBiome = PEAKS;
        }
    } else if (erosion >= -0.375 && erosion < -0.2225) {
        //level 2
        if (continentalness >= -1 && continentalness < 0) {
            //middle biome
            middleBiome(temperature, humidity);
        } else if (continentalness >= 0 && continentalness < 1) {
            //plateau biome
            currentBiome = PLATEAU;
        }
    } else if (erosion >= -0.2225 && erosion < 0.05) {
        //level 3
        if (continentalness >= -1 && continentalness < 0) {
            //middle biome
            middleBiome(temperature, humidity);
        } else if (continentalness >= 0 && continentalness < 0.5) {
            if (temperature >= -1 && temperature < 0) {
                //middle biome
                middleBiome(temperature, humidity);
            } else if (temperature >= 0 && temperature < 1) {
                //badlands biome
                currentBiome = BADLANDS;
            }
        } else if (continentalness >= 0.5 && continentalness < 1) {
            //plateau biome
            currentBiome = PLATEAU;
        }
    } else if (erosion >= 0.05 && erosion < 0.45) {
        //level 4
        //middle biome
        middleBiome(temperature, humidity);
    } else if (erosion >= 0.45 && erosion < 0.55) {
        //level 5
        if (continentalness >= -1 && continentalness < 0) {
            if (temperature >= -1 && temperature < 0) {
                //shattered biome
                currentBiome = SHATTERED;
            } else if (temperature >= 0 && temperature < 1) {
                //windswept savanna
                currentBiome = SAVANNA;
            }
        } else if (continentalness >= 0 && continentalness < 1) {
            //shattered biome
            currentBiome = SHATTERED;
        }
    } else if (erosion >= 0.55 && erosion < 1) {
        //level 6
        //middle biome
        middleBiome(temperature, humidity);
    }
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


void generateChunkImprov(int chunkX, int chunkY, std::map<std::pair<int, int>, sf::VertexArray> *chunks) {
    
    Color SAND, DIRT, ROCK, GRASS, AIR, WATER, CAVE, CLAY, DARK_DIRT, LAVA;

    setColor(SAND, 255, 239, 0);
    setColor(DIRT, 139, 69, 19);
    setColor(ROCK, 100, 100, 100);
    setColor(GRASS, 0, 204, 0);
    setColor(AIR, 135, 206, 235);
    setColor(CAVE, 28, 28, 28);
    setColor(WATER, 0, 0, 255);
    setColor(LAVA, 255, 86, 0);
    setColor(CLAY, 163, 163, 163);
    setColor(DARK_DIRT, 82, 39, 0);

    sf::VertexArray chunk(sf::Quads);

    for (int blockX = 0; blockX < CHUNK_SIZE; blockX++) {

        float worldX = chunkX * CHUNK_SIZE + blockX;

        //std::cout << "worldX: " << worldX << std::endl;

        float continentalness = multiNoise(worldX * 0.9, 0, 0.2f, 1.0f);
        float erosion = multiNoise(worldX * 0.5, 0, 0.7f, 0.75f);
        float peaksValleys = multiNoise(worldX * 1.2, 0, 1.5f, 0.9f);
        float temperature = multiNoise(worldX * 0.2, 0, 0.5f, 0.75f);
        float humidity = multiNoise(worldX * 0.7, 0, 0.2f, 1.0f);

        //std::cout << "continentalness: " << continentalness << std::endl;

        biomeGen(continentalness, erosion, temperature, humidity);
        biomeEffects(currentBiome);
        std::cout << "Current biome: " << biomeToString(currentBiome) << std::endl;


        continentalness = std::clamp((continentalness + 1.0f) * 0.5f, 0.0f, 1.0f);
        erosion = std::clamp((erosion + 1.0f) * 0.5f, 0.0f, 1.0f);
        peaksValleys = std::clamp((peaksValleys + 1.0f) * 0.5f, 0.0f, 1.0f);
        temperature = std::clamp((temperature + 1.0f) * 0.5f, 0.0f, 1.0f);
        humidity = std::clamp((humidity + 1.0f) * 0.5f, 0.0f, 1.0f);


        float baseHeight = 500 + MAX_HEIGHT * (0.6f * continentalness);

        float erosionEffect = 0.5f + 0.5f * erosion;
        baseHeight *= erosionEffect;

        float peaksEffect = 1.0f + 0.5f * peaksValleys;

        float groundHeight = baseHeight * peaksEffect;

        groundHeight = std::clamp(groundHeight, 0.0f, static_cast<float>(MAX_HEIGHT));

        for (int blockY = 0; blockY < CHUNK_SIZE; blockY++) {
            float worldY = chunkY * CHUNK_SIZE + blockY;

            bool isGround = (worldY >= MAX_HEIGHT - groundHeight);
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
                    float upperCaves = multiNoise(worldX * 2.20f, worldY * 2.0f, 8.0f, 1.0f);
                    float surfaceCaves = multiNoise(worldX * 3, worldY * 2, 2.2f, 0.4f);

                    //float DirtInStone = multiNoise(worldX, worldY, 80.0f, 1.0f);
                    // Deeper layers (stone)
                    //makes sure that when density is done the rock can only be placed where density is greater then 0 to avoid going over whats done
                    if (worldY < MAX_HEIGHT - groundHeight + 100 && multiNoise(worldX, worldY * 0.85f, 1.0f, 1.0f) > 0) {
                        if (stoneInDirt < -0.38) {
                            
                            blockColor = sf::Color(ROCK.r, ROCK.g, ROCK.b);
                        } else {
                            blockColor = sf::Color(DIRT.r, DIRT.g, DIRT.b);
                        }

                        if (clay < -0.6) {
                            blockColor = sf::Color(CLAY.r, CLAY.g, CLAY.b);
                        }

                        if (upperCaves < -0.5) {
                            blockColor = sf::Color(DARK_DIRT.r, DARK_DIRT.g, DARK_DIRT.b);
                        }

                        if (surfaceCaves < -0.12) {
                            blockColor = sf::Color(DARK_DIRT.r, DARK_DIRT.g, DARK_DIRT.b);
                        }

                    //this is the normal case
                    } else if (worldY > MAX_HEIGHT - groundHeight + 100 && worldY < MAX_HEIGHT - groundHeight + 120) {
                        if (stoneInDirt < -0.3) {
                            blockColor = sf::Color(ROCK.r, ROCK.g, ROCK.b);
                        } else {
                            blockColor = sf::Color(DIRT.r, DIRT.g, DIRT.b);
                        }

                        if (clay < -0.6) {
                            blockColor = sf::Color(CLAY.r, CLAY.g, CLAY.b);
                        }

                        if (caves < -0.7) { // water cave
                            blockColor = sf::Color(WATER.r, WATER.g, WATER.b);
                        }

                        if (upperCaves < -0.5) {
                            blockColor = sf::Color(DARK_DIRT.r, DARK_DIRT.g, DARK_DIRT.b);
                        }

                        if (surfaceCaves < -0.12) {
                            blockColor = sf::Color(DARK_DIRT.r, DARK_DIRT.g, DARK_DIRT.b);
                        }

                    } else if (worldY > MAX_HEIGHT - groundHeight + 120 && worldY < MAX_HEIGHT - groundHeight + 155) {
                        if (stoneInDirt < 0.1) {
                            blockColor = sf::Color(ROCK.r, ROCK.g, ROCK.b);
                        } else {
                            blockColor = sf::Color(DIRT.r, DIRT.g, DIRT.b);
                        }

                        if (clay < -0.6) {
                            blockColor = sf::Color(CLAY.r, CLAY.g, CLAY.b);
                        }

                        if (caves < -0.5) { // water cave
                            blockColor = sf::Color(WATER.r, WATER.g, WATER.b);
                        }

                        if (upperCaves < -0.2) {
                            blockColor = sf::Color(DARK_DIRT.r, DARK_DIRT.g, DARK_DIRT.b);
                        }

                        if (surfaceCaves < -0.2) {
                            blockColor = sf::Color(DARK_DIRT.r, DARK_DIRT.g, DARK_DIRT.b);
                        }


                    } else if (worldY > MAX_HEIGHT - groundHeight + 155) {
                        if (dirtInStone < 0.4) {
                            blockColor = sf::Color(ROCK.r, ROCK.g, ROCK.b);
                        } else {
                            blockColor = sf::Color(DIRT.r, DIRT.g, DIRT.b);
                        }

                        if (caves < -0.5) { // water cave
                            blockColor = sf::Color(WATER.r, WATER.g, WATER.b);
                        }

                        if (middleCaves < -0.5) {
                            blockColor = sf::Color(CAVE.r, CAVE.g, CAVE.b);
                        }

                    }

                } 
            

                if (worldY >= MAX_HEIGHT - groundHeight + 200 && worldY < MAX_HEIGHT - groundHeight + 400) {
                    //Caves

                    if (waterCaves < -0.6) { // water cave
                        blockColor = sf::Color(WATER.r, WATER.g, WATER.b);
                    }
                    
                    if (caves < -0.3) { // was -0.05
                        //r = CAVE.r; g = CAVE.g; b = CAVE.b;
                        blockColor = sf::Color(CAVE.r, CAVE.g, CAVE.b);
                    }

                    if (middleCaves < -0.5) {
                        blockColor = sf::Color(CAVE.r, CAVE.g, CAVE.b);
                    }

                }

                if (worldY >= MAX_HEIGHT - groundHeight + 400) {

                    if (caves < -0.3) { // was -0.05
                        //r = CAVE.r; g = CAVE.g; b = CAVE.b;
                        blockColor = sf::Color(CAVE.r, CAVE.g, CAVE.b);
                    }

                    if (lavaCaves < -0.5) { // lava cave
                        blockColor = sf::Color(LAVA.r, LAVA.g, LAVA.b);
                    }
                }
            }
             if (blockColor != sf::Color::Transparent) {
                sf::Vertex topLeft(sf::Vector2f(worldX * BLOCK_SIZE, worldY * BLOCK_SIZE), blockColor);
                sf::Vertex topRight(sf::Vector2f((worldX + 1) * BLOCK_SIZE, worldY * BLOCK_SIZE), blockColor);
                sf::Vertex bottomRight(sf::Vector2f((worldX + 1) * BLOCK_SIZE, (worldY + 1) * BLOCK_SIZE), blockColor);
                sf::Vertex bottomLeft(sf::Vector2f(worldX * BLOCK_SIZE, (worldY + 1) * BLOCK_SIZE), blockColor);

                chunk.append(topLeft);
                chunk.append(topRight);
                chunk.append(bottomRight);
                chunk.append(bottomLeft);
            }
        }
    }

    (*chunks)[{chunkX, chunkY}] = chunk;
}




void generateChunk(int chunkX, int chunkY, std::map<std::pair<int, int>, std::vector<std::vector<sf::RectangleShape>>> *chunks) {
    
    Color SAND, DIRT, ROCK, GRASS, AIR, WATER, CAVE, CLAY, DARK_DIRT, LAVA;

    setColor(SAND, 255, 239, 0);
    setColor(DIRT, 139, 69, 19);
    setColor(ROCK, 100, 100, 100);
    setColor(GRASS, 0, 204, 0);
    setColor(AIR, 135, 206, 235);
    setColor(CAVE, 28, 28, 28);
    setColor(WATER, 0, 0, 255);
    setColor(LAVA, 255, 86, 0);
    setColor(CLAY, 163, 163, 163);
    setColor(DARK_DIRT, 82, 39, 0);


    std::vector<std::vector<sf::RectangleShape>> chunk;

    for (int blockX = 0; blockX < CHUNK_SIZE; blockX++) {

        float worldX = chunkX * CHUNK_SIZE + blockX;

        //std::cout << "worldX: " << worldX << std::endl;

        float continentalness = multiNoise(worldX * 0.9, 0, 0.2f, 1.0f);
        float erosion = multiNoise(worldX * 0.5, 0, 0.7f, 0.75f);
        float peaksValleys = multiNoise(worldX * 1.2, 0, 1.5f, 0.9f);
        float temperature = multiNoise(worldX * 0.2, 0, 0.5f, 0.75f);
        float humidity = multiNoise(worldX * 0.7, 0, 0.2f, 1.0f);

        //std::cout << "continentalness: " << continentalness << std::endl;

        biomeGen(continentalness, erosion, temperature, humidity);
        biomeEffects(currentBiome);
        std::cout << "Current biome: " << biomeToString(currentBiome) << std::endl;


        continentalness = std::clamp((continentalness + 1.0f) * 0.5f, 0.0f, 1.0f);
        erosion = std::clamp((erosion + 1.0f) * 0.5f, 0.0f, 1.0f);
        peaksValleys = std::clamp((peaksValleys + 1.0f) * 0.5f, 0.0f, 1.0f);
        temperature = std::clamp((temperature + 1.0f) * 0.5f, 0.0f, 1.0f);
        humidity = std::clamp((humidity + 1.0f) * 0.5f, 0.0f, 1.0f);


        float baseHeight = 500 + MAX_HEIGHT * (0.6f * continentalness);

        float erosionEffect = 0.5f + 0.5f * erosion;
        baseHeight *= erosionEffect;

        float peaksEffect = 1.0f + 0.5f * peaksValleys;

        float groundHeight = baseHeight * peaksEffect;

        groundHeight = std::clamp(groundHeight, 0.0f, static_cast<float>(MAX_HEIGHT));

        //std::cout << "Height: " << groundHeight << std::endl;

        std::vector<sf::RectangleShape> column;

        for (int blockY = 0; blockY < CHUNK_SIZE; blockY++) {
            float worldY = chunkY * CHUNK_SIZE + blockY;

            //std::cout << "worldX: " << worldX << ", worldY: " << worldY << std::endl;

            //if (worldX < 0) {
            //    std::cout << "Negative worldX: " << worldX << std::endl;
            //}
            //if (worldY < 0) {
            //    std::cout << "Negative worldY: " << worldY << std::endl;
            //}

            bool isGround = (worldY >= MAX_HEIGHT - groundHeight);

            if (isGround) {

                sf::RectangleShape block(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
                block.setPosition(worldX * BLOCK_SIZE, worldY * BLOCK_SIZE);
                //float caves = multiNoise(worldX * 4.0f, worldY * 4.5f, 1.0f, 1.0f);
                float caves = multiNoise(worldX * 0.4f, worldY, 20.0f, 1.0f);
                float waterCaves = multiNoise(worldX * 0.8f, worldY * 2.0f, 25.7f, 1.2f);
                float lavaCaves = multiNoise(worldX * 0.2f, worldY * 0.7f, 17.0f, 1.3f);
                float middleCaves = multiNoise(worldX * 0.4f, worldY, 30.0f, 2.0f);

                if (worldY >= MAX_HEIGHT - groundHeight) {
                    float stoneInDirt = multiNoise(worldX, worldY, 80.0f, 1.0f);
                    float dirtInStone = multiNoise(worldX * 0.9f, worldY , 90.0f, 1.0f);
                    float clay = multiNoise(worldX * 0.5f, worldY * 2.0f, 50.0f, 1.0f);
                    float upperCaves = multiNoise(worldX * 2.20f, worldY * 2.0f, 8.0f, 1.0f);
                    float surfaceCaves = multiNoise(worldX * 3, worldY * 2, 2.2f, 0.4f);

                    //float DirtInStone = multiNoise(worldX, worldY, 80.0f, 1.0f);
                    // Deeper layers (stone)
                    //makes sure that when density is done the rock can only be placed where density is greater then 0 to avoid going over whats done
                    if (worldY < MAX_HEIGHT - groundHeight + 100 && multiNoise(worldX, worldY * 0.85f, 1.0f, 1.0f) > 0) {
                        if (stoneInDirt < -0.38) {
                            block.setFillColor(sf::Color(ROCK.r, ROCK.g, ROCK.b));
                        } else {
                            block.setFillColor(sf::Color(DIRT.r, DIRT.g, DIRT.b));
                        }

                        if (clay < -0.6) {
                            block.setFillColor(sf::Color(CLAY.r, CLAY.g, CLAY.b));
                        }

                        if (upperCaves < -0.5) {
                            block.setFillColor(sf::Color(DARK_DIRT.r, DARK_DIRT.g, DARK_DIRT.b));
                        }

                        if (surfaceCaves < -0.12) {
                            block.setFillColor(sf::Color(DARK_DIRT.r, DARK_DIRT.g, DARK_DIRT.b));
                        }

                        
                        column.push_back(block);

                    //this is the normal case
                    } else if (worldY > MAX_HEIGHT - groundHeight + 100 && worldY < MAX_HEIGHT - groundHeight + 120) {
                        if (stoneInDirt < -0.3) {
                            block.setFillColor(sf::Color(ROCK.r, ROCK.g, ROCK.b));
                        } else {
                            block.setFillColor(sf::Color(DIRT.r, DIRT.g, DIRT.b));
                        }

                        if (clay < -0.6) {
                            block.setFillColor(sf::Color(CLAY.r, CLAY.g, CLAY.b));
                        }

                        if (caves < -0.7) { // water cave
                            block.setFillColor(sf::Color(WATER.r, WATER.g, WATER.b));
                        }

                        if (upperCaves < -0.5) {
                            block.setFillColor(sf::Color(DARK_DIRT.r, DARK_DIRT.g, DARK_DIRT.b));
                        }

                        if (surfaceCaves < -0.12) {
                            block.setFillColor(sf::Color(DARK_DIRT.r, DARK_DIRT.g, DARK_DIRT.b));
                        }



                        column.push_back(block);

                    } else if (worldY > MAX_HEIGHT - groundHeight + 120 && worldY < MAX_HEIGHT - groundHeight + 155) {
                        if (stoneInDirt < 0.1) {
                            block.setFillColor(sf::Color(ROCK.r, ROCK.g, ROCK.b));
                        } else {
                            block.setFillColor(sf::Color(DIRT.r, DIRT.g, DIRT.b));
                        }

                        if (clay < -0.6) {
                            block.setFillColor(sf::Color(CLAY.r, CLAY.g, CLAY.b));
                        }

                        if (caves < -0.5) { // water cave
                            block.setFillColor(sf::Color(WATER.r, WATER.g, WATER.b));
                        }

                        if (upperCaves < -0.2) {
                            block.setFillColor(sf::Color(DARK_DIRT.r, DARK_DIRT.g, DARK_DIRT.b));
                        }

                        if (surfaceCaves < -0.2) {
                            block.setFillColor(sf::Color(DARK_DIRT.r, DARK_DIRT.g, DARK_DIRT.b));
                        }

                        column.push_back(block);

                    } else if (worldY > MAX_HEIGHT - groundHeight + 155) {
                        if (dirtInStone < 0.4) {
                            block.setFillColor(sf::Color(ROCK.r, ROCK.g, ROCK.b));
                        } else {
                            block.setFillColor(sf::Color(DIRT.r, DIRT.g, DIRT.b));
                        }

                        if (caves < -0.5) { // water cave
                            block.setFillColor(sf::Color(WATER.r, WATER.g, WATER.b));
                        }

                        if (middleCaves < -0.5) {
                            block.setFillColor(sf::Color(CAVE.r, CAVE.g, CAVE.b));
                        }

                        column.push_back(block);
                    }

                } 

                //if (worldY <= MAX_HEIGHT - groundHeight + 10) {
                //    block.setFillColor(sf::Color(DIRT.r, DIRT.g, DIRT.b));
                //    column.push_back(block);
                //}
            

                if (worldY >= MAX_HEIGHT - groundHeight + 200 && worldY < MAX_HEIGHT - groundHeight + 400) {
                    //Caves

                    if (waterCaves < -0.6) { // water cave
                        block.setFillColor(sf::Color(WATER.r, WATER.g, WATER.b));
                    }
                    
                    if (caves < -0.3) { // was -0.05
                        //r = CAVE.r; g = CAVE.g; b = CAVE.b;
                        block.setFillColor(sf::Color(CAVE.r, CAVE.g, CAVE.b));
                    }

                    if (middleCaves < -0.5) {
                            block.setFillColor(sf::Color(CAVE.r, CAVE.g, CAVE.b));
                    }

                    column.push_back(block);
                }

                if (worldY >= MAX_HEIGHT - groundHeight + 400) {

                    if (caves < -0.3) { // was -0.05
                        //r = CAVE.r; g = CAVE.g; b = CAVE.b;
                        block.setFillColor(sf::Color(CAVE.r, CAVE.g, CAVE.b));
                    }

                    if (lavaCaves < -0.5) { // lava cave
                        block.setFillColor(sf::Color(LAVA.r, LAVA.g, LAVA.b));
                    }
                    column.push_back(block);
                }
                //std::cout << "Generated block at: " << block.getPosition().x << ", " << block.getPosition().y << std::endl;
            } 
        }
        chunk.push_back(column);
    }
    (*chunks)[{chunkX, chunkY}] = chunk;
    //return chunks;
}


void generateMap(std::vector<std::vector<sf::RectangleShape>> *worldGrid) { //was sf::Uint8 generateMap(sf::Uint8 *pixels)
    Color SAND, DIRT, ROCK, GRASS, AIR, WATER, CAVE;

    setColor(SAND, 255, 239, 0);
    setColor(DIRT, 139, 69, 19);
    setColor(ROCK, 100, 100, 100);
    setColor(GRASS, 0, 204, 0);
    setColor(AIR, 135, 206, 235);
    setColor(CAVE, 28, 28, 28);
    setColor(WATER, 0, 0, 255);


    for (unsigned blockX = 0; blockX < WORLD_WIDTH / BLOCK_SIZE; blockX++) {

        float continentalness = multiNoise(blockX * 0.9, 0, 0.2f, 1.0f);
        float erosion = multiNoise(blockX * 0.5, 0, 0.7f, 0.75f);
        float peaksValleys = multiNoise(blockX * 1.2, 0, 1.5f, 0.9f);
        float temperature = multiNoise(blockX * 0.2, 0, 0.5f, 0.75f);
        float humidity = multiNoise(blockX * 0.7, 0, 0.2f, 1.0f);


        continentalness = std::clamp((continentalness + 1.0f) * 0.5f, 0.0f, 1.0f);
        erosion = std::clamp((erosion + 1.0f) * 0.5f, 0.0f, 1.0f);
        peaksValleys = std::clamp((peaksValleys + 1.0f) * 0.5f, 0.0f, 1.0f);
        temperature = std::clamp((temperature + 1.0f) * 0.5f, 0.0f, 1.0f);
        humidity = std::clamp((humidity + 1.0f) * 0.5f, 0.0f, 1.0f);

        float baseHeight = 500 + MAX_HEIGHT * (0.6f * continentalness);

        float erosionEffect = 0.5f + 0.5f * erosion;
        baseHeight *= erosionEffect;

        float peaksEffect = 1.0f + 0.5f * peaksValleys;

        float groundHeight = baseHeight * peaksEffect;

        groundHeight = std::clamp(groundHeight, 0.0f, static_cast<float>(MAX_HEIGHT));

        std::vector<sf::RectangleShape> column;

        for (unsigned blockY = 0; blockY < MAX_HEIGHT; blockY++) {
            bool isGround = (blockY >= MAX_HEIGHT - groundHeight);

            sf::Uint8 r, g, b;
            if (isGround) {

                sf::RectangleShape block(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
                block.setPosition(blockX * BLOCK_SIZE, blockY * BLOCK_SIZE);
                if (blockY >= MAX_HEIGHT - groundHeight) {
                    // Deeper layers (stone)
                    //r = ROCK.r; g = ROCK.g; b = ROCK.b;
                    if (blockY < MAX_HEIGHT - groundHeight + 150 && multiNoise(blockX, blockY * 0.85f, 1.0f, 1.0f) > 0) {
                        block.setFillColor(sf::Color(ROCK.r, ROCK.g, ROCK.b));
                        column.push_back(block);
                    } else if (blockY > MAX_HEIGHT - groundHeight + 150) {
                        block.setFillColor(sf::Color(ROCK.r, ROCK.g, ROCK.b));
                        column.push_back(block);
                    }
                    
                } 
                //if (blockY >= MAX_HEIGHT - groundHeight && blockY < MAX_HEIGHT - groundHeight + 150) {
                //    //Density
                //    if (multiNoise(blockX, blockY * 0.85f, 1.0f, 1.0f) < 0 && block.getFillColor() == sf::Color(ROCK.r, ROCK.g, ROCK.b)) {
                //        //r = AIR.r; g = AIR.g; b = AIR.b;
                //        
                //        block.setFillColor(sf::Color(AIR.r, AIR.g, AIR.b));
                //    }
                //}
                if (blockY >= MAX_HEIGHT - groundHeight + 200) {
                    //Caves
                    if (multiNoise(blockX * 4.0f, blockY * 4.5f, 1.0f, 1.0f) < -0.05) {
                        //r = CAVE.r; g = CAVE.g; b = CAVE.b;
                        block.setFillColor(sf::Color(CAVE.r, CAVE.g, CAVE.b));
                        column.push_back(block);
                    }
                }
            } else {
                // Above ground (air)
                //r = AIR.r; g = AIR.g; b = AIR.b; // Sky blue
                //block.setFillColor(sf::Color(AIR.r, AIR.g, AIR.b));
                //column.push_back(sf::RectangleShape());
            }


            //std::cout << value << " ";



            //for (int px = 0; px < BLOCK_SIZE; px++) {
            //    for (int py = 0; py < BLOCK_SIZE; py++) {
            //        int x = blockX * BLOCK_SIZE + px;
            //        int y = blockY * BLOCK_SIZE + py;
            //        int indx = (y * (WORLD_WIDTH / BLOCK_SIZE) * BLOCK_SIZE + x) * 4;
//
            //        pixels[indx] = r;
            //        pixels[indx + 1] = g;
            //        pixels[indx + 2] = b;
            //        pixels[indx + 3] = 255; // Fully opaque
            //    }
            //}

        }
        worldGrid->push_back(column);

    }
    
}

