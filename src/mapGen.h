#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include <unordered_map>
#include <iostream>


const int BLOCK_SIZE = 8;
const int WORLD_HEIGHT = 10000;
const int MAX_HEIGHT = WORLD_HEIGHT / BLOCK_SIZE;
const int WORLD_WIDTH = 30000;

const double NO_TREES = -1.0;
const double VERY_SPARSE_TREES = -0.55;
const double SPARSE_TREES = -0.5;
const double MEDIUM_TREES = -0.2;
const double DENSE_TREES = 0.0;

const sf::Color SAND = sf::Color(255, 239, 0);
const sf::Color DIRT = sf::Color(139, 69, 19);
const sf::Color ROCK = sf::Color(100, 100, 100);
const sf::Color GRASS = sf::Color(0, 204, 0);
const sf::Color CAVE = sf::Color(28, 28, 28);
const sf::Color WATER = sf::Color(0, 0, 255);
const sf::Color LAVA = sf::Color(255, 86, 0);
const sf::Color CLAY = sf::Color(163, 163, 163);
const sf::Color DARK_DIRT = sf::Color(82, 39, 0);

const sf::Color TRUNK_BLOCK = sf::Color(71, 48, 2);
const sf::Color LEAVES_BLOCK = sf::Color(44, 105, 12);

const sf::Color COAL = sf::Color(0, 0, 0);
const sf::Color GOLD = sf::Color(214, 169, 0);
const sf::Color COPPER = sf::Color(240, 113, 0);
const sf::Color IRON = sf::Color(194, 165, 140);
const sf::Color TIN = sf::Color(124, 143, 135);
const sf::Color ZINC = sf::Color(158, 158, 158);

struct PairHash {
    std::size_t operator()(const std::pair<int, int>& p) const {
        return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
    }
};

struct Chunk {
    std::vector<sf::Vertex> vertices;
    sf::VertexArray vertexArray;
    bool needsUpdate = true;

    void addQuad(int xPos, int yPos, sf::Color color) {
        sf::Vertex topLeft(sf::Vector2f(xPos * BLOCK_SIZE, yPos * BLOCK_SIZE), color);
        sf::Vertex topRight(sf::Vector2f((xPos + 1) * BLOCK_SIZE, yPos * BLOCK_SIZE), color);
        sf::Vertex bottomRight(sf::Vector2f((xPos + 1) * BLOCK_SIZE, (yPos + 1) * BLOCK_SIZE), color);
        sf::Vertex bottomLeft(sf::Vector2f(xPos * BLOCK_SIZE, (yPos + 1) * BLOCK_SIZE), color);

        vertices.push_back(topLeft);
        vertices.push_back(topRight);
        vertices.push_back(bottomRight);
        vertices.push_back(bottomLeft);

        needsUpdate = true;
    }

    void removeQuad(size_t quadIndex) {
        size_t start = quadIndex * 4;
        if (start + 4 <= vertices.size()) {
            vertices.erase(vertices.begin() + start, vertices.begin() + start + 4);
            needsUpdate = true;
        }
    }

    void updateVertexArray() {
        if (needsUpdate) {
            vertexArray.clear();
            vertexArray.setPrimitiveType(sf::Quads);
            vertexArray.resize(vertices.size());
            for (size_t i = 0; i < vertices.size(); ++i) {
                vertexArray[i] = vertices[i];
            }
            needsUpdate = false;
        }
    }
};


struct ChunkData {
    Chunk chunkInfo, airInChunk;

    std::map<std::pair<int, int>, sf::RectangleShape> collisionBlocks; // Exposed blocks

    
    bool airCheck(int xPos, int yPos, Chunk *airInfo) {
        for (size_t indx = 0; indx < (*airInfo).vertices.size(); indx+=4) {
            if ((*airInfo).vertices[indx].position.y == yPos && (*airInfo).vertices[indx].position.x == xPos) {
                return true;
            }
        }
        return false;
    }

    void adjustCollisions(int xPos, int yPos) {
        //std::cout << "block pos x: " << xPos <<  " block pos y: " << yPos << std::endl;
        if (collisionBlocks.count({xPos, yPos})) {
            std::cout << "erased" << std::endl;
        }

        collisionBlocks.erase({xPos, yPos});
        sf::RectangleShape block;
        sf::Vector2f size(8.0f, 8.0f);
        block.setSize(size);


        auto addBlockIfNeeded = [&](int newX, int newY) {
            if (!collisionBlocks.count({newX, newY}) && airCheck(newX, newY, &airInChunk)) {
                sf::Vector2f position(newX, newY);
                block.setPosition(position);
                collisionBlocks[{newX, newY}] = block;
            }
        };

        // Check in all four directions
        addBlockIfNeeded(xPos, yPos + BLOCK_SIZE); // Above
        addBlockIfNeeded(xPos, yPos - BLOCK_SIZE); // Below
        addBlockIfNeeded(xPos + BLOCK_SIZE, yPos); // Right
        addBlockIfNeeded(xPos - BLOCK_SIZE, yPos); // Left
    }
};


void generateChunkImprov(int chunkX, int chunkY, std::unordered_map<std::pair<int, int>, ChunkData, PairHash> *chunks);


float multiNoise(float blockX, float blockY, float frequency, float amplitude);