//
// Created by Александр Бисеров on 03.12.2022.
//

#ifndef KINGSANDPIGS_PLAYER_H
#define KINGSANDPIGS_PLAYER_H

#endif //KINGSANDPIGS_PLAYER_H
#include "SFML/Graphics.hpp"
#include "Parser.h"

struct Player {
    float dx, dy;
    bool grounded = false;
    float jumpForce = 0;
    Map map;
    sf::Sprite sprite;
    sf::Texture texture;
    Player(Map &mp) {
        map = mp;
        texture.loadFromFile("/Users/aleksandrbiserov/CLionProjects/KingsAndPigs/Idle (78x58).png");
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(9, 18, 37, 26));
    }

    void update(float time) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
            sprite.setTextureRect(sf::IntRect(9 + 37, 18, -37, 26));
            dx = -0.1;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            sprite
            .setTextureRect(sf::IntRect(9, 18, 37, 26));
            dx = 0.1;
        }

        if (!grounded) {
            dy += 0.0005 * time;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && grounded) {
            dy = -0.25;
        }
        grounded = false;
        collision();
        sprite.move(dx, dy);
        dx = 0;
    }

    void collision() {
        sf::FloatRect playerRect(
                abs(sprite.getPosition().x + dx),
                abs(sprite.getPosition().y + dy),
                abs(sprite.getTextureRect().width),
                abs(sprite.getTextureRect().height)
        );

        std::vector<Object> intersectedObjects;

        for (auto object: map.objects) {
            if (playerRect.intersects(object.rect)) {
                switch (object.type) {
                    case ObjectTypeUknown:break;

                    case ObjectTypeSolid:
                        float newXPosition = playerRect.left;
                        float newYPosition = playerRect.top;
                        // vertical
                        if (object.rect.top < playerRect.top &&
                            object.rect.top + object.rect.height < playerRect.top + playerRect.height) { // user top side is in the block
                            dy = 0;
                            newYPosition = object.rect.top + object.rect.height;
                        }

                        if (playerRect.top < object.rect.top &&
                            playerRect.top + playerRect.height > object.rect.top) { // user bottom side is in the block
                            dy = 0;
                            newYPosition = object.rect.top - playerRect.height;
                            grounded = true;
                        }

                        if (!dy)
                            sprite.setPosition(sprite.getPosition().x, newYPosition);

                        playerRect.top = newYPosition;
                        if (!playerRect.intersects(object.rect)) break;

                        // horizontal
                        if (playerRect.left > object.rect.left &&
                            playerRect.left + playerRect.width > object.rect.left + object.rect.width) {
                            dx = 0;
                            newXPosition = object.rect.left + object.rect.width;
                        }

                        if (playerRect.left + playerRect.width > object.rect.left &&
                            playerRect.left < object.rect.left) {
                            dx = 0;
                            newXPosition = object.rect.left - playerRect.width;
                        }

                        if (!dx)
                            sprite.setPosition(newXPosition, sprite.getPosition().y);
                        break;
                }
            }
        }
    }
};