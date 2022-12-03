//
// Created by Александр Бисеров on 02.12.2022.
//

#ifndef KINGSANDPIGS_PARSER_H
#define KINGSANDPIGS_PARSER_H
#include "Map.h"

class Parser {
public:
    Map parseMap();
    sf::Texture levelTexture;
};


#endif //KINGSANDPIGS_PARSER_H
