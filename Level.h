//
// Created by Александр Бисеров on 02.12.2022.
//

#ifndef KINGSANDPIGS_LEVEL_H
#define KINGSANDPIGS_LEVEL_H
#include "SFML/Graphics.hpp"
#include "vector"

class Level {
public:
    Level();

private:
    sf::Texture levelTexture;
    std::vector<sf::Sprite> tiles;


};


#endif //KINGSANDPIGS_LEVEL_H
