#pragma once
#include <SFML/Graphics.hpp>

void initAnimation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);

void update(int row, float deltaTime, bool faceRight);

const sf::IntRect getUvRect();