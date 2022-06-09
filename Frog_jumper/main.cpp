#include <SFML/Window.hpp>

#include <iostream>
#include "frog.hpp"
#include "map.hpp"
#include "button.hpp"
#include "wood.hpp"
#include "grass.hpp"
#include "mainscreen.hpp"
#include "gamescreen.hpp"
#include "gameoverscreen.hpp"

#include <ctime>

using namespace std;

void moveUpDown(sf::Event &event, GameScreen &game)
{
    if(event.type == sf::Event::KeyPressed) {
        if(event.key.code == sf::Keyboard::Up) {
            game.player.move(0, -96);
        }
    }
}

sf::Vector2f calculateOrigin(Frog pl)
{
    float x = pl.getPosition().x+pl.getGlobalBounds().width/2;
    float y = pl.getPosition().y+pl.getGlobalBounds().height/2;
    return {x, y};
}

void moveLeftRight(GameScreen &game, GameOverScreen &end)
{
    Wood *tmp = NULL;
    for (int i = 0; i < 6; i++) if (game.woods[i].getGlobalBounds().contains(calculateOrigin(game.player).x, calculateOrigin(game.player).y))
    {
        tmp = &game.woods[i];
    }
    if (game.player.getGlobalBounds().intersects(game.grassFrom.getGlobalBounds())) tmp = &game.grassFrom;
    if (game.player.getGlobalBounds().intersects(game.grassTo.getGlobalBounds())) tmp = &game.grassTo;
    if (game.grassTo.getGlobalBounds().contains(calculateOrigin(game.player).x, calculateOrigin(game.player).y))
    {
        //wygrana
        game.active = false;
        game.reset();
        end.active = true;
        end.result(true);
    }
    if (tmp == NULL)
    {
        //przegrana
        //zaba w wode
        game.active = false;
        game.reset();
        end.result(false);
        end.active = true;
    }
    else
    {
        if (game.player.getPosition().x <= 0) game.player.move(1, 0);
        else if (game.player.getPosition().x >= 864) game.player.move(-1, 0);
        else game.player.move(tmp->speed, 0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            game.player.move(-3, 0);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            game.player.move(3, 0);
        }
    }
}

int main() { //lilie To sa drzewa z predkoscia 0 i innym np kolorem
    sf::Vector2i window_size(960, 768);
    MainScreen main;
    GameScreen game;
    GameOverScreen end;
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(window_size.x, window_size.y), "Frog jumper");
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (main.active)
            {
                if (event.type == sf::Event::MouseButtonPressed && main.button1.isHover(window))
                {
                    //gra
                    game.active = true;
                    main.active = false;
                }
                else if (event.type == sf::Event::MouseButtonPressed && main.button2.isHover(window))
                {
                    window.close();
                }
            }
            else if (game.active)
            {
                moveUpDown(event, game);
            }
            else if (end.active)
            {
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    //restartowanie gry.
                    end.active = false;
                    main.active = true;
                }
            }
        }

        if (game.active) game.move();
        if (game.active) moveLeftRight(game, end);

        window.clear(sf::Color::Black);
        if (main.active) main.drawScreen(window);
        else if (game.active) game.drawScreen(window);
        else if (end.active) end.drawScreen(window);
        window.display();
    }

    return 0;
}
