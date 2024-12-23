#include "animation.h"
#include <SFML/Graphics.hpp>

struct AnimationData {
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;
    sf::IntRect uvRect;

    float totalTime;
    float switchTime;
};
static AnimationData aniData;

void initAnimation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime) {
    aniData.imageCount = imageCount;
    aniData.switchTime = switchTime;
    aniData.totalTime = 0.0f;
    aniData.currentImage.x = 0;

    aniData.uvRect.width = texture->getSize().x / float(aniData.imageCount.x);
    aniData.uvRect.height = texture->getSize().y / float(aniData.imageCount.y);
}

void update(int row, float deltaTime, bool faceRight) {
    aniData.currentImage.y = row;
    aniData.totalTime += deltaTime;

    if (aniData.totalTime >= aniData.switchTime) {
        aniData.totalTime -= aniData.switchTime;
        aniData.currentImage.x++;

        if (aniData.currentImage.x >= aniData.imageCount.x) {
            aniData.currentImage.x = 0;
        }
    }

    
    aniData.uvRect.top = aniData.currentImage.y * aniData.uvRect.height;

    if (faceRight) {
        aniData.uvRect.left = aniData.currentImage.x * aniData.uvRect.width;
        aniData.uvRect.width = abs(aniData.uvRect.width);
    } else {
        aniData.uvRect.left = (aniData.currentImage.x + 1)  * abs(aniData.uvRect.width);
        aniData.uvRect.width = -abs(aniData.uvRect.width);
    }
}

const sf::IntRect getUvRect() {
    return aniData.uvRect;
}