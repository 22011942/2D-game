#include "collider.h"
#include <cmath> // For std::abs, std::min, and std::max

// Define the constructor
Collision::Collision(sf::RectangleShape& body) : body(body) {}

// Member function to get the position of the body
sf::Vector2f Collision::getPosition() const {
    return body.getPosition();
}

// Member function to get half the size of the body
sf::Vector2f Collision::getHalfSize() const {
    return body.getSize() / 2.0f;
}

// Move the body by a specified amount
void Collision::move(float dx, float dy) {
    body.move(dx, dy);
}

// Check collision with another Collision object
bool Collision::checkCollision(Collision& other, float push, sf::Vector2f& direction) {
    sf::Vector2f otherPos = other.getPosition();
    sf::Vector2f otherHalfSize = other.getHalfSize();
    sf::Vector2f thisPos = getPosition();
    sf::Vector2f thisHalfSize = getHalfSize();

    float deltaX = otherPos.x - thisPos.x;
    float deltaY = otherPos.y - thisPos.y;

    float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

    if (intersectX < 0.0f && intersectY < 0.0f) {
        push = std::min(std::max(push, 0.0f), 1.0f);

        if (intersectX > intersectY) {
            if (deltaX > 0.0f) {
                move(intersectX * (1.0f - push), 0.0f);
                other.move(-intersectX * push, 0.0f);

                direction.x = 1.0f;
                direction.y = 0.0f;

            } else {
                move(-intersectX * (1.0f - push), 0.0f);
                other.move(intersectX * push, 0.0f);

                direction.x = -1.0f;
                direction.y = 0.0f;

            }
        } else {
            if (deltaY > 0.0f) {
                move(0.0f, intersectY * (1.0f - push));
                other.move(0.0f, -intersectY * push);

                direction.x = 0.0f;
                direction.y = 1.0f;

            } else {
                move(0.0f, -intersectY * (1.0f - push));
                other.move(0.0f, intersectY * push);

                direction.x = 0.0f;
                direction.y = -1.0f;

            }
        }

        return true;
    }

    return false;
}
