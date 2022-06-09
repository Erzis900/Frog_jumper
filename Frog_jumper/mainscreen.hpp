#ifndef MAINSCREEN_HPP
#define MAINSCREEN_HPP
#include <SFML/Graphics.hpp>
#include "button.hpp"

class Screen
{
public:
    bool active = false;
    virtual void drawScreen(sf::RenderWindow &window)
    {

    }
};

class MainScreen : public Screen
{
public:
    sf::Text title;
    sf::Font font;
    Button button1;
    Button button2;
    int abc;

    MainScreen();

    void drawScreen(sf::RenderWindow &window)
    {
        window.draw(title);
        button1.drawButton(window);
        button2.drawButton(window);
    }
};

#endif // MAINSCREEN_HPP
