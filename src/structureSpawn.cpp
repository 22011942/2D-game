#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "mapGen.h"

const sf::Color TRUNK_BLOCK = sf::Color(71, 48, 2);
const sf::Color LEAVES_BLOCK = sf::Color(44, 105, 12, 0.678);

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
    {{-1, 3}, {0, 3}, {1, 3}, {-1, 4}, {0, 4}, {1, 4}} // Leaves
};

void spawnTreeAt(int baseX, int baseY, sf::VertexArray *chunk) {
    for (auto [dx, dy] : oakTree.trunk) {
        //setBlock(baseX + dx, baseY + dy, TRUNK_BLOCK);

        //for (size_t indx = 0; indx < air->getVertexCount(); indx++) {
        //    if ((*air)[indx].position.x == baseX + dx && (*air)[indx].position.y == baseY + dy) {
        //        std::cout << "indx: " << indx << std::endl;
        //        (*air)[indx].color = sf::Color::Red;
        //    }
        //}

        

        sf::Vertex topLeft(sf::Vector2f((baseX + dx) * BLOCK_SIZE, (baseY + dy) * BLOCK_SIZE), sf::Color::Red);
        sf::Vertex topRight(sf::Vector2f((baseX + 1 + dx) * BLOCK_SIZE, (baseY + dy) * BLOCK_SIZE), sf::Color::Red);
        sf::Vertex bottomRight(sf::Vector2f((baseX + 1 + dx) * BLOCK_SIZE, (baseY + 1 + dy) * BLOCK_SIZE), sf::Color::Red);
        sf::Vertex bottomLeft(sf::Vector2f((baseX + dx) * BLOCK_SIZE, (baseY + 1 + dy) * BLOCK_SIZE), sf::Color::Red);

        chunk->append(topLeft);
        chunk->append(topRight);
        chunk->append(bottomRight);
        chunk->append(bottomLeft);

    }
    for (auto [dx, dy] : oakTree.leaves) {

        //for (size_t indx = 0; indx < air->getVertexCount(); indx++) {
        //    if ((*air)[indx].position.x == baseX + dx && (*air)[indx].position.y == baseY + dy) {
        //        (*air)[indx].color = sf::Color::Red;
        //    }
        //}

        sf::Vertex topLeft(sf::Vector2f((baseX + dx) * BLOCK_SIZE, (baseY + dy) * BLOCK_SIZE), sf::Color::Red);
        sf::Vertex topRight(sf::Vector2f((baseX + 1 + dx) * BLOCK_SIZE, (baseY + dy) * BLOCK_SIZE), sf::Color::Red);
        sf::Vertex bottomRight(sf::Vector2f((baseX + 1 + dx) * BLOCK_SIZE, (baseY + 1 + dy) * BLOCK_SIZE), sf::Color::Red);
        sf::Vertex bottomLeft(sf::Vector2f((baseX + dx) * BLOCK_SIZE, (baseY + 1 + dy) * BLOCK_SIZE), sf::Color::Red);

        chunk->append(topLeft);
        chunk->append(topRight);
        chunk->append(bottomRight);
        chunk->append(bottomLeft);
    }
}

