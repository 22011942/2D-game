#include "player.h"
#include "animation.h"
#include "collider.h"
#include "player.h"
#include <cmath>
#include <SFML/Graphics.hpp>

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight) : playerCollider(body) {
    initAnimation(texture, imageCount, switchTime);
    this->speed = speed;
    this->jumpHieght = jumpHeight;
    row = 0;
    faceRight = true;
    body.setSize(sf::Vector2f(30.0f, 20.0f));
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(500.0f, 550.0f);
    body.setTexture(texture);
}

void Player::updatePlayer(float deltaTime) {
    auto movement = sf::Vector2f(0.0f, 0.0f);

    velocity.x = 0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        //velocity.x -= speed;
        movement.x -= speed * deltaTime;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        //velocity.x += speed;
        movement.x += speed * deltaTime;


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { //add && canJump

        movement.y -= speed * deltaTime;

        //canJump = false;

        //velocity.y = -sqrtf(2.0f * 981.0f * jumpHieght);
        //sqaure root (2.0f * gravity * jumpheight)

    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        movement.y += speed * deltaTime;
    }

    velocity.y += 981.0f * deltaTime;

    if (velocity.x == 0.0f) {
        row = 0;

    } else {
        row = 1;
        
        if (movement.x > 0) { // change to velocity
            faceRight = true;
        } else {
            faceRight = false;
        }
    }



    update(row, deltaTime, faceRight);
    body.setTextureRect(getUvRect());
    body.move(movement); // change to velocity * delta time
}

void Player::Draw(sf::RenderWindow& window) {
    window.draw(body);
}

void Player::onCollision(sf::Vector2f direction) {
    if (direction.x < 0.0f) {
        //Collision on the left
        velocity.x = 0.0f;
    } else if (direction.x > 0.0f) {
        //Collision on the right
        velocity.x = 0.0f;
    }

    if (direction.y < 0.0f) {
        //Collision on the bottom
        velocity.y = 0.0f;
        canJump = true;
    } else if (direction.y > 0.0f) {
        //Collision on the top
        velocity.y = 0.0f;
    }

}

sf::Vector2f Player::getPlayerPosition() {
    return body.getPosition();
}

Collision& Player::getPlayerCollider() {
    return playerCollider;
}
