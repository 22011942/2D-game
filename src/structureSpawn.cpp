#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "mapGen.h"

struct Tree {
    std::vector<std::pair<int, int>> trunk;  
    std::vector<std::pair<int, int>> leaves;
};

struct IceSpike {
    std::vector<std::pair<int, int>> core;  //blue ice
    std::vector<std::pair<int, int>> outerShell;  //normal ice
};

Tree oakTree = {
    {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}, {0, 8}, {0, 9}},               // Trunk: 4 blocks tall
    {{-2, 9}, {-1, 9}, {0, 9}, {1, 9}, {2, 9}, {-1, 10}, {0, 10}, {1, 10}, {0, 11}} // Leaves
};


void spawnTreeAt(int baseX, int baseY, ChunkData *chunk) {
    for (auto [dx, dy] : oakTree.trunk) {

        sf::Vertex topLeft(sf::Vector2f(baseX - dx * BLOCK_SIZE, baseY - dy * BLOCK_SIZE), TRUNK_BLOCK);
        sf::Vertex topRight(sf::Vector2f(baseX - dx * BLOCK_SIZE + BLOCK_SIZE, baseY - dy * BLOCK_SIZE), TRUNK_BLOCK);
        sf::Vertex bottomRight(sf::Vector2f(baseX - dx * BLOCK_SIZE + BLOCK_SIZE, baseY - dy * BLOCK_SIZE + BLOCK_SIZE), TRUNK_BLOCK);
        sf::Vertex bottomLeft(sf::Vector2f(baseX - dx * BLOCK_SIZE, baseY - dy * BLOCK_SIZE + BLOCK_SIZE), TRUNK_BLOCK);


        chunk->chunkInfo.vertices.push_back(topLeft);
        chunk->chunkInfo.vertices.push_back(topRight);
        chunk->chunkInfo.vertices.push_back(bottomRight);
        chunk->chunkInfo.vertices.push_back(bottomLeft);


    }
    for (auto [dx, dy] : oakTree.leaves) {

        sf::Vertex topLeft(sf::Vector2f(baseX - dx * BLOCK_SIZE, baseY - dy * BLOCK_SIZE), LEAVES_BLOCK);
        sf::Vertex topRight(sf::Vector2f(baseX - dx * BLOCK_SIZE + BLOCK_SIZE, baseY - dy * BLOCK_SIZE), LEAVES_BLOCK);
        sf::Vertex bottomRight(sf::Vector2f(baseX - dx * BLOCK_SIZE + BLOCK_SIZE, baseY - dy * BLOCK_SIZE + BLOCK_SIZE), LEAVES_BLOCK);
        sf::Vertex bottomLeft(sf::Vector2f(baseX - dx * BLOCK_SIZE, baseY - dy * BLOCK_SIZE + BLOCK_SIZE), LEAVES_BLOCK);


        chunk->chunkInfo.vertices.push_back(topLeft);
        chunk->chunkInfo.vertices.push_back(topRight);
        chunk->chunkInfo.vertices.push_back(bottomRight);
        chunk->chunkInfo.vertices.push_back(bottomLeft);
    }

    chunk->chunkInfo.needsUpdate = true;
}