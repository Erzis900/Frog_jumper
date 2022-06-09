#include "gameoverscreen.hpp"

GameOverScreen::GameOverScreen()
{
    font.loadFromFile("art/BAUHS93.TTF");
    endScreenText.setCharacterSize(100);
    endScreenText.setFont(font);
    endScreenText.setPosition(280, 200);
    endScreenText.setFillColor(sf::Color::White);
    endScreenText.setString("");
}

void GameOverScreen::drawScreen(sf::RenderWindow &window) {
    window.draw(endScreenText);
}

void GameOverScreen::result(bool res) {
    if (res)
    {
        endScreenText.setString("YOU WIN");
    }
    else
    {
        endScreenText.setString("YOU LOSE");
    }
}
