#include "button.hpp"

Button::Button(int x, int y, std::string str)
{
    body.setSize({200, 50});
    body.setPosition(x, y);
    font.loadFromFile("art/BAUHS93.TTF");
    buttonText.setCharacterSize(30);
    buttonText.setFont(font);

    buttonText.setFillColor(sf::Color::Black);
    buttonText.setString(str);
    centre();
}

void Button::centre()
{
    buttonText.setOrigin(buttonText.getGlobalBounds().width/2, buttonText.getGlobalBounds().height/2);
    buttonText.setPosition(body.getPosition().x + body.getGlobalBounds().width/2, body.getPosition().y + body.getGlobalBounds().height/2 - 10);
}

bool Button::isHover(sf::RenderWindow &window)
{
    return body.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
}

void Button::drawButton(sf::RenderWindow &window)
{
    window.draw(body);
    window.draw(buttonText);
}
