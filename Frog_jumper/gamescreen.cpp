#include "gamescreen.hpp"

GameScreen::GameScreen()
{
    backgroundTexture.loadFromFile("art/tileset.jpg", sf::IntRect(672, 96, 32, 32));
    backgroundTexture.setRepeated(true);
    background.setTexture(backgroundTexture);
    background.setScale(5, 5);
    background.setTextureRect(sf::IntRect(0,0, 960, 768));
    grassFrom.setPosition(0, 672);
    for(int i = 0; i < 6; i++)
    {
        woods[i].setPosition(rand() % (960-192) , 96 + 96 * i);
        if (i % 2 == 0) woods[i].speed = -woods[i].speed;
    }
}

void GameScreen::reset()
{
    for(int i = 0; i < 6; i++)
    {
        woods[i].speed = -woods[i].speed;
    }
    player.setPosition(5*96, 7*96);
}

void GameScreen::move()
{
    for(int i = 0; i < 6; i++)
    {
        if (woods[i].getPosition().x > 960) woods[i].setPosition(-192, woods[i].getPosition().y);
        if (woods[i].getPosition().x < -192) woods[i].setPosition(960, woods[i].getPosition().y);
        woods[i].move(woods[i].speed, 0);
    }
}

void GameScreen::drawScreen(sf::RenderWindow &window) {
    window.draw(background);
    window.draw(grassFrom);
    window.draw(grassTo);

    for(int i = 0; i < 6; i++)
    {
        window.draw(woods[i]);
    }
    window.draw(player);
}
