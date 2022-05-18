#include <SFML/Window.hpp>

#include <iostream>
#include "frog.hpp"
#include "map.hpp"
#include <ctime>

using namespace std;

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

    MainScreen()
    {
        active = true;
    }
};

class Wood : public sf::RectangleShape
{
public:
    float speed = 1;
    Wood()
    {
        speed = (rand() % 15 + 10) / 10.0;
        setSize({192, 94});
        setFillColor(sf::Color::Red);
    }
};

class Grass : public Wood
{
public:
    bool isPlayerOn = false;
    Grass()
    {
        setSize({96*10, 96});
        setFillColor(sf::Color(26, 109, 19));
        speed = 0;
    }
};

class GameScreen : public Screen
{
public:
    sf::Sprite background;
    sf::Texture backgroundTexture;
    Frog player;
    Grass grassFrom;
    Grass grassTo;
    Wood woods[6];

    GameScreen()
    {
        backgroundTexture.loadFromFile("../Frog_Jumper/art/tileset.jpg", sf::IntRect(672, 96, 32, 32));
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

    void move()
    {
        for(int i = 0; i < 6; i++)
        {
            if (woods[i].getPosition().x > 960) woods[i].setPosition(-192, woods[i].getPosition().y);
            if (woods[i].getPosition().x < -192) woods[i].setPosition(960, woods[i].getPosition().y);
            woods[i].move(woods[i].speed, 0);
        }

    }
    void drawScreen(sf::RenderWindow &window)
    {
        window.draw(background);
        window.draw(grassFrom);
        window.draw(grassTo);
        for(int i = 0; i < 6; i++)
        {
            window.draw(woods[i]);
        }
        window.draw(player);
    }
};


class GameOverScreen : public Screen
{
public:
    GameOverScreen()
    {
        tex.loadFromFile("../Frog_Jumper/art/endscreen.png");
        sprite.setTexture(tex);
    }

    void drawScreen(sf::RenderWindow &window)
    {
        window.draw(sprite);
    }
private:
    sf::Texture tex;
    sf::Sprite sprite;
};

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

    if (tmp == NULL)
    {
        //zaba w wode
        game.active = false;
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

int main() {
    sf::Vector2i window_size(960, 768);
    MainScreen main;
    GameScreen game;
    GameOverScreen end;
    main.active = false;
    game.active = true;
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(window_size.x, window_size.y), "Frog jumper");
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (game.active) moveUpDown(event, game);

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
