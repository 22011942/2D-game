#include "collider.h"
#include "platform.h"
#include <SFML/Graphics.hpp>

Platform::Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position) {
    body.setSize(size);
    body.setOrigin(size / 2.0f);
    body.setTexture(texture);
    body.setPosition(position);
}

// Draw the platform to the window
void Platform::drawPlatform(sf::RenderWindow& window) {
    window.draw(body);
}

// Return a Collision object for the platform
Collision Platform::getColliderPlat() {
    return Collision(body);
}