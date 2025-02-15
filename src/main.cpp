#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "animation.h"
#include "player.h"
#include "platform.h"
#include "mapGen.h"
#include <random>
#include <ctime>
#include <unordered_map>
using namespace std;


static const unsigned int VIEW_HEIGHT = 3000;
const bool NOCLIP = true;
bool breakingBlock = false;
//sf::Vector2f breakingPosition;

unordered_map<pair<int, int>, ChunkData, PairHash> chunks;


void resizeView(const sf::RenderWindow& window, sf::View& view) {
    float aspectRatio = (float)window.getSize().x / (float)window.getSize().y;

    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}


void updateChunks(const sf::View& view, sf::RenderWindow& window, Player *player) {
    //vector<vector<sf::RectangleShape>> chunk;



    int startX = view.getCenter().x / (16 * BLOCK_SIZE);
    int startY = view.getCenter().y / (16 * BLOCK_SIZE);

    int viewRadius = 15; // Number of chunks to load around the player

    for (int dx = -viewRadius; dx <= viewRadius; ++dx) {
        for (int dy = -viewRadius; dy <= viewRadius; ++dy) {
            int chunkX = startX + dx;
            int chunkY = startY + dy;

            if (chunks.find({chunkX, chunkY}) == chunks.end()) {
                generateChunkImprov(chunkX, chunkY, &chunks);
            }


            sf::Vector2f direction;

            if (chunks.find({chunkX, chunkY}) != chunks.end()) { // Finds the chunk that the player is in
                ChunkData& chunk = chunks.at({chunkX, chunkY});

                (*player).mouseInteration(window, &chunk);

                if (!NOCLIP) {
                    for (auto [postion, block] : chunk.collisionBlocks) { // Gets every block exposed to air in the chunk and checks its position against to player for collision
                        if (Collision(block).checkCollision(player->getPlayerCollider(), 1.0f, direction)) {
                            player->onCollision(direction);
                        }
                    }
                }

                //if (breakingBlock && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                //    //continueBreakingBlock(breakingPosition);
                //}

                chunk.chunkInfo.updateVertexArray();

                window.draw(chunk.chunkInfo.vertexArray);
            }

        }
    }

}


int main() {
    auto window = sf::RenderWindow({1920u, 1080u}, "CMake SFML Project", sf::Style::Close | sf::Style::Resize);

    auto view = sf::View(sf::Vector2f(0.0f,0.0f), {VIEW_HEIGHT, VIEW_HEIGHT});

    float aspectRatio = (float)window.getSize().x / (float)window.getSize().y;
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);

    sf::Texture playerTexture, skyTexture;
    playerTexture.loadFromFile("assets\\New Piskel.png");
    Player player(&playerTexture, sf::Vector2u(2, 3), 0.3f, 2500.0f, 200.0f);

    skyTexture.loadFromFile("assets\\skyboxtemp.jpg");
    sf::RectangleShape sky(sf::Vector2f(30000, 10000));
    sky.setTexture(&skyTexture);
    sky.setPosition(0, 0);

    std::vector<sf::RectangleShape> worldSprites;
    std::vector<Collision> collisions;

    float deltaTime {0.0f};
    sf::Clock clock;

    window.setFramerateLimit(144);

    while (window.isOpen()) {
        deltaTime = clock.restart().asSeconds();
        if (deltaTime > 1.0f / 20.0f) {
            deltaTime = 1.0f / 20.0f;
        }

        for (auto event = sf::Event(); window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::Resized) {
                cout << "Resized " << event.size.width << " " << event.size.height << endl;
            }

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128)
                    printf("%c", event.text.unicode);
            }

            //if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            //    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            //    sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
            //    breakingBlock = true;
            //}

            //if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            //    // Stop breaking the block
            //    breakingBlock = false;
            //}

        }


        player.updatePlayer(deltaTime);

        view.setCenter(player.getPlayerPosition());

        window.clear(sf::Color(207, 207, 207, 255));
        window.setView(view);
        window.draw(sky);

        updateChunks(view, window, &player);


        player.Draw(window);

        window.display();
    }

    //delete[] pixels;
    std::getchar();
    return 0;
}
