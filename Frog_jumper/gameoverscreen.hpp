#ifndef GAMEOVERSCREEN_HPP
#define GAMEOVERSCREEN_HPP
#include "mainscreen.hpp"

class GameOverScreen : public Screen
{
public:
    GameOverScreen();

    void drawScreen(sf::RenderWindow &window);

    void result(bool res);
private:
    sf::Text endScreenText;
    sf::Font font;
};

#endif // GAMEOVERSCREEN_HPP
