#pragma once
#include "collider.h"
#include <SFML/Graphics.hpp>

struct Player {
    sf::RectangleShape body;

    Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight);

    void updatePlayer(float deltaTime);

    void Draw(sf::RenderWindow& window);

    void onCollision(sf::Vector2f direction);

    sf::Vector2f getPlayerPosition();

    Collision playerCollider;

    Collision& getPlayerCollider();

    unsigned int row;
    float speed;
    bool faceRight;

    sf::Vector2f velocity;
    bool canJump;
    float jumpHieght;
};
