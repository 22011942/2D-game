#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "animation.h"
#include "player.h"
#include "platform.h"
#include "mapGen.h"
#include <random>
#include <ctime>
using namespace std;


static const unsigned int VIEW_HEIGHT = 5000;
//map<pair<int, int>, vector<vector<sf::RectangleShape>>> chunks;
map<pair<int, int>, sf::VertexArray> chunks;


void resizeView(const sf::RenderWindow& window, sf::View& view) {
    float aspectRatio = (float)window.getSize().x / (float)window.getSize().y;

    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

void renderVisibleBlocks(sf::RenderWindow& window, sf::View& view, vector<vector<sf::RectangleShape>> worldGrid) {
    sf::FloatRect viewBounds(
        view.getCenter().x - view.getSize().x / 2,
        view.getCenter().y - view.getSize().y / 2,
        view.getSize().x,
        view.getSize().y
    );

    for (const auto& column : worldGrid) {
        for (const auto& block : column) {
            if (viewBounds.intersects(block.getGlobalBounds())) {
                window.draw(block);
            }
        }
    }
}

void updateChunks(const sf::View& view, sf::RenderWindow& window) {
    //vector<vector<sf::RectangleShape>> chunk;

    int startX = view.getCenter().x / (16 * BLOCK_SIZE);
    int startY = view.getCenter().y / (16 * BLOCK_SIZE);

    int viewRadius = 20; // Number of chunks to load around the player

    for (int dx = -viewRadius; dx <= viewRadius; ++dx) {
        for (int dy = -viewRadius; dy <= viewRadius; ++dy) {
            int chunkX = startX + dx;
            int chunkY = startY + dy;

            if (chunks.find({chunkX, chunkY}) == chunks.end()) {
                //generateChunk(chunkX, chunkY, &chunks);
                generateChunkImprov(chunkX, chunkY, &chunks);
            }

            if (chunks.find({chunkX, chunkY}) != chunks.end()) {
                window.draw(chunks.at({chunkX, chunkY}));
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
    Player player(&playerTexture, sf::Vector2u(2, 3), 0.3f, 1000.0f, 200.0f);

    skyTexture.loadFromFile("assets\\skyboxtemp.jpg");
    sf::RectangleShape sky(sf::Vector2f(30000, 10000));
    sky.setTexture(&skyTexture);
    sky.setPosition(0, 0);

    std::vector<sf::RectangleShape> worldSprites;
    std::vector<Collision> collisions;


    //generateMap(&worldGrid);

    //sf::Texture texture1; 

    //texture1.create(WORLD_WIDTH, WORLD_HEIGHT);
    //texture1.update(pixels);

    //
    //sf::Sprite sprite1(texture1);


    //std::vector<Platform> platforms;

    //platforms.push_back(Platform(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 200.0f)));
    //platforms.push_back(Platform(&texture1, sf::Vector2f(1000.0f, 1000.0f), sf::Vector2f(1500.0f, 0.0f)));
    //platforms.push_back(Platform(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 0.0f)));
    //platforms.push_back(Platform(nullptr, sf::Vector2f(1000.0f, 200.0f), sf::Vector2f(500.0f, 500.0f)));

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

            if (event.type == sf::Event::Resized) {
                resizeView(window, view);
            }
        }


        player.updatePlayer(deltaTime);

        //sf::Vector2f direction;
//
//
        //for (Collision& col : collisions) {
        //    if (col.checkCollision(player.getPlayerCollider(), 1.0f, direction)) {
        //        player.onCollision(direction);
        //    }
        //}

        //for (Platform& platform : platforms) {
        //    if (platform.getColliderPlat().checkCollision(player.getPlayerCollider(), 1.0f, direction)) {
        //        player.onCollision(direction);
        //    }
        //}

        //platform1.getColliderPlat().checkCollision(player.getPlayerCollider(), 0.0f);
        //platform2.getColliderPlat().checkCollision(player.getPlayerCollider(), 1.0f);


        view.setCenter(player.getPlayerPosition());

        window.clear(sf::Color(207, 207, 207, 255));
        window.setView(view);
        //window.draw(sprite1);
        window.draw(sky);

        //renderVisibleBlocks(window, view, worldGrid);

        updateChunks(view, window);


        player.Draw(window);
        //platform1.drawPlatform(window);
        //platform2.drawPlatform(window);

        //for (Platform& platform : platforms) {
        //    platform.drawPlatform(window);
        //}

        //for (sf::RectangleShape& shape : worldSprites) {
        //    window.draw(shape);
        //}

        window.display();
    }

    //delete[] pixels;
    return 0;
}
