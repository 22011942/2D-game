#include "player.h"
#include "animation.h"
#include "collider.h"
#include "player.h"
#include <cmath>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "mapGen.h"

const bool FLIGHT = true;

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight) : playerCollider(body) {
    initAnimation(texture, imageCount, switchTime);
    this->speed = speed;
    this->jumpHieght = jumpHeight;
    row = 0;
    faceRight = true;
    body.setSize(sf::Vector2f(30.0f, 20.0f));
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(0.0f, 50.0f);
    body.setTexture(texture);
}

void Player::updatePlayer(float deltaTime) {
    auto movement = sf::Vector2f(0.0f, 0.0f);

    velocity.x = 0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))

        if (FLIGHT) {
            movement.x -= speed * deltaTime;
        } else {
            velocity.x -= speed;  
        }
        

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))

        if (FLIGHT) {
            movement.x += speed * deltaTime;
        } else {
            velocity.x += speed; 
        }


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && canJump) { //add && canJump

        if (FLIGHT) {
            movement.y -= speed * deltaTime;
        } else {
            canJump = false;
            velocity.y = -sqrtf(2.0f * 981.0f * jumpHieght);
            //sqaure root (2.0f * gravity * jumpheight)
        }


    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && FLIGHT) {
        movement.y += speed * deltaTime;
    }

    velocity.y += 981.0f * deltaTime;

    if (velocity.x == 0.0f) {
        row = 0;

    } else {
        row = 1;

        if (velocity.x > 0 && !FLIGHT || movement.x > 0 && FLIGHT) { // change to velocity
            faceRight = true;
        } else {
            faceRight = false;
        }

    }



    update(row, deltaTime, faceRight);
    body.setTextureRect(getUvRect());
    if (FLIGHT) {
        body.move(movement);
    } else {
        body.move(velocity * deltaTime); // change to velocity * delta time
    }
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

void Player::mouseInteration(sf::RenderWindow& window, ChunkData* chunk) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

        for (size_t indx = 0; indx < chunk->chunkInfo.getVertexCount(); indx +=4) {
            if (chunk->chunkInfo[indx].position.x / BLOCK_SIZE == (int)worldPos.x / BLOCK_SIZE && chunk->chunkInfo[indx].position.y / BLOCK_SIZE == (int)worldPos.y / BLOCK_SIZE) {
                chunk->chunkInfo[indx].color = sf::Color::Transparent;
                chunk->chunkInfo[indx + 1].color = sf::Color::Transparent;
                chunk->chunkInfo[indx + 2].color = sf::Color::Transparent;
                chunk->chunkInfo[indx + 3].color = sf::Color::Transparent;
                std::cout << "A match has been found" << std::endl;
            }
        }
    }
}

sf::Vector2f Player::getPlayerPosition() {
    return body.getPosition();
}

Collision& Player::getPlayerCollider() {
    return playerCollider;
}
