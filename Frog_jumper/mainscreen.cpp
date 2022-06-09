#include "mainscreen.hpp"

MainScreen::MainScreen() : button1(380, 320, "Play"), button2(380, 400, "Exit")
{
    active = true;
    font.loadFromFile("art/BAUHS93.TTF");
    title.setCharacterSize(80);
    title.setFont(font);
    title.setFillColor(sf::Color::White);
    title.setString("Frog jumper");
    title.setOrigin(title.getGlobalBounds().width/2, title.getGlobalBounds().height/2);
    title.setPosition(button1.body.getPosition().x + button1.body.getGlobalBounds().width/2, 200);
}
