#pragma once
#include "collider.h"
#include <SFML/Graphics.hpp>

struct Platform {

    Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);

    void drawPlatform(sf::RenderWindow& window);

    Collision getColliderPlat();

    sf::RectangleShape body;
};