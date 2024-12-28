#pragma once
#include "SFML/Graphics.hpp"
#include <vector>

const int BLOCK_SIZE = 8;
const int WORLD_HEIGHT = 10000;
const int MAX_HEIGHT = WORLD_HEIGHT / BLOCK_SIZE;
const int WORLD_WIDTH = 30000;

const sf::Color SAND = sf::Color(255, 239, 0);
const sf::Color DIRT = sf::Color(139, 69, 19);
const sf::Color ROCK = sf::Color(100, 100, 100);
const sf::Color GRASS = sf::Color(0, 204, 0);
const sf::Color CAVE = sf::Color(28, 28, 28);
const sf::Color WATER = sf::Color(0, 0, 255);
const sf::Color LAVA = sf::Color(255, 86, 0);
const sf::Color CLAY = sf::Color(163, 163, 163);
const sf::Color DARK_DIRT = sf::Color(82, 39, 0);

const sf::Color COAL = sf::Color(0, 0, 0);
const sf::Color GOLD = sf::Color(214, 169, 0);
const sf::Color COPPER = sf::Color(240, 113, 0);
const sf::Color IRON = sf::Color(194, 165, 140);
const sf::Color TIN = sf::Color(124, 143, 135);
const sf::Color ZINC = sf::Color(158, 158, 158);

void generateChunkImprov(int chunkX, int chunkY, std::map<std::pair<int, int>, sf::VertexArray> *chunks);

float multiNoise(float blockX, float blockY, float frequency, float amplitude);