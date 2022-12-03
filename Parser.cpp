//
// Created by Александр Бисеров on 02.12.2022.
//

#include "Parser.h"

using namespace tinyxml2;


Map Parser::parseMap() {
    XMLDocument doc;
    XMLError err =  doc.LoadFile( "/Users/aleksandrbiserov/CLionProjects/KingsAndPigs/TestLevel.tmx" );
    if (err) {
        printf("Failed");
    }

    XMLElement *mapElement = doc.FirstChildElement("map");
    Map map;
    map.parse(mapElement);
    return map;
}