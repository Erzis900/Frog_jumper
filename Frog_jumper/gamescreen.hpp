#ifndef GAMESCREEN_HPP
#define GAMESCREEN_HPP
#include "mainscreen.hpp"
#include "frog.hpp"
#include "grass.hpp"
#include "wood.hpp"

class GameScreen : public Screen
{
public:
    sf::Sprite background;
    sf::Texture backgroundTexture;
    Frog player;
    Grass grassFrom;
    Grass grassTo;
    Wood woods[6];

    GameScreen();

    void reset();

    void move();

    void drawScreen(sf::RenderWindow &window);
};

#endif // GAMESCREEN_HPP
