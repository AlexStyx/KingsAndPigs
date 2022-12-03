//
// Created by Александр Бисеров on 30.11.2022.
//

#include "Game.h"
#include "Parser.h"
#include "vector"
#include "Player.h"

void Game::start() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Kings And Pigs");
    Parser parser;
    Map map = parser.parseMap();
    map.prepare();
    Player player(map);
    sf::Clock clock;
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();

        time /= 500;
        if (time > 40) time = 40;
        sf::Event event;

        while (window.pollEvent(event))

        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        player.update(time);
        window.clear();
        map.draw(window);
        window.draw(player.sprite);
        window.display();
    }
}