#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <SFML/Graphics.hpp>

class Button
{
public:
    sf::RectangleShape body;
    sf::Text buttonText;
    sf::Font font;

    Button(int x, int y, std::string str);

    void centre();

    bool isHover(sf::RenderWindow &window);

    void drawButton(sf::RenderWindow &window);
};

#endif // BUTTON_HPP
