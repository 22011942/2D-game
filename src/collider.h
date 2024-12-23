#pragma once
#include <SFML/Graphics.hpp>

// Define the Collision struct in the header
struct Collision {
    sf::RectangleShape& body; // Reference to the shape this collider wraps

    // Constructor
    Collision(sf::RectangleShape& body);

    // Member functions
    sf::Vector2f getPosition() const;
    sf::Vector2f getHalfSize() const;
    void move(float dx, float dy);

    // Collision check
    bool checkCollision(Collision& other, float push, sf::Vector2f& direction);
};
