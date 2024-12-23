#pragma once
#include "SFML/Graphics.hpp"
#include <vector>

const int BLOCK_SIZE = 8;
const int WORLD_HEIGHT = 10000;
const int MAX_HEIGHT = WORLD_HEIGHT / BLOCK_SIZE;
const int WORLD_WIDTH = 30000;

void generateChunkImprov(int chunkX, int chunkY, std::map<std::pair<int, int>, sf::VertexArray> *chunks);