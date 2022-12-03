//
// Created by Александр Бисеров on 03.12.2022.
//

#ifndef KINGSANDPIGS_MAP_H
#define KINGSANDPIGS_MAP_H

#endif //KINGSANDPIGS_MAP_H
#include "tinyxml2.h"
#include "string"
#include "vector"
#include "SFML/Graphics.hpp"

using namespace tinyxml2;

struct Tileset {
    int firstGlobalId;
    std::string source = "/Users/aleksandrbiserov/Downloads/Kings and Pigs/Sprites/14-TileSets/Terrain (32x32).png";
    sf::Texture texture;
    void parse(XMLElement *element) {
        // todo: добавить парсер ресурса
        firstGlobalId = atoi(element->Attribute("firstgid"));
        texture.loadFromFile(source);
    }
};


struct Layer {
    std::vector<int> tileGlobalIds;
};


enum ObjectType {
    ObjectTypeUknown,
    ObjectTypeSolid,
};

struct Object {
    int id;
    std::string name;
    ObjectType type;
    sf::FloatRect rect;

    void parse(XMLElement *element) {
        id = atoi(element->Attribute("id"));
        name = element->Attribute("name");
        type = ObjectTypeUknown;
        if (name == "solid") {
            type = ObjectTypeSolid;
        }
        float x, y, width, height;
        x = std::stof(element->Attribute("x"));
        y = std::stof(element->Attribute("y"));
        width = std::stof(element->Attribute("width"));
        height = std::stof(element->Attribute("height"));
        rect = sf::FloatRect(x, y, width, height);
    }

};

struct Map {
    std::vector<sf::Sprite> sprites;
    int width, height, tileHeight, tileWidth;
    std::vector<Tileset> tilesets;
    std::vector<Layer> layers;
    std::vector<Object> objects;

    void prepare() {
        createSprites(subrects());
    }

    void draw(sf::RenderWindow &window) {
        for (auto sprite : sprites) window.draw(sprite);
    }

    void parse(XMLElement *element) {
        width = atoi(element->Attribute("width"));
        height = atoi(element->Attribute("height"));
        tileWidth = atoi(element->Attribute("tilewidth"));
        tileHeight = atoi(element->Attribute("tileheight"));
        parseTilesets(element);
        parseLayers(element);
        parseObjects(element);
    }

    void parseTilesets(XMLElement *element) {
        XMLElement *tilesetElement = element->FirstChildElement("tileset");
        while (tilesetElement) {
            Tileset newTileset;
            newTileset.parse(tilesetElement);
            tilesets.push_back(newTileset);
            tilesetElement = tilesetElement->NextSiblingElement("tileset");
        }
    }

    void parseLayers(XMLElement *element) {
        XMLElement *layerElement = element->FirstChildElement("layer");
        while (layerElement) {
            Layer layer;
            std::string layerData = layerElement->FirstChildElement("data")->GetText();
            std::string number;
            for (const char c : layerData) {
                if (isdigit(c)) {
                    number += c;
                    continue;
                }
                if (number.length()) layer.tileGlobalIds.push_back(std::stoi(number));
                number = "";
            }
            layers.push_back(layer);
            layerElement = layerElement->NextSiblingElement("layer");
        }
    }

    std::vector<sf::Rect<int>> subrects() {
        int columns = tilesets[0].texture.getSize().x / tileWidth;
        int rows = tilesets[0].texture.getSize().y / tileHeight;

        std::vector<sf::Rect<int> > subRects;

        for(int y = 0; y < rows; y++) {
            for (int x = 0; x < columns; x++) {
                sf::Rect<int> rect;

                rect.top = y * tileHeight;
                rect.height = tileHeight;
                rect.left = x * tileWidth;
                rect.width = tileWidth;

                subRects.push_back(rect);
            }
        }
        return subRects;
    }

    void createSprites(std::vector<sf::Rect<int>> subRects) {
        for (const auto layer : layers) {
            int x = 0;
            int y = 0;
            for (int globalId : layer.tileGlobalIds) {
                int subrectIndex = globalId - tilesets[0].firstGlobalId;
                if (subrectIndex >= 0)
                {
                    sf::Sprite sprite;
                    sprite.setTexture(tilesets[0].texture);
                    sprite.setTextureRect(subRects[subrectIndex]);
                    sprite.setPosition(x * tileWidth, y * tileHeight);
                    sprites.push_back(sprite);
                }
                x++;
                if (x >= width)
                {
                    x = 0;
                    y++;
                    if(y >= height)
                        y = 0;
                }
            }
        }
    }

    void parseObjects(XMLElement *element) {
        XMLElement *objectGroup = element->FirstChildElement("objectgroup");
        if (objectGroup) {
            XMLElement *objectElement = objectGroup->FirstChildElement("object");
            while (objectElement) {
                Object newObject;
                newObject.parse(objectElement);
                objects.push_back(newObject);
                objectElement = objectElement->NextSiblingElement("object");
            }
        }
    }
};